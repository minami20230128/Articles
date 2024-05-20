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