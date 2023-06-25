//・再入可能性とは
//関数が複数のプロセスから同時に呼び出されても正しい結果を返せること
//関数を作る際には、コードの独立性を保つためこの再入可能性を持たせるようにするべき

//以下のstrtok関数は再入可能「ではない」

#include <string.h>
#include <stdio.h>

int main()
{
    char str[] = "ab,cde,f,ghi";
    char* p;
    p = strtok(str, ",");
    printf("%s\n", p);//*1

    while(p != NULL)
    {
        p = strtok(NULL, ",");//*2
        if(p != NULL) printf("%s\n", p);
    }

    return 0;
}

//実行結果:
// ab(*1)
// cde(*2)
// f
// ghi

//*2では、同じ関数に同じ引数を渡しているにも関わらず実行ごとに結果が変わっている

//これは*3のように静的な変数を関数内に持っているためであり、
char *strtok(char *str, const char *delimiter)
{
    char  *pbegin, *pend;
    static char  *save = "";//*3

    pbegin = str ? str : save;
    pbegin += strspn(pbegin, delimiter);              
    if (*pbegin == '\0') {
        save = "";
        return (NULL);
    }
    pend = pbegin + strcspn(pbegin, delimiter);       
    if (*pend != '\0')
        *pend++ = '\0';
    save = pend;
    return (pbegin);
}
//静的な変数を使わないようにすれば再入可能性を持たせることができる