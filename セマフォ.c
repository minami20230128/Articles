//・セマフォとは
//コンピュータ上の共有資源（ファイルなど）を一度に使用できるプロセスの数を表す数
//プロセスが資源を利用するときはセマフォから1を引き、開放するときは1を足す
//0になると、他のプロセスからは使用できなくなる
//
//これを利用して、たとえば
//「プロセス1がファイルに書き込んだ内容をプロセス2が読み出す」という同期処理を行う時、
//プロセス1がセマフォを減じておくことでプロセス2を待たせることができる

#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/types.h>
#define PJ_ID 1

int main()
{
    int ch;
    const char* PATH = "./test.txt";

    key_t key = ftok(PATH, PJ_ID);

    int semid = semget(key, 1, 0666);
    if(semid  == -1)
    {
        printf("error");

        return -1;
    }

    printf("sid = %d", semid);

    return 0;
}

