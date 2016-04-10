#include<iostream>

long long fibonacci(long long index, long long* cache)
{
    if (index <= 1)
    {
        return cache[index] = index;
    }
    return cache[index] != 0 ? cache[index] : cache[index] = fibonacci(index - 2, cache) + fibonacci(index - 1, cache);
}
long long fibonacci(long long index)
{
    if (index <= 1)
    {
        return index;
    }
    return fibonacci(index - 2) + fibonacci(index - 1);
}

long long getFibonacciAtIndex(int index)
{
    long long cache[INT16_MAX] = { 0 };
    return fibonacci(--index, cache);
}
int main(void)
{
    int index;
    std::cin >> index;
    std::cout << getFibonacciAtIndex(index) << std:: endl;
}