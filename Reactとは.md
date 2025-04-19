# Reactとは？
## 設計思想
- コンポーネントベース...カプセル化されたコンポーネントを組み合わせて開発する  
コンポーネントとは、ひとまとまりのロジックとビュー。  
（HTML的な見た目を司る部分=JSXと、その動きを司る部分が一体になっているのが特徴）  
カプセル化されているというのは、中身を意識しなくても使えること。　　
（オブジェクト指向と同じ）

- 宣言的UI,,,「どう表示するのか」ではなく「何を表示するのか」を書くこと。  
以下はボタンを押すとカウントが増える処理をReactとjQueryで書いたもの。  
jQueryはまずインデックスを定義し、ボタンが押されたらプラスしている（手続き的）のに対して、
Reactでは「こういうものを返すよ」ということだけを書いているのがわかる。シンプルで可読性も高い。
ちょうどfor文・mapの対比のような感じ。

```
const [count, setCount] = useState(0);

return (
  <div>
    <p>カウント: {count}</p>
    <button onClick={() => setCount(count + 1)}>増やす</button>
  </div>
);

```

同じ処理をjQueryで書いた場合
```
<!-- HTML -->
<div id="app">
  <p id="count">カウント: 0</p>
  <button id="increment">増やす</button>
</div>

<script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
<script>
  // 初期状態
  let count = 0;

  // ボタンにイベントを登録
  $('#increment').on('click', function () {
    count += 1;
    $('#count').text('カウント: ' + count); // DOMを手動で更新
  });
</script>

```

## 得意なこと
- 画面の動的制御  
**useState**で状態管理し、**JSX**(下のHTMLっぽい部分)で条件分岐  
以下はuseStateでtext、setTextの状態を管理している。
ユーザ入力でtextの状態が変わるとJSXを再評価し、入力内容が表示される。
```
const [text, setText] = useState("");

return (
    <>
        <input value={text} onChange={(e) => setText(e.target.value)} />
        <p>入力中のテキスト: {text}</p>
    </>
);
```

- 非同期処理  
**useEffectで**非同期処理を組み込める。
```
useEffect(() => {
    const ws = new WebSocket("wss://...");
    ws.onmessage = (msg) => setMessages((prev) => [...prev, msg.data]);
    return () => ws.close();
}, []);

```