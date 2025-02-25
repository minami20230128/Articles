//・ディープコピーとシャローコピー
//ディープコピー...オブジェクトとメモリ上の値を両方コピーする。指している先はコピー元と別。
//シャローコピー...オブジェクトのみコピーする。指している先はコピー元と同じなので、コピー先の値を操作するとコピー元も変わる。

//以下はディープコピー、シャローコピーの例。
//person2はperson1のディープコピーなので、person2.nameに「Bob」という値を代入しても、person1.nameはBobに置き換わることはない。
//一方、person3はperson1のシャローコピーなので、person3->nameを置き換えるとperson1.nameも変わる。

#include <string>
#include <iostream>

class Person
{
public:
    std::string name;

    Person(std::string name)
    {
        this->name = name;
    }
};

int main()
{
    auto person1 = Person("Alice");
    //ディープコピー
    auto person2 = person1;
    person2.name = "Bob";
    std::cout << person1.name << std::endl;
    //出力結果
    //Alice

    //シャローコピー
    auto person3 = &person1;
    person3->name = "Bob";
    std::cout << person1.name << std::endl;
    //出力結果
    //Bob

    return 0;
}

//参照渡しやポインタはシャローコピーであり、指している先の値をコピーしない分メモリ消費量が少なく高速。
//しかし意図しないタイミングでの値の変化を引き起こす場合があり、処理内容の理解を難しくする（副作用の発生）ので、望ましくない場面もある。
//パフォーマンス向上を図りたい場面や、意図的にオブジェクト同士の参照先を同じにしたい場合に使うようにしたほうがよさそう。