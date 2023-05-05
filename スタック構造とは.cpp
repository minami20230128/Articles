//・スタックとは
//後入れ先出し方式(LIFO)のデータ構造
//あとに入れたデータが先に取り出される構造になっている
//プッシュ...データを挿入すること
//ポップ...データを取り出すこと

#include <iostream>
#include <stdlib.h>
#define MAX 10

class Stack
{
    int data[MAX];
    int top;

    public:
        void push(int number)
        {
            this->top += 1;
            this->data[this->top] = number;
        }

        int pop()
        {
            this->top -= 1;
            return this->data[top];
        }
};

int main()
{
    Stack* stack;
    stack = (struct Stack*) malloc(sizeof(struct Stack));

    //プッシュ
    stack->push(10);
    stack->push(20);

    //ポップ
    std::cout << stack->pop() << std::endl;
    std::cout << stack->pop() << std::endl;

    return 0;
}

