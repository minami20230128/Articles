//・マルチスレッドプログラミングとは
//複数のコアにタスクを割り当てるプログラミングのこと
//通常のプログラミングでmain関数を実行した場合、動作するのは一つのコアのみである
//しかし、マルチスレッドプログラミングによって動作するコアを増やせば、あるタスクを完了するまでの時間を短縮することができる

//Go(goroutine, channel)、Rust(Rayon)など、近年の言語では直接マルチスレッドプログラミングを記述しなくて良いような抽象化レイヤが用意されている


#include <future>
#include <iostream>
#include <thread>

void welcome_back()
{
    std::cout << "おかえり" << std::endl;
}

int main()
{
    std::cout << "ただいま" << std::endl;
    std::thread t(welcome_back);
    std::this_thread::sleep_for(std::chrono::seconds(20));//<-C++の場合、このように何秒間待つかを具体的に書かなければならない
    
    return 0;
}


//package main
//
//import (
//    "fmt"
//    "sync"
//)
//
//func welcomeBack() {
//    fmt.Println("おかえり")
//}
//
//func main() {
//    fmt.Println("ただいま")
//
//    var wg sync.WaitGroup
//    wg.Add(1)
//
//    go func() {
//        welcomeBack()
//        wg.Done()
//    }()
//
//    wg.Wait()
//}

//Goであれば、54行目のWaitGroupのように待ち合わせを行う機能があるなど