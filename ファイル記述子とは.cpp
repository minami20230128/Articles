// ・ファイル記述子とは
// ファイルへの参照を抽象化したもの。
// プロセスがOSにファイル参照を要求した際、データの通り道に割り振られた番号。

// 直接ファイルを参照しないメリットとしては、
// 1. OSの細かい処理を隠蔽しているためOSに依存しない点
// 2. プログラム上から異なる種類のファイルを単に「ファイル」として同等に扱える点、
// 3. ファイルのアクセス権限を制御しやすい点
// が挙げられる。

// UNIXではあらゆるものをファイルとして扱っているため、いわゆるファイルの読み書きだけでなく様々な場面で登場する。
// *標準入力、標準出力、標準エラー出力
// パイプもファイル記述子が割り当てられる対象である。
// なお、以下のファイル記述子の番号は、それぞれ以下の処理のパイプを指すものとして予約されている。
// 0->標準入力
// 1->標準出力
// 2->標準エラー出力

// *ソケット通信
// よくsock_fdなどと呼ばれるsocket()関数の返り値は、ソケットのファイル記述子である。

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>

int main()
{
    //ファイル記述子を使って書き込み
    std::string str = "test";
    int fd = open("test.txt", O_WRONLY);
    std::cout << fd << std::endl;//*1 ファイル記述子
    write(fd, str.c_str(), strlen(str.c_str()));

    //ファイル記述子ではなく、ファイルのパスを指定して開き、内容を表示する。
    std::ifstream file("test.txt"); 
    std::string line;

    while (std::getline(file, line)) {  
        std::cout << line << std::endl;//*2 ファイルの内容
    }

    return 0;
}

//出力結果：
//3 *1
//test *2