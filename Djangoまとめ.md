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