#include <iostream>
#include <thread>
#include <future>

int factorial(std::future<int> &&fu)
{
    int number = fu.get();
    if (number <= 1) { return number; }

    int result = 1;
    for (; number > 1; --number) {
        result *= number;
    }

    return result;
}

int main()
{
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    std::future<int> result = std::async(std::launch::async, factorial, std::move(future));
    promise.set_value(3);
    int x = result.get();
    std::cout << "Answer::" << x << '\n';

    return 0;
}
