//・Mediatorパターンとは
//互いに複雑に関係しあっているコンポーネントを、全て一つのクラスを通じてやり取りするようにすること

//例えば、以下のような画面があったとする

//ユーザ名...1
//┌─------------------------┓
//|                         |
//└------------------------─┘
//
//パスワード...2
//┌─------------------------┓
//|                         |
//└------------------------─┘
//
//ボタン...3
//┌─------┓
//|ログイン|
//└-─-----┘
//
//テキストエリア...4
//┌─-------------------------------┓
//| (入力値が不正な場合メッセージを出す) |
//└-------------------------------─┘
//

//これに加えて性別のチェックボックスが増えただけの、似たフォームを作成予定であり、ロジックを使いまわしたい。
//しかし、ボタンを押した際のロジックが変わってきてしまうため、そのままでは使い回せない

//そこでMediatorパターンを使う。

#include <string>

class Mediator
{
    std::string user_name;
    std::string password;
    void notify(Component sender, std;;string event)
    {
        if(typeid(*sender) == typeid(TextBox) && event == "user_name")
        {
            this->user_name = sender->val;
        }

        if(typeid(*sender) == typeid(TextBox) && event == "password")
        {
            this->password = sender->val;
        }

        if(typeid(*sender) == typeid(Button))
        {
            sender->check(this->user_name, this->password);
        }
    }
};

class Component
{
    private:
    Mediator mediator;
    std::string val;
};

class Button : Component
{
    private:
    std::string user_name = "minami"
    std::string password = "1234"

    bool check(std::string password, std;;string user_name)
    {
        return password == this->password && user_name == this->user_name;
    }
};

class TextBox : Component
{
  
};

class TextArea : Component
{
    
};

class CheckBox : Component
{
    

}