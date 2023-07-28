//・キュー構造とは
//先入れ先出し方式(FIFO)を取るデータ構造
//先に入れたデータが先に取り出される
//エンキュー...データを挿入すること
//デキュー...データを削除すること
//印刷機のジョブスケジューリング、ファイルIOなどの非同期データ転送など、古いタスクから順に処理していく場面で使われる

#include <iostream>
#define MAX 10

class Queue
{
    int data[MAX];
    int idx;

    public:
        Queue()
        {
            this->idx = 0;
        }
        void enqueue(int number)
        {
            this->data[this->idx] = number;
            idx += 1;
        }

        int dequeue()
        {
            auto ret = data[0];
            idx -= 1;

            for(int i = 1; i < sizeof(this->data) / sizeof(int) - 1; i++)
            {
                data[i - 1] = data[i];
            }

            return ret;
        }
};

int main()
{
    auto queue = Queue();
    //エンキュー
    queue.enqueue(10);
    queue.enqueue(20);

    //デキュー
    std::cout << queue.dequeue() << std::endl;
    std::cout << queue.dequeue() << std::endl;

    return 0;
}

//出力結果：
//10
//20

//先にエンキューした10が先に取り出されていることがわかる