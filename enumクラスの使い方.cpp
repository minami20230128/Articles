//・enumクラスの使い方・利点

#include <string>
#include <vector>

std::vector<std::string> v_Dogs = 
{
    "bulldog",
    "shepherd",
    "retriever".
    "poodle"
};

enum class e_Dogs
{
    bulldog,
    shepherd,
    retriever.
    poodle
};

int main()
{
    std::string dog1 = v_Dogs[1];
    switch(dog1)
    {
        case "bulldog":
        {
            break;
        }
        case "Shephard"//<-単純な配列の場合、このようなミスタイプがあってもエラーにならないので自分で気づくしかない
        {
            break;
        }
    }

    e_Dogs dog2 = e_Dogs::retriever;
    switch(dog2)
    {
        case e_Dogs::bulldog:
        {
            break;
        }
        case e_Dogs::Shepherd://<-ミスタイプをするとエラーになる
        {
            break;
        }
    }
}