# JavaScriptでよく使う高階関数まとめ
- map()  
全要素に同じコールバックを適用した結果を返す。  
```
const array = [1, 4, 9, 16];
const mapped = array.map((x) => x * 2);
```
- filter()  
条件に当てはまる要素のみ抜き出す。  
```
const words = ["spray", "elite", "exuberant", "destruction", "present"];
const result = words.filter((word) => word.length > 6);
```
- flat()  
配列の次元を一つ下げる。2次元配列を1次元配列にするなど。  
```
const arr1 = [0, 1, 2, [3, 4]];
console.log(arr1.flat());
// 予想される結果: Array [0, 1, 2, 3, 4]
```
- flatMap()  
flat()+map()。各要素のコールバック適用結果を配列化したあと。次元を下げる。 
下記のように、コールバックの結果が配列で返るが、すべて一つの配列の要素にしたい場合などに使用する。
```
const arr = ["1", "2\n3", "1"];
const result = arr.flatMap(a => a.split("\n"));
console.log(result);
// 予想される結果: Array [1, 2, 2, 1]
```
- reduce()  
全要素に順番に同じ処理を適用していく。
```
const array = [1, 2, 3, 4];
const initialValue = 0;
const sumWithInitial = array.reduce(
  (accumulator, currentValue) => accumulator + currentValue,
  initialValue,
);
console.log(sumWithInitial);
// 予想される結果: 10
```
- forEach()  
全要素に同じコールバックを適用する。  
mapと異なり、配列の要素を直接変更する。   
```
const array = ["a", "b", "c"];
array.forEach((element) => console.log(element));
```
- find()  
条件を満たす一番最初の要素のみを返す。  
```
const array = [5, 12, 8, 130, 44];
const found = array.find((element) => element > 10);
```
- findIndex()  
条件を満たす要素の一番最初の要素のインデックスを返す。  
```
const array = [5, 12, 8, 130, 44];
const isLargeNumber = (element) => element > 13;
```
- some()  
条件を満たす要素が一つでもあればtrue、なければfalseを返す。  
```
const array = [1, 2, 3, 4, 5];
const even = (element) => element % 2 === 0;
console.log(array.some(even));
```
- every()  
すべての要素が条件を満たす場合trueを返す。  
```
const isBelowThreshold = (currentValue) => currentValue < 40;
const array1 = [1, 30, 39, 29, 10, 13];
console.log(array1.every(isBelowThreshold));
```
- includes()  
特定の要素が含まれている場合trueを返す。  
```
const array = [1, 2, 3];
console.log(array.includes(2));
```
- indexOf()  
String型を引数に取り、指定した部分文字列が初めて出現したインデックスを返す。  
```
const beasts = ["ant", "bison", "camel", "duck", "bison"];
console.log(beasts.indexOf("bison"));
```
- sort()  
元の配列をソートし、配列の参照を返す。  
元の配列をソートしたくない場合は、toSorted()を使用する。
```
const months = ["March", "Jan", "Feb", "Dec"];
months.sort();
```
- Object.keys()  
オブジェクトのプロパティ名の配列を返す。
- Object.value()  
オブジェクトのプロパティ値の配列を返す。
- Object.entries()  
オブジェクトのプロパティのキー名：値のペアを返す。