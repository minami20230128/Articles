//・ステートパターンとは
//モノの状態遷移を大量のif文を使わなくても表現できるデザインパターンの一種
//状態クラス...状態の種類ごとに作られる。ある状態のときどうなるか、どのようなときに他の状態に移るかを表す
//Contextクラス...現在どちらの状態なのかを表す。また最初どの状態からスタートするかを設定する

#include <iostream>
#include <string>

class Context;

class State
{
    public:
    virtual void drive(Context* context) = 0;
    virtual void walk(Context* context) = 0;

    protected:
    virtual void _display_parameters() = 0;
};

class FainState;

class Context
{
    State* _state;
    public:
    Context(State* state) : _state(nullptr)
    {
        this->set_state(state);
    }
    void set_state(State* p_state)
    {
        this->_state = p_state;
    }

    void drive()
    {
        this->_state->drive(this);
    }

    void walk()
    {
        this->_state->walk(this);
    }
};

class FainState : public State
{
    public:
    FainState()
    {

    };

    void drive(Context* context) override;
    void walk(Context* context) override;

    private:
    std::string belongings;
    int distance;
    Context* context;

    void _display_parameters() override
    {
         std::cout << "移動距離 : " << this->distance << "持ち物 : " << this->belongings << std::endl;
    }
};

class RainState : public State
{
    public:
    RainState()
    {

    };
    void drive(Context* context) override
    {
        this->belongings = "免許証、傘";
        this->distance = 60;
        this->_display_parameters();
        auto p_fain_state = new FainState();
        context->set_state(p_fain_state);
    }

    void walk(Context* context) override
    {
        this->belongings = "傘";
        this->distance = 80;
        this->_display_parameters();
        auto p_fain_state = new FainState();
        context->set_state(p_fain_state);
    }

    private:
    std::string belongings;
    int distance;

    void _display_parameters() override
    {
         std::cout << "移動距離 : " << this->distance << "持ち物 : " << this->belongings << std::endl;
    }
};

void FainState::drive(Context* context) 
{
    this->belongings = "免許証";
    this->distance = 80;
    this->_display_parameters();
    context->set_state(new RainState());
}

void FainState::walk(Context* context) 
{
    this->belongings = "お弁当";
    this->distance = 20;
    this->_display_parameters();
    context->set_state(new RainState());
}

int main()
{
    auto context = Context(new FainState());
    context.drive();
    context.walk();
    return 0;
}

//walkかdriveを一度実行すると、もう一方の状態に遷移する。
//そのため、
//123行目...晴れ・drive
//124行目...雨・walk
//となる。

//実行結果：
//移動距離 : 80持ち物 : 免許証
//移動距離 : 80持ち物 : 傘