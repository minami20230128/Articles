//リスト構造とは
//各要素が次の要素を指すポインタを持つリスト
//ポインタを通して次の要素にアクセスできる

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

    printf("%s", one->next->title);

    return 0;
}

//出力：second book
