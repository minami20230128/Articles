# 「Linux 7.0のプリエンプション変更でPostgreSQLが大きな性能低下：AWSは既定値差し戻しを提案」
## 元記事
https://xenospectrum.com/linux-7-postgresql-regression/#google_vignette

## 内容  
Linux7.0のプリエンプションモード変更により、PostgreSQLのパフォーマンスが大幅に低下した。  
AWS EC2上で、変更を含むバージョンと含まないバージョンでベースラインを計測したところ、ほぼ半減していた。

## 疑問点
- ベースラインとは？  

- そもそもなぜLinuxの変更がPostgreSQLの速度に影響すると言われているのか？  
PostgreSQLをLinuxサーバ上で実行することが多いから。

- 今回Linuxに入った変更内容

- ユーザ空間スピンロックとは？