# ・CORSポリシーとは
あるオリジン（後述）で動作しているアプリケーションにおいて、異なるオリジンからのアクセスを制限するWebブラウザの仕組み。

## オリジンとは?  
プロトコル(例えばhttps)
ドメイン(例えば〇〇.co.jp)
ポート(例えば80)
を合わせた概念。

## 異なるオリジンからリソースにアクセスされる危険性とは?  
1. クロスサイトリクエストフォージェリ  
サイトA（https://bank.com）にログイン済みのユーザが、そのまま悪意あるサイトB（https://attacker.com）にアクセス。
BにはAに自動的にアクセスするような仕組みが施されている。（たとえばimg要素のsrc、fetch先に"https://bank.com/transfer?amount=10000&to=attacker"を指定するなど。srcが画像でない場合でも、リクエストは正常に実行される。）
その結果、ユーザの意図しないリクエストが実行されてしまう。この場合だと10000円勝手に送金されてしまう。  
⇒CORSがあると、異なるオリジンの画像などのリソースは取得できないため防止できる。

2. クロスサイトスクリプティング
上記と同様の流れでユーザが悪意あるサイトBにアクセス。
Bにfetch("https://bank.com/user-data")など、DBのAPIにアクセスする処理が仕掛けられている場合、クロスサイトスクリプティングとなる。

