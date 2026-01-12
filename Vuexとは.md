# Vuexとは
Vue2で使われる状態管理ライブラリ。  
状態管理ライブラリとは、アプリケーション全体にとって意味のある情報を管理するための仕組み（ログイン後に一度だけ取得するデータ、入力途中のデータ、カートの中身、言語設定etc）。  
Vueでいうと、コンポーネント間でpropsを通じて情報の受け渡しを行わなくていいように一括管理するためのもの。  

## ストア
Vuexにおける、状態（state）を保持するコンテナ。  
通常アプリケーションごとに一つしか存在せず、"信頼できる唯一の情報源 (single source of truth)"として機能する。  
this.$store.〇〇でどのコンポーネントからも参照可能。

1. ゲッター
ストアの状態を算出したいときに使用するもの。  
stateを第一引数に取る。
```
const store = createStore({
  state: {
    todos: [
      { id: 1, text: '...', done: true },
      { id: 2, text: '...', done: false }
    ]
  },
  getters: {
    doneTodos (state) {
      return state.todos.filter(todo => todo.done)
    }
  }
})
```

2. ミューテーション
ストアの状態を変更したいときに使用する。  
変更経路が追えなくなるため、必ずこのミューテーションを通して変更する。

3. アクション
ミューテーションを発火する。  

```
const store = createStore({
    state: {
        count: 1
    },
    mutations: { // ミューテーション
        increment(state) {
            state.count++
        }
    }
    actions: { // アクション
        increment(conext) {
            context.commit('increment')
        }
    }
})
```
4. モジュール
ストアをいくつかの部品に分けたもの。
```
const moduleA = {
  state: () => ({ ... }),
  mutations: { ... },
  actions: { ... },
  getters: { ... }
}

const moduleB = {
  state: () => ({ ... }),
  mutations: { ... },
  actions: { ... }
}

const store = createStore({
  modules: {
    a: moduleA,
    b: moduleB
  }
})
```