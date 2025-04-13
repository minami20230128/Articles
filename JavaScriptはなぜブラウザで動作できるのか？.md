# ・JavaScriptはなぜブラウザで動作できるのか？
現状、ブラウザで動作しDOM操作などを行うことができる言語はJavaScriptしかない。
また、JavaScriptはサーバサイドではそのままで動作せず、Node.jsを使用しなければならない。
JavaScriptとその他の言語の違いは何なのだろうか？

## ・JavaScriptがブラウザで動作する理由
ブラウザにJavaScriptエンジンが組み込まれているから。  
JavaScriptエンジン...JavaScriptのコードを実行するためのプログラム。  
以前は単なるインタープリタであったようだが、現在は**JITコンパイル**で機械語に翻訳し、高速に動作するような仕組みを取っている。  

各ブラウザには、以下のようなJavaScriptエンジンが組み込まれている。  
Google Chrome: V8エンジン  
Firefox: SpiderMonkeyエンジン  
Safari: JavaScriptCore（Nitroエンジン）  
Microsoft Edge: Chakraエンジン（以前）やV8エンジン（現在）  

他の言語を動かそうと思った場合、WebAssemblyを用いてwasmモジュールを作成し、JavaScriptから呼び出す方法が現実的。

## ・JavaScriptがサーバサイドで動かない理由
ブラウザ操作に特化した言語なので、必要な処理を行うライブラリがないから。  
Node.jsによりファイルシステム操作やソケット通信などが提供されているため、サーバサイドでの利用が可能になる。
