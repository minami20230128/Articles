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
同じサーバに攻撃したいページがある場合はlocalhost、別サーバにある場合はIPアドレスを変えながら攻撃してどこにあるか探る。

## 詰まったところ・疑問点など
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

- Burpで管理者画面のIPアドレスを探り、攻撃する方法
1. リクエスト内で別APIを叩いている箇所を探す
2. Burp Proxyでリクエストを傍受する
3. 該当リクエストを右クリックし「Send to Intruder」を選択
4. IntruderタブでAPIを叩いている箇所（今回で言えばstockApiパラメータ）のIPアドレスをハイライトし、「Add §」ボタンをクリック
5. Payloadタブで「Payload type」に「numbers」を選択。「Number Range」の「From」に1、「To」に255を入力
6. 「Start Attack」をクリック。
Intruderの結果は本体とは別タブに出るので注意！！
7. Status Code=200のレスポンスがあれば、それが攻撃対象のIPアドレス。  
右クリックし「Send to Repeater」を選択  
8. リクエスト内で別APIを叩いている箇所のパスを「/admin/delete?username=carlos」のように書き換え、リクエスト送信して攻撃