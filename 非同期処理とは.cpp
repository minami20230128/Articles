//・非同期処理とは
//同時に複数の処理を行う処理
//時間のかかる処理と、その処理を中断させるために入力待ちする処理を同時に動かすときなどに使う

//以下、20秒間待つ処理と処理終了の入力を受け付ける処理を同時に行う非同期処理の例

#include <future>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <thread>

std::string WaitCancel()//<-処理1. 入力を受け付ける処理
{
    std::string cancellation;
    std::cin >> cancellation;
    std::terminate();
    return cancellation;
}

std::future<std::string> TestAsync()
{
    std::future<std::string> ret = std::async(std::launch::async, WaitCancel);//処理１をここから呼び出す
    std::this_thread::sleep_for(std::chrono::seconds(20));//<-処理2. 20秒待つ処理

    std::cout << "after wait" << std::endl;//何も入力をせずに20秒経過するとこれが表示される
    return ret;
}

int main()
{
    auto ret = TestAsync();
    std::cout << ret.get() << std::endl;
    return 0;
}