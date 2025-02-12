//・スタックとヒープの違い
//スタック領域...LIFO形式でデータを管理。関数など使用範囲を抜けたら自動的に開放される。
//ヒープ領域...動的なメモリ確保に使われる領域。スタックのようなデータ構造を持たず、好きに確保・開放できる。

//C++では、スタックとヒープをそれぞれ使った2つのインスタンス作成方法がある。

#include <string>
#include <iostream>

class Person
{
    std::string name;

public:
    Person(std::string name)
    {
        this->name = name;
    }

    ~Person(){}

    std::string get_name()
    {
        return this->name;
    }
};

int main()
{
    //こっちがヒープを使った方法
    //newはメモリをヒープ上に確保し、アドレスを返すのでポインタが返される。
    Person* person1 = new Person("Alice");
    //こっちがスタックを使った方法
    //スタックに実体を作成し、返す
    Person person2 = Person("Bob");

    std::cout << person1->get_name() << std::endl;
    std::cout << person2.get_name() << std::endl;

    //ヒープを使って確保したインスタンスは手動で開放する必要があるが、スタックの方は勝手に解放されるので気にしなくて良い。
    delete person1;

    return 0;
}

//Javaなどガベージコレクションのある言語では、newを使ってヒープ上に確保したメモリは自動的に解放される。
//ただし、以下の事項に気をつける必要がある。
//・ガベージコレクションが走るタイミングは読めない
//  ->どうしても意図したタイミングで開放したい場合は、オブジェクトにnullを代入する
//・staticのメンバ変数はプログラム終了まで残り続ける