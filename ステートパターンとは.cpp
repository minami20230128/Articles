//・ステートパターンとは
//モノの状態遷移を大量のif文を使わなくても表現できるデザインパターンの一種
//状態クラスを作成し、状態が変化したときにクラスを入れ替えるイメージ

#include <iostream>
#include <string>
#include <map>

class State
{
    public:
    virtual std::pair<int, std::string> drive() = 0;
    virtual std::pair<int, std::string> walk() = 0;
};

class FainState : public State
{
    public:
    FainState()
    {

    };
    std::pair<int, std::string> drive() override
    {
        return std::make_pair(80, "免許証");
    }

    std::pair<int, std::string> walk() override
    {
        return std::make_pair(20, "お弁当");
    }
};

class RainState : public State
{
    public:
    RainState()
    {

    };
    std::pair<int, std::string> drive() override
    {
        return std::make_pair(80, "免許証、傘");
    }

    std::pair<int, std::string> walk() override
    {
        return std::make_pair(80, "傘");
    }
};

class Person
{
    State* state;
    public:
    void change_state(State* p_state)
    {
        this->state = p_state;
    }

    std::pair<int, std::string> drive()
    {
        return this->state->drive();
    }

    std::pair<int, std::string> walk()
    {
        return this->state->drive();
    }
};

int main()
{
    auto person = Person();
    auto p_rain_state = new RainState();
    person.change_state(p_rain_state);
    auto result = person.drive();
    std::cout << "移動距離：" << std::to_string(result.first) << "持ち物" << result.second << std::endl;

    return 0;
}