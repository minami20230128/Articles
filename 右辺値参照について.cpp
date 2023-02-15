//c++ &&, &, 何もついてないときの違い
//&->左辺値参照
//&&->右辺値参照
//何もついてないとき->値をコピー

//右辺値参照は、右辺値（代入などに使われる一時的な値、一時オブジェクトのこと）しか代入できないようにすること

#include <iostream>

int add(int a, int b)
{
    return (a+b);
}

int radd(int&& a, int&& b)//右辺値しか渡せない関数
{
    return (a+b);
}

int main()
{
    int a = 1;
    int b = 2;

    //これだとコピーが発生する
    auto result = add(a, b);
    std::cout << result << std::endl;

    //直接右辺値を渡せばコピーが発生しない
    result = radd(1, 2);
    std::cout << result << std::endl;

    //これは右辺値ではないのでエラーになる
    //result = radd(a, b);

    //左辺値を右辺値にキャストするとエラーが起きない
    result = radd(std::move(a), std::move(b));
    std::cout << result << std::endl;

    return 0;
}

//ただし、右辺値参照したあとの変数の利用は保証されない（要追加調査）
//このようなデメリットを鑑みて、JavaのString型などは変更不能(immutable)になっている

// class Main
// {
//     public static void main(String[] args)
//     {
//          String a = "あいうえお";
//          String b = a;
//          a = "かきくけこ";
//          
//          if(a == b)//参照値が同じならtrue
//          {
//              System.out.println("同じ");
//          }
//          else
//          {
//              System.out.println("違う");
//          }
//     }
// }

//出力結果：違う
//そのため、こうした変数の再代入を繰り返すとメモリを圧迫する



