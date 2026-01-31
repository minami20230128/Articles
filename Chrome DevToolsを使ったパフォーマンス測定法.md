# Chrome DevToolsを使ったパフォーマンス測定法
- CRUスロットリング  
  画面表示などPCの計算速度に依存しているパフォーマンスを確かめたいときに使う。  
  4x、6x、20xの倍率がある。  
  ![CPUスロットリング](/images/CPUスロットリング.png)
  それ以外の倍率を設定したい場合はProtocol Monitorから設定できる。手順は以下を参照。  
  https://zenn.dev/from_host/articles/2d91bf31807b57  

- ネットワークスロットリング  
  API通信など、通信を伴う動作のパフォーマンスを確かめたいときに使う。