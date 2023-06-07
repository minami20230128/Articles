#・map関数・reduce関数の使い方
#1. map関数
#イテラブルオブジェクト(listなど)の全要素に変更を反映できる関数

def double(num):
   return num * 2

numberlist = [1, 2, 3, 4, 5]
doubled_list = map(double, numberlist)#一行で全要素にdouble関数を反映させることができる
print(list(doubled_list))#map関数が返すのはmapオブジェクトなので、list型に直す

#実行結果
#[2, 4, 6, 8, 10]