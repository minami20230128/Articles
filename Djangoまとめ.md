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
