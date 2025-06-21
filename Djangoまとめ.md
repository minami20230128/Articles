# Djangoまとめ

## プロジェクトの作成
- ディレクトリ作成  
mkdir djangotutorial

- プロジェクト立ち上げ  
django-admin startproject mysite djangotutorial

## URLConfとは
URLConfとは、**URLディスパッチャ**の動作を決めるDjangoの仕組み。  
URLディスパッチャ...URLにアクセスされたときに、URLを解釈し必要なページを返す処理をするもの。  
グローバルなURLConfとアプリケーションごとのURLConfがあり、後者を前者から指定することで、アプリケーションの中のページを表示できる。

以下はアプリケーションのURLConfであり、polls/views.pyのindex関数を実行するコード。  

polls/url.py
```
from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
]
```

以下はグローバルのURLConfであり、polls/urls.pyを呼び出す設定になっている。

mysite/urls.py
```
from django.contrib import admin
from django.urls import include, path

urlpatterns = [
    path("polls/", include("polls.urls")),
    path("admin/", admin.site.urls),
]
```

## DBテーブル作成方法
settings.pyの設定通りにマイグレーションを行う。
```
python manage.py migrate
```
**manage.py**とは、Djangoの管理用スクリプト。  
これを通して、プロジェクトの設定を反映しながらマイグレーションを実行する。

## モデルの作成
**models.py**に作成するのが一般的な監修。
以下のように、テーブル名=クラス名、カラム名=変数名として定義。

```
from django.db import models


class Question(models.Model):
    question_text = models.CharField(max_length=200)
    pub_date = models.DateTimeField("date published")


class Choice(models.Model):
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    choice_text = models.CharField(max_length=200)
    votes = models.IntegerField(default=0)
```

## モデルの有効化
**mysite/settings.py**にアプリケーションを登録する。

```
INSTALLED_APPS = [
    "polls.apps.PollsConfig",  <-この行
    "django.contrib.admin",
    "django.contrib.auth",
    "django.contrib.contenttypes",
    "django.contrib.sessions",
    "django.contrib.messages",
    "django.contrib.staticfiles",
]
```

manage.pyを通して、pollsアプリケーションのモデルの変更点を検出し、マイグレーションファイルを作成するコマンド。  
新しく作ったQuestion、Choiceモデルを反映する。
```
python manage.py makemigrations polls
```

このコマンドでマイグレーションが発行するSQLの内容を確認できる。
以下pollsアプリのマイグレーションファイル・0001_initial.py に対応するSQL文を表示するもの。
```
python manage.py sqlmigrate polls 0001
```

## 対話シェル
対話シェルとは、ちょっとしたPythonコードを実行してDB操作などの動作確認ができるツール。
以下のコマンドで起動可能。
```
python manage.py shell
```

```
>>> from polls.models import Choice, Question  # Import the model classes we just wrote.

ChoiceモデルとQuestionモデルを読み込み、これ以降で使えるようにしている。

# No questions are in the system yet.
>>> Question.objects.all()
<QuerySet []>

Questionテーブルの全てのレコードを取得。（空）

# Create a new Question.
# Support for time zones is enabled in the default settings file, so
# Django expects a datetime with tzinfo for pub_date. Use timezone.now()
# instead of datetime.datetime.now() and it will do the right thing.
>>> from django.utils import timezone
>>> q = Question(question_text="What's new?", pub_date=timezone.now())

Questionオブジェクトを作成。

# Save the object into the database. You have to call save() explicitly.
>>> q.save()

作成したQuestionオブジェクトをDBに保存する。

# Now it has an ID.
>>> q.id
1

保存したオブジェクトをDB登録したときに、自動採番されたIDを表示する。

# Access model field values via Python attributes.
>>> q.question_text
"What's new?"
>>> q.pub_date
datetime.datetime(2012, 2, 26, 13, 0, 0, 775217, tzinfo=datetime.timezone.utc)

question_textとpub_dateが指定したとおりになっていることを確認。

# Change values by changing the attributes, then calling save().
>>> q.question_text = "What's up?"
>>> q.save()

Questionオブジェクトのテキストを変更して再度保存。

# objects.all() displays all the questions in the database.
>>> Question.objects.all()
<QuerySet [<Question: Question object (1)>]>
```

再度DBに保存されているQuestonをずべて表示。
1件保存されていることが分かる。

## adminサイト
管理者だけがログインできるサイト。
GUIでDBのCRUD操作ができる。

### ログイン方法
ユーザを作成。以下のコマンドに続けてユーザ名・メールアドレス・パスワードを入力。
```
python manage.py createsuperuser
```

