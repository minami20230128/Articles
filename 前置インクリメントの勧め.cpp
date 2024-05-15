//・前置インクリメントの勧め
//イテレータを回すときは後置インクリメント(itr++)より前置インクリメントの方が時間・メモリ効率が良い。
//後置インクリメントだと、インクリメント以前の状態を示す一時オブジェクトを作成してから状態を変更するが、
//前置インクリメントだと一時オブジェクトを生成しないため。

#include <vector>
#include <iostream>

int main()
{
    std::vector<int> nums{1, 2, 3};
    for(auto itr = nums.begin(); itr != nums.end(); itr++)
    {
        std::cout << *itr << std::endl;
    }

    for(auto itr = nums.begin(); itr != nums.end(); ++itr)
    {
        std::cout << *itr << std::endl;
    }

    return 0;
}


