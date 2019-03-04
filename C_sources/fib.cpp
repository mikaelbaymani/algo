#include<iostream>
#include<cstdint>
#include<unordered_map>
std::unordered_map<uint64_t, uint64_t> memo;

uint64_t fib(uint64_t n)
{
    if(n == 0)
    {
        return 1;
    }
    if(n == 1)
    {
        return 1;
    }

    auto search = memo.find(n);
    if(search != memo.end())
    {
        return search->second;
    }

    uint64_t fib1 = fib(n-1);
    uint64_t fib2 = fib(n-2);
    uint64_t sum = fib1 + fib2;

    if(sum < fib1)
    {
        return 0;
    }

    memo[n] = sum;
    return sum;
}

int main(int argc, char* argv)
{
    std::cout << fib(93) << std::endl;
    return 0;
}
