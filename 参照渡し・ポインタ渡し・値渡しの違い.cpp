//・参照渡し・ポインタ渡し・値渡しの違い

#include <iostream>

//値渡し...仮引数は実引数のコピーなので、呼び元の値は書き換わらない
void CallByVal(int a)
{
    a += 1;
}

//参照渡し...仮引数と実引数が完全に同じ実体を表すので、呼び元の値が書き換わる
//下記のポインタ渡しの表記をわかりやすくしたもので、
//・ポインタを定義しなくてよい点
//・メモリ破壊の危険性がない点
//がポインタと比較した場合のメリットである
void CallByRef(int& a)
{
    a += 1;
}

//ポインタ渡し...アドレスを引数とし、aを間接参照するので、呼び元の値が書き換わる
void CallByPointer(int* a)
{
    *a += 1;
}

int main()
{
    int a = 1;
    int* pa = &a;

    CallByVal(a);
    std::cout << a << std::endl;
    //1

    CallByPointer(pa);
    std::cout << a << std::endl;
    //2

    CallByRef(a);
    std::cout << a << std::endl;
    //3

    return 0;
}

