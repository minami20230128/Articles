# Direct Connect と Site to Site VPNの違い
双方ともオンプレミス環境とAWSを接続するサービスだが、以下の点で違いがある。

準備期間：  
Direct Connect > Site to Site VPN  
Site to Site VPNはVPN導入さえすればすぐに使える。  
Direct Connectは工事が必要なので、数週間かかる。

コスト：  
Direct Connect > Site to Site VPN   
Direct Connectは工事費用が必要なため、Site to Site VPNより費用がかかる。


接続方法：  
Direct Connect...物理専用線  
Site to Site VPN...インターネット回線を利用したVPN  
Site to Site VPNはインターネット回線を利用しているため、他ユーザの影響で混み合うことがある。  
Direct Connectは専用回線のためそういったことはなく、高速なネットワークを実現できる。


