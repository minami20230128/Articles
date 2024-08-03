//・演算子を使わず計算する方法
//->ビット演算しよう！！！

//基礎知識

//論理積 (AND): a & b
//論理和 (OR): a | b
//排他的論理和 (XOR): a ^ b
//ビット反転 (NOT): ~a
//左シフト: a << n
//右シフト: a >> n

//a, bは十進数でOK

//a=12, b=25でXOR演算を行う場合、以下のように一度ビットに変換されて、十進数の21が返ってくる。

//  00001100 (12)
//^ 00011001 (25)
//  --------
//  00010101 (21)

bool eql(int a, int b) {
    if(a ^ b) return false;
    return true;
}

bool neq(int a, int b) {
    if(a ^ b) return true;
    return false;
}

//加算
//繰り上がり部分...XOR
//繰り上がらない部分...論理和

//01 ^ 10 = 11
//01 & 10 = 00

//11=3

int add(int a, int b)
{
    if(eql(b, 0)) return a;
    return add(a ^ b, (a & b) << 1);
}

#include <iostream>

int main()
{
    std::cout << add(1, 2) << std::endl;

    return 0;
}