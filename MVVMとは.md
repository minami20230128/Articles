・MVVMとは
Model、View、ViewModelの3層から成るシステム構成。
Model...DBとのやり取り、ビジネスロジックなど
ViewModel...ModelのデータをViewに表示させるために成形する、
またはViewでユーザが行った変更をModelに反映させる
View...UI部分。ユーザから操作をする

データバインディング...ViewとViewModelを結びつけるために提供されている仕組みのこと
![データバインディングの例](/image/データバインディングの例.png)

ViewからもModelからも変更があるようなシステムを作る場合、MVCよりもMVVMを使った方が良い。