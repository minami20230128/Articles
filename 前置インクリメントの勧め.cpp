//・前置インクリメントの勧め
//イテレータを回すときは後置インクリメント(itr++)より前置インクリメントの方が時間・メモリ効率が良い。
//後置インクリメントだと、インクリメント以前の状態を示す一時オブジェクトを作成してから状態を変更するが、
//前置インクリメントだと一時オブジェクトを生成しないため。

#include <vector>
#include <iostream>
#include <time.h>

int main()
{
    clock_t start = clock();
    std::vector<int> nums{1, 2, 3};
    for(auto itr = nums.begin(); itr != nums.end(); itr++)
    {
        std::cout << *itr << std::endl;
    }
    clock_t end = clock();

    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    printf("time %lf[ms]\n", time);

    start = clock();
    for(auto itr = nums.begin(); itr != nums.end(); ++itr)
    {
        std::cout << *itr << std::endl;
    }
    end = clock();
    time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    printf("time %lf[ms]\n", time);

    return 0;
}

//出力結果
// 1
// 2
// 3
// time 0.054000[ms]
// 1
// 2
// 3
// time 0.010000[ms]

//このように処理時間に大きな差があることが分かる
