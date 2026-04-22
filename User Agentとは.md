# User Agentとは
## 調べようと思ったきっかけ
業務でブラウザの種別による分岐処理を書くことになり、実装方法を調べたが、  
複数のブラウザ名が入っていて素直に取得できない点やそもそもユーザーエージェントとは？という点が気になったから。

Webサイトにアクセスしているソフトウェアのこと（ブラウザなど）。  
これを取得する方法はいくつかある。

1. User-Agent文字列   
ユーザーエージェント自身が自分を説明するために持っている文字列。
JavaScriptではnavigator.userAgentで取得可能。  
ただしこの中には複数のブラウザ名が含まれており、本当はどのブラウザなのかが非常にわかりにくい。  
以下はChrome上での取得結果。
```
Mozilla/5.0 (...) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/146.0.0.0 Safari/537.36
```
これは、かつてWebサイトやアプリケーションの実装に以下のようなコードが含まれていることが多かったため。  
```
if (ua.includes("Mozilla")) { ... }
if (ua.includes("Safari")) { ... }
if (ua.includes("Chrome")) { ... }
```
このような実装があると、新しいブラウザを開発してもサイト側の判定に引っかからず、表示されるはずのものが表示されなかったりする。  
それを防ぐために、複数のブラウザの名前を名乗っている。

2. User-Agent Client Hints  
User-Agent文字列に代わる新しい仕組み。  
User-Agent文字列は、サイトやアプリケーション側がブラウザ名やバージョンによって細かく分岐していることを前提に肥大化してしまった。  
そのため、User-Agent Client Hintsはそれを防ぐように作られている。  
JavaScriptではnavigator.userAgentData.brandsで取得可能。  
これを実行するとブラウザ名が取得できるが、**順不同かつそれ以外の要素も混ざってくる。**
````
[
    {
        "brand": "Chromium", // ...ベースとなったブラウザ名
        "version": "146"
    },
    {
        "brand": "Not-A.Brand",// ...ダミー
        "version": "24"
    },
    {
        "brand": "Google Chrome",// ...ブラウザ名
        "version": "146"
    }
]
````
ダミーが混ざるのはUA Client HintsのGREASEという仕組みのよるもの。  
Webサイト、アプリケーションなどにおいて、順序に依存した実装がなされることを防ぎたいから。  
```
const brand = navigator.userAgentData.brands[0].brand;
if (brand === "Google Chrome") {

}
```
また、最初からブラウザのバージョンの小数点以下の部分は明かさないようになっている。  
これもサイト側にバージョンをハードコードして分岐されるのを防ぐため。