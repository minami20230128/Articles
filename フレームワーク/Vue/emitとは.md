# $emitとは
子コンポーネントが親コンポーネントのメソッドを発火させるためのもの。  

## 通常の使い方
イベント発火  
```
this.$emit('increment')
```
イベントと親のメソッドを結びつけてる箇所
```
<Child @increment="onIncrement" />
```
親メソッド
```
methods: {
        onIncrement() {
            this.count++
        }
    }
```

## 双方向バインディング
イベント発火
```
<input 
    type="text" 
    :value="email" 
    @input="$emit('update:email', $event.target.value)" 
/>
```

イベントと親のメソッドを結びつけてる箇所
```
:email.sync="user.email"
これは内部的に以下のように展開される。
    :email="user.email"
    @update:email="user.email = $event"
    （この$eventというのは、子が$emitで渡した値のこと）
```

## なぜ必要なのか
データの操作箇所を親コンポーネントだけに絞るため。
仮に子が直接データを操作できる場合、
- 変更箇所を追うのが難しくなる
- 親の構造を知らないと使えないコンポーネントになってしまう
this.$parent.user.email = value