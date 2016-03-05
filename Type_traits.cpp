#include <iostream>
#include <vector>

template <typename T>
struct iterator_traits {
    typedef typename T::value_type value_type;
};

template<typename T>
struct iterator_traits<T*>
{
    typedef T value_type;
};

template <typename T>
void iterator_swap(T first, T second) {
    std::cout << "before :" << *first << " " << *second << std::endl;

    typename iterator_traits<T>::value_type temp = *first;
    *first = *second;
    *second = temp;

    std::cout << "after  :" << *first << " " << *second << std::endl;
}


int main() {
    std::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    int x(10), y(20);
    int *a = &x, *b = &y;

    iterator_swap(a, b);
    iterator_swap(v.begin(), v.end() - 1);


    return 0;
}