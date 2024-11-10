# ・Webサーバを作る

## デフォルトページの表示
1. インスタンスを作成  
Amazon Linux2023を選択  
「インターネットからのHTTPトラフィックを許可」という項目にチェックを入れる

2. nginxをインストール・起動  
sudo dnf install nginx  
sudo systemctl start nginx

3. デフォルトページにアクセス  
http://パブリックIPアドレス にアクセス


[デフォルトページのイメージ](../image/デフォルトページ.png)

## 自作のページを表示
/var/www配下にindex.htmlを作成し表示する。
1. /wwwがないので作成する。
   mkdir /var/www
2. /www内に移動し、index.htmlを作成する
   cd /var/www
   sudo nano index.html
3. /etc/nginx/nginx.confを編集する
   sudo nano /etc/nginx/nginx.conf
   任意の文字を書き込み、保存
4. nginxを再起動
   sudo systemctl restart nginx
5. 自作ページにアクセス
   http://パブリックIPアドレス にアクセス
    以下のように書いた文字列が表示されればOK

[自作ページのイメージ](../image/自作ページ.png)