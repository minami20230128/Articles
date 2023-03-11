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
        major = ver.substr(0, firstperiod);
        minor = ver.substr(firstperiod + 1, secondperiod - firstperiod);
        revision = ver.substr(secondperiod);
    }

    int compare(Version ver)
    {
        int result = 0;
        if((result = strcmp(this->major.c_str(), ver.major.c_str())) != 0)
        {
            return result;
        }

        if((result = strcmp(this->minor.c_str(), ver.minor.c_str())) != 0)
        {
            return result;
        }

        return strcmp(this->revision.c_str(), ver.revision.c_str());
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


