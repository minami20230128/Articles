・Syslogとは
System Logging Protocolの略
システムログ・イベントメッセージをSyslogサーバに送るためのプロトコル。
Facility(ログの種類)、Severity(重要度) という概念があり、ログのフィルタリングやルーティングの際に役立つ。
種類は以下の通り。

![facility](/image/syslog_facility.png)
![severity](/image/syslog_sevetiry.png)

Priorityは、8 * Facility + Severityで表される。

*Syslogの改良版
rsyslog
Syslogが通信プロトコルにUDPを採用しているところ、より確実にデータ送信ができるTCPを採用。
フィルタリング機能、暗号化機能も追加された。

syslog-ng
GPL(GNU General Public License)で利用できるオープンソースのソフトウェア。
ログの出力先が設定でき、TCP・UDP両方使用可能。
Syslogとファイル形式の互換性がない。

*syslogd...syslogデーモンのこと

*歴史
1980年頃 Sendmailのプロジェクトの一環として誕生。
2001年頃 RFC3164として文書化され、仕様の標準化が行われる。
2009年頃 RFC5424の発表が行われ、既存機能の強化、拡張性の改善などが行われる。
2010以降 RFC6012、RFC6587など、更に新機能が取りまとめられた文書が発表されている。

そのうち特に標準化を目的としているものは以下の２つ。

RFC3164...ログを転送する「リレー」、ログを受信・収集する「コレクター」、ログを出力する「発信元」の最大3種類の要素から構成される。
メッセージ形式 : BSD形式
「PRI」、TimeStampとHostnameからなる「HEADER」、Message部分の「MSG」の3つの部品からできている。

RFC5424...syslogはメッセージ情報となる「コンテンツ」、それを処理（生成、解釈、格納、転送）する「アプリケーション」、ネットワークでのやり取りを司る「トランスポート」の3つのレイヤーで構成される。
メッセージ形式 : IETF形式
PRIやタイムスタンプMSGIDなどを含んだHEADERと任意で付与された構造化データであるSTRUCTURED-DATA、メッセージ部分であるMSGの3つの部品を含む。

参考：
https://logstorage.com/case/syslog/