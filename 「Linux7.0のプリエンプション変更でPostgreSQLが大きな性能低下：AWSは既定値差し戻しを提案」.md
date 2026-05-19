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
pgbenchについて：  
https://www.postgresql.jp/docs/9.6/pgbench.html

- プリエンプションとは？  
実行状態のタスクをいったん停止して実行可能状態に戻すこと。

- そもそもなぜLinuxの変更がPostgreSQLの速度に影響すると言われているのか？  
PostgreSQLをLinuxサーバ上で実行することが多いから。

- 今回Linuxに入った変更内容  
利用可能なプリエンプションモードの削減。  
もともとPREEMPT_NONE、PREEMPT_VOLUNTARY、PREEMPT_FULL。PREEMPT_LAZYの4種類が使用可能だった。  
PREEMPT_NONE...処理終了までほぼプリエンプションを行わない   
PREEMPT_VOLUNTARY...プリエンプションするとき、プロセスが自発的に処理を中断するまで待つ  
PREEMPT_FULL...カーネルがほぼいつでもプロセス中断可能  
しかし、変更後は実質PREEMPT_LAZYとFULLしか使用できなくなった。  

- ユーザ空間スピンロックとは？  
あるリソースがスレッドによってロックされているとき、別スレッドがCPU側ではなくアプリ側で取得できるかどうか短い期間確認し続けながら待機すること。  
今回のLinux側の変更により、カーネルによるプリエンプションが頻繁に行われるようになったが、同時にもともとPostgreSQL側でもプリエンプションを行っていたのでパフォーマンス低下に繋がってしまった。  