//・エラトステネスの篩とは
//N以下の素数を求めるためのアルゴリズム

#include <iostream>
#include <vector>

std::vector<bool> eratosthenes(int N)
{
    std::vector<bool> is_prime(N + 1, true);

    //0, 1は素数ではないので、はじめから除外
    is_prime[0] = false;
    is_prime[1] = false;

    for(int i = 2; i <= N; ++i)
    {
        if(!is_prime[i]) continue;

        //iの倍数を素数から除外
        for(int j = i * 2; j <= N; j+= i)
        {
            is_prime[j] = false;
        }
    }

    return is_prime;
}

int main()
{
    int N = 50;
    
    auto is_prime = eratosthenes(N);

    for(int k = 0; k <= N; k++)
    {
        if(is_prime[k]) std::cout << k << std::endl;
    }
        
    return 0;
}

//出力結果
//2
//3
//5
//7
//11
//13
//17
//19
//23
//29
//31
//37
//41
//43
//47