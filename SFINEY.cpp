#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void show(typename T::iterator x, typename T::iterator y)
{
    for (; x != y; ++x) cout << *x << endl;
}

template <typename T>
void show(T a, T b)
{
    cout << a << ", " << b << endl;
}

template <typename T>
struct has_iterator
{
    template <typename U>
    static char test(typename U::iterator* x);

    template <typename U>
    static long test(U* x);

    static const bool value = sizeof(test<T>(0)) == 1;
};

int main()
{
    show<int>(16, 18);
    cout << has_iterator<int>::value << endl;
    cout << has_iterator<vector<int> >::value << endl;

    return 0;
}