//・フィボナッチ数列
//前の２つの項の和が次の項になっている数列
//人口、株式予想など様々な場面で用いられる

#include <iostream>
#include <vector>

int fibonacci(std::vector<int> answers)
{
    const auto SECOND_IDX = answers.size() - 1;
    const auto FIRST_IDX = answers.size() - 2;

    return answers[FIRST_IDX] + answers[SECOND_IDX];
}

int main()
{
    //最初の2項は配列に入れておく
    std::vector nums{1, 1};

    for(int i = 0; i < 12; i++)
    {
        int answer = fibonacci(nums);
        nums.push_back(answer);
    }

    for(auto&& num : nums)
    {
        std::cout << num << std::endl;
    }
    
    return 0;
}