# ・REST APIとは
REST（REpresentational State Transfer）というWebシステムの設計思想に則ったAPI  
RESTには以下の4つの原則がある

1. 統一インターフェース  
あらかじめ定義・共有された方式でデータのやりとりをすること。
HTTPメソッドで送受信を行う、JSONを使用するなど

2. アドレス可能性  
すべての情報が一意なURI（識別子）を持っていること。
![RESTAPIのURIの例](/images/RESTAPIのURIの例.png)

3. 接続性  
やりとりする情報にハイパーリンクを含められること。

4. ステートレス性  
状態がない＝やりとりが一回で完結すること。
