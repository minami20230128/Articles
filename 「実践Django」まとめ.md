# ・「実践Django」まとめ  
## 1章
HttpRequestクラスはビュー関数を直接呼び出すため、ビュー関数の単体テスト用。
```
from django.http import HttpRequest
request = HttpRequest()
response = top(request)
```
Clientクラスはエンドポイントにリクエストを送るため、結合テスト・E2Eテスト用。
```
from django.test import Client
client = Client()
response = client.get("/")
```

## 2章
- モデルがどのようなSQLでマイグレーションされるかは、以下のコマンドで確認可能。
```
manage.py sqlmigrate <app_label> <migration_name>
```
- 「id」カラムはモデルになくても勝手にオートインクリメントの項目として追加される。  
- テーブル名を変更したい場合Metaオプションでできる。 
- オブジェクトの操作は以下のように行う。  
保存...オブジェクト.save()  
消去...オブジェクト.delete()  
更新...フィールドを変更したうえでオブジェクト.save()  
- DBのテーブル操作は以下のように行う。
全件取得...テーブル名.objects.all()  
idで取得...テーブル名.filter(id)  
特定のid以外の全件を取得...テーブル名.exclude(id)  
- オリジナルのクエリパターンを作成する場合、django.db.models.Managerを継承したモデルマネージャを作成。  
- トランザクション管理したい場合、以下のように書く。
```
with transaction.atomic():
    ...
```
### N+1問題への対処
N+1問題...DBアクセスにおいて、1件のSQLで取得できる情報を複数件のSQLで取得しようとしてしまうこと。  
ORMにおいて、DB上ではそれぞれ別テーブルに記録されているオブジェクトとそのメンバ変数を取り出したときに起きやすい。  
Djangoでこれを防ぐには2つの方法がある。  

- select_related
  外部キーや一対一の関係性に使う。
  テーブルを事前に連結してから取り出す。
```
テーブル名.objects().select_related(JOINするカラム名).all()
```

- prefetch_related
  一対多、多対多の関係性に使う。
  Pythonコード上でテーブル連結する。
```
テーブル名.objects.prefetch_related(JOINするカラム名)
```

## 8章
- JSON APIの実装方法
serializers.py...Serializerクラスを利用してオブジェクトをJSONにシリアライズ・デシリアライズする方法を定める。  
api_views.py...ViewSetsクラスを利用し、モデルに対するCRUD APIを一気に用意する。  
api_urls.py...URLのマッピングを行う。Routerクラスを使用することで、api_views.pyに用意したAPIが一気に使えるようになる。

- ページネーションの実装方法
以下の3つのクラスを利用して実装できる。  
**PageNumberPagination**...ページ番号を指定  
**LimitOffsetPagination**...開始位置と取得サイズを指定して取得  
**CursorPagination**...特定のリソースを指定しそれより前、もしくはあとを取得する  
どのページネーションを使用するかはsettings.pyで指定可能。  
クラスベースビューを使用している場合は、pagination_class属性で指定できる。  
絶対位置指定のAPIでは、ページネーションの途中であるデータが削除された場合、前後のデータが取得できなくなるズレを防止することが可能。  
また、B木インデックスを使用したDBからデータ取得する場合も、相対位置指定のクラスより計算量少なく取得できる。  
これらのメリット・デメリットを比較して使用することが重要。

- APIのリクエスト制限
settings.pyから以下のようなリクエスト制限方法を指定できる。
AnonRateThrottle...未認証ユーザをIPアドレスベースで制限
UserRateThrottle...認証済みユーザの主キーをベースにした制限
ScopedRateThrottle...特定のAPIのアクセス制限（重いAPIなど）