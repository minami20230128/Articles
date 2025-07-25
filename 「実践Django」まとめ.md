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
以下のように、先にJOINしてから取り出せば防ぐことができる。

```
テーブル名.objects().select_related(JOINするカラム名).all()
```

