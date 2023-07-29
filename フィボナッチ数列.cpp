//・フィボナッチ数列
//前の２つの項の和が次の項になっている数列
//人口、株式予想など様々な場面で用いられる

#include <iostream>
#include <vector>

std::vector<int> fibonacci(std::vector<int> answers, int count)
{
    auto idx = answers.size();
    std::cout << "idx = " << idx << std::endl;
    if(idx < 2) return answers;
    while(count > 0)
    {
        answers.push_back(answers[idx] + answers[idx - 1]);//最後尾に前の２つの項の合計を格納
        std::cout << "answer = " << (answers[idx] + answers[idx - 1]) << std::endl;//2
        return fibonacci(answers, count - 1);
    }

    if(count == 0) return answers;
}

int main()
{
    //最初の2項は配列に入れておく
    std::vector<int> nums{1, 1};
    auto answers = fibonacci(nums, 1);

    for(auto&& answer : answers)
    {
        std::cout << answer << std::endl;//1,1,1?
    }
    
    return 0;
}