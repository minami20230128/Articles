# User Agentとは
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

2. User-Agent Client Hints  
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
ダミーが混ざるのはUA Client HintsのGREASEという仕組み。  
Webサイト、アプリケーションなどにおいて、順序に依存した実装がなされることを防ぎたいから。  
```
const brand = navigator.userAgentData.brands[0].brand;
if (brand === "Google Chrome") {

}
```