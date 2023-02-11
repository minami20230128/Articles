//・テンプレートとは
//メソッドを一度の定義で（オーバーロード等せずに）複数の型に対応できるようにしたもの

#include <stdio.h>
int main()
{
    int a = 1;
    int b = 2;
    printf("%d", Add(a, b));
}

template<typename T>
    T Add(T a, T b)
    {
        return a + b;
    }