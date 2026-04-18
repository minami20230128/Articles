# 「Linux 7.0のプリエンプション変更でPostgreSQLが大きな性能低下：AWSは既定値差し戻しを提案」
## 元記事
https://xenospectrum.com/linux-7-postgresql-regression/#google_vignette

## 内容  
Linux7.0のプリエンプションモード変更により、PostgreSQLのパフォーマンスが大幅に低下した。  
AWS EC2上で、変更を含むバージョンと含まないバージョンでベースラインを計測したところ、ほぼ半減していた。

## 疑問点
- どうやって性能比較したのか   
pgbench simple-update（pgbenchと呼ばれるPostgreSQLにベンチマーク試験を行うためのツールのうち、更新系の処理を行うプログラム）を、  
変更を含むバージョンと差し戻し後のバージョンで実行して比較した。
その結果、前者ではTPS（transactions per second、1秒あたりのトランザクション数）が平均50,751.96、後者では平均98,565.86だったので、  
前者は後者の性能の約半分になってしまっていると言える。

- そもそもなぜLinuxの変更がPostgreSQLの速度に影響すると言われているのか？  
PostgreSQLをLinuxサーバ上で実行することが多いから。

- 今回Linuxに入った変更内容

- ユーザ空間スピンロックとは？