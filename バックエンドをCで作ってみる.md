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
[{"title":1, "start_date":資料作成, "due_date":2025-07-01, "task_condition":2025-07-03, "memo":資料ドラフト作成中, "status":パワポで資料を作成中"},{"title":2, "start_date":会議準備, "due_date":2025-07-02, "task_condition":2025-07-05, "memo":関連資料収集中, "status":必要な資料をまとめる"},{"title":3, "start_date":レビュー対応, "due_date":2025-07-05, "task_condition":2025-07-07, "memo":修正箇所確認済み, "status":コードレビューの指摘を反映"},{"title":4, "start_date":テストケース作成, "due_date":2025-07-03, "task_condition":2025-07-06, "memo":一部未完, "status":単体テストのケースを書いている"},{"title":5, "start_date":資料提出, "due_date":2025-07-06, "task_condition":2025-07-06, "memo":完了, "status":クライアントに提出済み"},{"title":6, "start_date":打ち合わせ調整, "due_date":2025-07-04, "task_condition":2025-07-04, "memo":連絡済み, "status":関係者に連絡済み。日程確定待ち。"},{"title":7, "start_date":進捗報告, "due_date":2025-07-07, "task_condition":2025-07-07, "memo":準備中, "status":上司への週次報告の準備中"}]
```
- Wiresharkで見る

## 感想
- TCPの上にHTTPが乗っていることが実感できた
- Wiresharkで通信をキャッチするところまではできた。スリーウェイハンドシェイクの観測までやりたい。
- コードもうちょっとリファクタリングしたい
- 普段フレームワークで開発するとき、ルーティングやビジネスロジックくらいしか書いていないので、今回全部作ってみて何を隠しているのかがよくわかった。