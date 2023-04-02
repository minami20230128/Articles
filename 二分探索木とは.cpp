//・二分探索木とは
//各データにつき2本のノードがあるデータ構造
//より大きいデータを右側、小さいデータを左側のノードに配置する
//リスト構造よりも探索効率が良い

//以下C++での実装例

class Person
{
    public:
    int age;
    Person* left;
    Person* right;

    Person(int age)
    {
        this->age = age;
    }
    void add(Person* person)
    {
        if(person->age > this->right->age)
        {
            this->right = person;//追加する要素のデータが大きければ右のノードに配置
        }
        else
        {
            this->left = person;//そうでなければ左側
        }
    }
};

#include <string>
#include <iostream>

int main()
{
    Person john = Person(15);
    Person charles = Person(30);
    Person margaret = Person(20);

    john.right = &margaret;//先に小さいデータを右側のノードに追加しておく
    john.add(&charles);//その後大きいデータを追加

    std::cout << john.right->age << std::endl;

    return 0;
}

//出力結果：30 なのでcharlesが右側に追加されたことがわかる
//なお、データが片側に偏りすぎている場合、線形リストとあまり探索効率が変わらなくなる
//そのため、できるだけ二分探索木の高さを揃えるようにした「平衡二分探索木」というものもある