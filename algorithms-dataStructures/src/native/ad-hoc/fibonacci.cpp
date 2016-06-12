#include<iostream>

/*
 * implementation #1
 */
long long fibonacci2(long long firstPrevious, long long secondPrevious, long long currentIndex, long long index)
{
    if(currentIndex == index) {
        return firstPrevious + secondPrevious;
    }
    return fibonacci2(firstPrevious, (firstPrevious + secondPrevious), ++currentIndex, index);
}
long long getFibonacciAtIndex2(int index)
{
    return fibonacci2(1,0,0,index);
}

/*
 * implementation #2 -> fastest with lookup table
 */

long long fibonacci(long long index, long long* cache)
{
    if (index <= 1)
    {
        return cache[index] = index;
    }
    return cache[index] != 0 ? cache[index] : cache[index] = fibonacci(index - 2, cache) + fibonacci(index - 1, cache);
}
/*
 * implementation #3 -> vanilla and the slowest implementation
 */

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