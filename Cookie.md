# ・Cookieとは  
ブラウザに保存されるkey-value形式の情報などのこと

## 実際の通信におけるCookieの使われ方
### Cookieの作成
1. サーバがSet-Cookie HTTPレスポンスヘッダーを送る  
例：  
`Set-Cookie: a=apple; path=/`  
これによりa=appleという情報を記録したCookieが作成される

### 作成したCookieの読み取り

2. HTTPリクエストの際、ブラウザがCookie HTTPリクエストヘッダーでCookieの情報を送る
3. サーバがCookieを読み取る

Cookie情報はHTTP通信によってサーバに送られるため、HTTPSで暗号化されている場合、Cookie情報を参照する必要のあるサーバは復号機能を持っている必要がある

