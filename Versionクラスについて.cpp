//・Versionクラス(C#)について
//バージョン比較を行うためのクラス
//単純な文字列比較だと、例えば
//20.0.0 と 5.0 を比べたとき 2 < 5 で前者の方が小さいと認識されてしまう
//またカンマが2つあるため、float型に直すことはできない
//
//しかしバージョンクラスであれば正確に比較できる

//・C++で作ってみる

#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main();

class Version
{
    private:
    int major;
    int minor;
    int revision;

    public:
    Version(std::string ver)
    {
        int firstperiod = ver.find(".");
        int secondperiod = ver.rfind(".");
        major = atoi(ver.substr(0, firstperiod).c_str());
        minor = atoi(ver.substr(firstperiod + 1, secondperiod - firstperiod + 1).c_str());
        revision = atoi(ver.substr(secondperiod + 1).c_str());

        //1.50.00

    }

    int compare(Version ver)
    {
        int majorsub = this->major - ver.major;
        int minorsub = this->minor - ver.minor;
        int revisionsub = this->revision - ver.revision;
        
        if(majorsub == 0 && minorsub == 0 && revisionsub == 0)
        {
            return 0;
        }

        if(majorsub > 0)
        {
            return 1;
        }

        if(minorsub > 0)
        {
            return 1;
        }

        if(revisionsub > 0)
        {
            return 1;
        }

        return -1;
    }
};

int main()
{
    std::string str1 = "10.5.0";
    std::string str2 = "5.5.0";
    auto ver1 = Version(str1);
    auto ver2 = Version(str2);

    printf("%d", strcmp(str1.c_str(), str2.c_str()));
    printf("%d", ver1.compare(ver2));
}

//出力　-4、1
//辞書順比較だと5.5.0のほうが大きく、versionクラスだと10.0.0のほうが大きい
