#・map関数・reduce関数の使い方
#1. map関数
#イテラブルオブジェクト(listなど)の全要素に変更を反映できる関数

def double(num):
   return num * 2

list = [1, 2, 3, 4, 5]
doubled_list = map(double, list)#一行で全要素にdouble関数を反映させることができる
for num in doubled_list:
    print(num)

#実行結果
#2
#4
#6
#8
#10