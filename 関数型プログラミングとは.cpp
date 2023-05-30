//・関数型プログラミングとは
//変数の状態がどんどん変化していき、コードの見通しが悪くなる(=副作用)を避けるためのプログラミング手法
//状態が変化するとは、以下のようなことをいう

#include <stdio.h>
#include <iostream>

int add(int& a)
{
    a += 1;
    return a;
}

//add(a)を何度も呼び出すとaの値が変わる=実行結果が変わる=読みづらい

//これを関数型に書き換えると、

int add(int& a)
{
    return a + 1;//aの値は変わらず処理の結果だけが得られる
}

//こうすることでadd(a)を何回行っても結果が同じになり、保守性・可読性が上がる
int main()
{
    int a = 1;
    printf("%d", add(a));
    printf("%d", add(a));//どちらも2になる

//さらに、ラムダ式を使うことで使い捨ての無名関数を作ることが出来る
    int b = 1;
    auto add = [b](int& a){return a + b;};
    std::cout << add(a) << std::endl;
    return 0;
}

