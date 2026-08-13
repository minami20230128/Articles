# バックエンドをCで作ってみる
## 目的
普段業務で使っているバックエンドフレームワークと、昔実務で関わったTCP/IPのようなネットワーク基礎の知識、ソケット通信などが頭の中で十分に結びついておらず、繋がりを理解したいから。  
今後バックエンドの難しい領域や、インフラ絡みの仕事に関わりたいと思っているので、改めて復習。

## リポジトリ
https://github.com/minami20230128/BackendProgramInC

## やること
以前自作したアプリのバックエンド（https://github.com/minami20230128/ToDoAppBackend）と同等のものをCで作る。（DBのみポスグレで作り直し）
- TCP通信でリクエストを取得
- ルーティング
- DBからデータ読み出し
- 結果をJSON化
- レスポンスを返す
まずは全件取得APIから。

- curlでリクエストを投げる
```
curl http://localhost:3000/api/tasks
```
取得結果：
```
[{"id":"1","title":"資料作成","start_date":"2025-07-01","due_date":"2025-07-03","task_condition":"資料ドラフト作成中","memo":"パワポで資料を作成中","status":"1","created_at":"2026-08-10 18:44:48.336184","updated_at":"2026-08-10 18:44:48.336184"},{"id":"2","title":"会議準備","start_date":"2025-07-02","due_date":"2025-07-05","task_condition":"関連資料収集中","memo":"必要な資料をまとめる","status":"0","created_at":"2026-08-10 18:44:48.336184","updated_at":"2026-08-10 18:44:48.336184"},{"id":"3","title":"レビュー対応","start_date":"2025-07-05","due_date":"2025-07-07","task_condition":"修正箇所確認済み","memo":"コードレビューの指摘を反映","status":"2","created_at":"2026-08-10 18:44:48.336184","updated_at":"2026-08-10 18:44:48.336184"},{"id":"4","title":"テストケース作成","start_date":"2025-07-03","due_date":"2025-07-06","task_condition":"一部未完","memo":"単体テストのケースを書いている","status":"1","created_at":"2026-08-10 18:44:48.336184","updated_at":"2026-08-10 18:44:48.336184"},{"id":"5","title":"資料提出","start_date":"2025-07-06","due_date":"2025-07-06","task_condition":"完了","memo":"クライアントに提出済み","status":"2","created_at":"2026-08-10 18:44:48.336184","updated_at":"2026-08-10 18:44:48.336184"},{"id":"6","title":"打ち合わせ調整","start_date":"2025-07-04","due_date":"2025-07-04","task_condition":"連絡済み","memo":"関係者に連絡済み。日程確定待ち。","status":"0","created_at":"2026-08-10 18:44:48.336184","updated_at":"2026-08-10 18:44:48.336184"},{"id":"7","title":"進捗報告","start_date":"2025-07-07","due_date":"2025-07-07","task_condition":"準備中","memo":"上司への週次報告の準備中","status":"0","created_at":"2026-08-10 18:44:48.336184","updated_at":"2026-08-10 18:44:48.336184"}]
```
- Wiresharkで見る

## コード理解
sockfd...接続待ちするソケット  
create()...ソケットを作成する  
bind()...ソケットを特定のIPアドレスとポートに紐付ける  
htons()...ポート番号をネットワークのバイトオーダーに変換する  
listen()...接続の待受を開始する  
accept()...クライアントからの接続を受信する  
newsockfd...クライアントと接続済みのソケット  
recv()...ソケットからデータを受信する  
close()...接続を切断する  

- なぜ接続待ち用ソケットと接続済みソケットを別で用意するのか
接続待ちするソケットが一つあれば複数のクライアントと接続可能だから。  
sockfdとnew_sockfdは以下のような関係。  
```
sockfd
localhost:3000
状態: LISTEN

new_sockfd
localhost:3000 ←→ localhost:〇〇
状態: ESTABLISHED
```
今回はcurlを一回投げて終わりだが、実際のWebサーバであれば当然複数のクライアントからのリクエストを受け付ける。  
その場合、何度もaccept()にあたる処理が実行され、複数の接続済みソケットが作られる。

## 試したこと
- 間を開けて複数のリクエストを送信する  
以下のクライアントを実行し、少しずつメッセージを送ってサーバとWiresharkで観測した。
```
import socket
import time

s = socket.socket()
s.connect(("127.0.0.1", 3000))

s.sendall(b"GET /api/")
time.sleep(1)

s.sendall(b"tasks HTTP/1.1\r\n")
time.sleep(1)

s.sendall(b"Host: localhost\r\n")
time.sleep(1)

s.sendall(b"\r\n")

print(s.recv(4096))
```

実行結果：  
サーバには「GET /api」のみ表示されたが、Wiresharkには「GET /api/tasks HTTP/1.1」と表示された。  
また、以下のエラーが出た。
```
Traceback (most recent call last):
  File "/Users/hirataminami/Desktop/Articles/client.py", line 13, in <module>
    s.sendall(b"Host: localhost\r\n")
    ~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^
BrokenPipeError: [Errno 32] Broken pipe
```
これは、recvを一回だけ実行して次に進んでしまったから。  
実用サーバにはリクエストが完成するまで読む（ただ、一定時間完成しなかったら閉じる）という仕組みがある。


## 感想
- TCPの上にHTTPが乗っていることが実感できた
- Wiresharkで通信をキャッチするところまではできた。スリーウェイハンドシェイクの観測までやりたい。
- コードもうちょっとリファクタリングしたい
- 普段フレームワークで開発するとき、ルーティングやビジネスロジックくらいしか書いていないので、今回全部作ってみて何を隠しているのかがよくわかった。