//リスト構造とは
//各要素が次の要素を指すポインタを持つリスト
//ポインタを通して次の要素にアクセスできる

//以下、Book型のリスト構造で1.次のデータのtitleを表示、2.データを插入、3.データを削除するコード

#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct Book
    {
        char* title;
        struct Book* next;
    };

    struct Book* one;
    one = (struct Book*)malloc(sizeof(struct Book));
    one->title = (char*)malloc(20);
    one->title="first book";

    struct Book* two;
    two = (struct Book*)malloc(sizeof(struct Book));
    two->title = (char*)malloc(20);
    two->title="second book";

    one->next = two;

    printf("%s", one->next->title);//1.次のデータのtitleを表示

    struct Book* three;
    three=(struct Book*)malloc(sizeof(struct Book));
    three->title = (char*)malloc(20);
    three->title ="third book";

    //2.データを插入
    one->next = three;//前のデータのポインタ部を挿入したいデータのポインタに置き換える
    three->next = two;//挿入したデータのポインタ部に後ろのデータのポインタを渡す

    printf("%s", one->next->title);

    //3.データを削除する
    one->next = two;//削除したいデータの前のデータのポインタ部を、後ろのデータのポインタに置き換える

    printf("%s", one->next->title);

    free(one);
    free(two);

    return 0;
}

//出力：
//second book
//third book
//second book
