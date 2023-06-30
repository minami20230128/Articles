//・再帰可能性とは
//ある関数が自分自身を呼び出せること
//n重のfor文を書きたいとき、ソートや一部のアルゴリズムを書きたいときに使用される

//以下は、0から渡した数字までの総和を求める再帰関数の例

#include <iostream>

int calcsum(int n)
{
    if(n == 0) return 0;//再帰が終わる条件を必ず書く
    return n + calcsum(n - 1);
}

int main()
{
    std::cout << calcsum(5) << std::endl;
    return 0;
}

//実行結果：15