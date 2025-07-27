# URL設計方法
## HTTPメソッド
GET...リソースの取得
POST...リソースの新規作成
PUT...リソースの変更  
PATCH...リソースの一部変更
DELETE...リソースの消去

## 命名
1. REST APIを作成する場合
    URLはリソースの所在を表し、操作はHTTPメソッドで表される。

    GET /snippets/{id}/
    POST /snippets/{id}/
    PUT /snippets/{id}/
    DELETE /snippets/{id}/

2. Web UIを作成する場合
    URLにも操作を表す言葉を入れたほうがわかりやすい。

    /snippets/new/ 新規作成画面表示
    /snippets/{id}/ 詳細画面表示
    /snippets/{id}/edit/ 編集フォーム表示
    /snippets/<id>/delete/ 削除画面表示

    URLは上のようにしておき、動作は以下のようにHTTPメソッドで分ける。
    フォーム表示...GET  
    フォームへの入力結果をサーバ側に送信...POST

    なお、ブラウザのフォームでは、HTTPメソッドはGETとPOSTしか使えない。  
    （HTMLの<form>要素がこの２つにしか対応していないため）  
    ブラウザでAPIを呼びたい場合はJavaScriptで呼ぶ。
    ```
    fetch('/api/snippets/1/', {
        method: 'DELETE'
    });
    ```