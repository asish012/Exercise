#include <iostream>
#include <vector>

template <typename T>
struct iterator_traits {
    typedef typename T::value_type          value_type;
    typedef typename T::reference           reference;
    typedef typename T::pointer             pointer;
    typedef typename T::difference_type     difference_type;
    typedef typename T::iterator_category   iterator_category;
};

template<typename T>
struct iterator_traits<T*>
{
    typedef T value_type;
};

template <typename T>
void iterator_swap(T first, T second) {
    typename iterator_traits<T>::value_type temp = *first;
    *first = *second;
    *second = temp;
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

    for(auto i: v) {
        std::cout << i << std::endl;
    }


    return 0;
}