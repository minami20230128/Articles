// ・goroutineとは
// Go言語におけるプログラムの基本的な構成単位
// main関数はメインゴルーチンと言われる

// 用語
// channel...同時実行するgoroutineをつなぐパイプ
// channelを通して、あるgoroutineから別のgoroutineに値を送信することができる

// 以下は。main関数とwelcomeback関数を非同期実行するコード例

// package main

// import (
//     "fmt"
//     "time"
// )

// func welcomeBack() {
//     fmt.Println("おかえり")
// }

// func main() {
//     fmt.Println("ただいま")
//     go welcomeBack()
//     time.Sleep(50 * time.Millisecond)
// }

// 実行結果:
// (そのまま実行した場合)
// ただいま
// おかえり
// // (23行目を消した場合)
// ただいま

// 23行目の処理がないと、welcomeback関数の前にmain関数が終了してしまうことがわかった
// しかし、毎度終了までの時間を測って指定するのは面倒である
// そこで sync.WaitGroup を使用すれば、複数のgoroutineの終了を待つことができる

package main

import (
    "fmt"
    "sync"
)

func welcomeBack() {
    fmt.Println("おかえり")
}

func main() {
    fmt.Println("ただいま")

    var wg sync.WaitGroup // WaitGroupの生成
    wg.Add(1)             // カウンタをインクリメント

    go func() {
        welcomeBack()
        wg.Done() // カウンタをデクリメント
    }()

    wg.Wait() // mainのゴールールは新規のゴールーチンが完了するのを待つ
}

//実行結果
//ただいま
//おかえり

//goroutineは軽量スレッドであり、通常のスレッドよりも省メモリである
//理由としては、
//・ガードページ(ヒープとスタックが互いに干渉しないように、一スレッドにつき一つ入るメモリ空間)がないこと、
//(代わりに、スレッドに必要なメモリ量を予め計算する処理があるので衝突を避けられる)
//・コンテキストスイッチのコストが低い
//の２つが挙げられる

