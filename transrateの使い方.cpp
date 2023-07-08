//・std::transformの使い方
//C++のtransformは、配列の複数の要素に同じ処理をするときに使う関数（map関数のようなもの）
//以下は文字列のうち、指定した箇所だけ大文字にするコード

#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>

int main(){
    int a, b;
    std::cin >> a;
    std::cin >> b;
    std::cin.ignore(); 
    
    std::string str ="";
    std::getline(std::cin, str);
    
    std::transform(str.begin() + a - 1, str.begin() + b, str.begin() + a - 1, ::toupper);
    //どこからどこまで処理したいか、その結果をどこに反映したいかイテレータで指定
    std::cout << str << std::endl;
    
    return 0;
}

//入力：
//2
//6
//this is a pen

//出力結果：
//tHIS Is a pen