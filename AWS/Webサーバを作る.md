# ・Webサーバを作る

## デフォルトページ表示まで
1. インスタンスを作成  
Amazon Linux2023を選択  
「インターネットからのHTTPトラフィックを許可」という項目にチェックを入れる

2. nginxをインストール・起動  
sudo dnf install nginx  
sudo systemctl start nginx

3. デフォルトページにアクセス  
http://パブリックIPアドレス にアクセス


[デフォルトページのイメージ](../image/デフォルトページ.png)