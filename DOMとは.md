# DOMとは
Document Object Modelの略。  
HTMLのような文書をメモリ内に木構造で表現したもの、またはそれを扱うAPI。  

- フレームワークを使用した開発において、DOMの直接操作が推奨されないのはなぜか？  
フレームワークでの値と実際のDOMの値が一致しなくなるから。  
一時的に直接操作した結果が反映されても、すぐにフレームワーク上の値で置き換わってしまったり、不整合を起こしてバグの原因になったりする。  
基本的にフレームワークはDOMを一元管理する責任を負うものなので、フレームワークを使って操作するべき。

以下は、Vueにおいて<p>というDOMの中身をVueの機能と直接操作の両方で書き換えたもの。
```
<script>
export default {
  data() {
    return {
      count: 0
    }
  },
  mounted() {
    document.querySelector('p').textContent = '999' //直接操作
  },
  methods: {
    inc() { //Vueの機能で操作
      this.count++
    }
  }
}
</script>

<template>
  <p>{{ count }}</p>
  <button @click="inc">+1</button>
</template>

```
表示結果：  
初期表示直後は「999」と表示されているが、  
ボタンクリック後は1から順に増えていく。