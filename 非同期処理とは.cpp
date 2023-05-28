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

//用語
//・プロセス
//UNIXにおける実行中のプログラムのこと
//〇〇.exeなど
//メモリを共有しないので競合を起こさない

//・スレッド
//アプリケーション内の処理の単位
//ボタンを押す-データを取得する->WEBページを表示する　のような一連の処理の流れ
//メモリを共有するためデッドロックを起こす可能性がある

//シグナル
//異常が発生したときなどにプロセスを終了させ、所定の動作を行わせる非同期処理の一種
//SIGINT...Ctrl+Cによるユーザの割り込み
//SIGFPE...0での除算など、不正な演算が行われた　などがある

//シグナルが発生すると、カーネルが一度保持する
//受信側のプロセスが処理する準備ができたら、シグナルの番号を受け取り処理する(=handle)