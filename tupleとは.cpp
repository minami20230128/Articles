//・tupleとは
//複数の型の変数をまとめるためのクラス
//新しい構造体・クラスを作る代わりに使える
//デメリットとして、クラスを作る場合と比べ名前がついていないので見通しが悪いコードになりやすいことが挙げられる

//・tupleを作った場合

// #include <tuple>
// #include <string>

// std::tuple<std::string, std::string, int> getBook()
// {
//     std::string title = "Anne of Green Gables";
//     std::string author = "Mongomery";
//     int date = 20230128;

//     return std::tuple <std::string, std::string, int> {title, author, date};
// }


// int main()
// {
//     var book = getBook();
//     std::cout << book[0] << std::endl;

//      return 0;
// }

//クラスを利用した場合

#include <string>

class Book
{
    std::string title;
    std::string author;
    int date;
}

Book getBook()
{
    Book book;
    book.title = "Anne of Green Gables";
    book.author = "Mongomery";
    book.date = 20230128;

    return book;
}

int main()
{
    var book = getBook();
    std::cout << book.title << std::endl;

    return 0:
}