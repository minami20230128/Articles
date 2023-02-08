//・16進文字列とは
//アスキーコードの16進数バージョン

#include <stdio.h>

int main()
{
    printf("10進数アスキーから文字列:");
    const char deci[4] = {67, 65, 84};
    printf("%s ", deci);

    printf("16進数アスキーから文字列:");
    const char hex[4] = {0x43, 0x41, 0x54};
    printf("%s ", hex);

    printf("文字列から10進数アスキー:");
    printf("%d", 'C');
    printf("%d", 'A');
    printf("%d ", 'T');

    printf("文字列から16進数アスキー:");
    printf("%x", 'C');
    printf("%x", 'A');
    printf("%x ", 'T');

    return 0;
}

//を実行すると、
//10進数アスキーから文字列:CAT 16進数アスキーから文字列:CAT 文字列から10進数アスキー:676584 文字列から16進数アスキー:434154
//と表示される
