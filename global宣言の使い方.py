#・global宣言の使い方
#グローバル変数を関数の中から宣言したいときに使う

number = 0

def func1():
    number = 10#ローカル変数

def func2():
    global number#global宣言
    number = 10

def main():
    print(number)
    func1()
    print(number)
    func2()
    print(number)

main()

#出力結果：
#0
#0
#10