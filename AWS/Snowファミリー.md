# AWS Snowファミリー
AWSから送られてきた物理デバイスを用いて、大容量のデータを移行する手段。  
直接的にネット接続することが難しい場合に使う。

## Snowcone
8TB程度のデータ移行に使用する。

## Snowball
大量のデータをAWSに上げる時に使うデバイス。  
郵送で送られてきたデバイスからデータを格納する。  
デバイスを送り返すと、AWSがS3までデータをセキュアに移行する。  
10PB未満のデータ容量であればこちらの方が良い。  
以下の2つのオプションがある。  
**Snowball Edge Compute Optimized**...機械学習  
**Snowball Edge Storage Optimized**...大容量のデータ移行に適している

## Snowmobile  
Snowballよりさらに大容量のデータを打ち上げる。
トラックで運送されてくるストレージにデータを取り込む。
1台100PBまで対応可能。

