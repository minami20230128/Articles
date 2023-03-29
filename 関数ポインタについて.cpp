// ・関数ポインタについて
// 関数ポインタとは、関数のエントリポインタを指すポインタ

// 型 (ポインタ) (仮引数) = 関数名

// のように宣言する

#include <iostream>

int add(int& a, int& b)
{
    return a + b;
}

int main()
{
    int a = 1;
    int b = 2;
    int (*pAdd)(int&, int&), i;//関数ポインタ(pAdd)、返り値(i)を宣言する
    pAdd = add;
    i = (*pAdd)(a, b);//a,bを渡したときの結果を取得

    std::cout << i << std::endl;

    return 0;
}

//出力結果：3