開発サーバを起動。
```
python manage.py runserver
```
以下にアクセス。
http://127.0.0.1:8000/admin/ 

## ビューの作成
polls/views.py...URLで渡されたパラメータを受け取り、文字列に埋め込む関数を定義 
```
def detail(request, question_id):
    return HttpResponse("You're looking at question %s." % question_id)


def results(request, question_id):
    response = "You're looking at the results of question %s."
    return HttpResponse(response % question_id)


def vote(request, question_id):
    return HttpResponse("You're voting on question %s." % question_id)
```

polls/urls.py...各URLとviews.py上の関数を結びつける
```
from django.urls import path

from . import views

urlpatterns = [
    # ex: /polls/
    path("", views.index, name="index"),
    # ex: /polls/5/
    path("<int:question_id>/", views.detail, name="detail"),
    # ex: /polls/5/results/
    path("<int:question_id>/results/", views.results, name="results"),
    # ex: /polls/5/vote/
    path("<int:question_id>/vote/", views.vote, name="vote"),
]
```
path("<int:question_id>/", views.detail, name="detail")の1行を例にとって説明すると、
- <int:question_id>...question_idという数値を受け取る
- views.detail...views.pyのdetail関数が呼ばれる
- name="detail"...「/polls/5/」のような形式のURLに「detail」という名前をつけている
  例:  
  polls/index.htmlには、 
  ```
  <li><a href="/polls/{{ question.id }}/">{{ question.question_text }}</a></li>
  ```
  このように「/polls/{{ question.id }}/」とURLをハードコートすることも可能だが、  
  ```
  <li><a href="{% url 'detail' question.id %}">{{ question.question_text }}</a></li>
  ```
  'detail'という名前をつけたほうが可読性が上がる。

### テンプレートの分離

polls/templates/polls/index.html...テンプレート。Pythonの変数をHTMLに埋め込むための仕組み。
```
{% if latest_question_list %}
    <ul>
    {% for question in latest_question_list %}
        <li><a href="/polls/{{ question.id }}/">{{ question.question_text }}</a></li>
    {% endfor %}
    </ul>
{% else %}
    <p>No polls are available.</p>
{% endif %}
```

### テンプレートの呼び出し方・ショートカット
- 通常のテンプレートロード  
行う処理は以下の3段階。
1. loader.get_template()でテンプレートを読み込む
2. Questionテーブルから読み出したデータをcontext(後述)としてテンプレートに渡す
3. HttpResponse()でレスポンスとして返す
```
from django.http import HttpResponse
from django.template import loader

from .models import Question

def index(request):
    latest_question_list = Question.objects.order_by("-pub_date")[:5]
    template = loader.get_template("polls/index.html")
    context = {
        "latest_question_list": latest_question_list,
    }
    return HttpResponse(template.render(context, request))
```

上は冗長な書き方で、**ショートカットバージョン**の**Render()関数**の仕様が推奨されている。
```
from django.shortcuts import render
from .models import Question

def index(request):
    latest_question_list = Question.objects.order_by("-pub_date")[:5]
    context = {"latest_question_list": latest_question_list}
    return render(request, "polls/index.html", context)
```

**context**...テンプレートに埋め込む変数を渡すための辞書型の変数。
4行目の
```
context = {
        "latest_question_list": latest_question_list,
    }
```
のこと。

- 404 エラーの送出
行っている処理としては、
1. URLで渡されたquestion_idに当てはまるQuestionを取得
2. 取得できなかった場合404を発生させる
```
from django.http import Http404
from django.shortcuts import render

from .models import Question

# ...
def detail(request, question_id):
    try:
        question = Question.objects.get(pk=question_id)
    except Question.DoesNotExist:
        raise Http404("Question does not exist")
    return render(request, "polls/detail.html", {"question": question})
```

この処理にもショートカットがあり、**get_object_or_404()**の使用が推奨されている。
```
from django.shortcuts import get_object_or_404, render

from .models import Question

# ...
def detail(request, question_id):
    question = get_object_or_404(Question, pk=question_id)
    return render(request, "polls/detail.html", {"question": question})
```
### URLに名前空間を作る方法
polls/urls.pyに「app_name = "polls"」という記述を追加する。
```
from django.urls import path

from . import views

app_name = "polls"
urlpatterns = [
    path("", views.index, name="index"),
    path("<int:question_id>/", views.detail, name="detail"),
    path("<int:question_id>/results/", views.results, name="results"),
    path("<int:question_id>/vote/", views.vote, name="vote"),
]
```

index.htmlのURL部分を「detail->polls/detail」に置き換える
```
<li><a href="{% url 'polls:detail' question.id %}">{{ question.question_text }}</a></li>
```