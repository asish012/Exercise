/* Template Template Parameter:
 * This construct means that the argument must itself be a template, not a class constructed from template.
 * In the following example, the name A of the template parameter for a template template parameter can be omitted,
 * because there is no way that it can be used.
 *
 *     template <class T>
 *     struct MyStruct_1 {
 *         T t;
 *     };
 *
 *     template <template<class A> class T>          // or we could write: template <template<class> class T>
 *     struct MyStruct_2 {
 *         T<int> var;
 *     };
 *
 *     int main() {
 *         MyStruct_2<MyStruct_1> mystr2;
 *     }
 *
 *
 * [ More Details ]
 * In the following example we name the first parameter of the inner template Seq (with the name U)
 * because the allocators in the standard sequences must themselves be parameterized with the same type as the contained objects in the sequence.
 *
 *     template<class T, template<class U, class = allocator<U> > class Seq
 *     struct MyStruct {
 *         Seq<T> seq;                               // Default of allocator<T> applied implicitly
 *     };
 *
 *     int main() {
 *         MyStruct<int, std::vector> mystr2;
 *     }
 *
 *
 */

#include <cstddef>
#include <iostream>
using namespace std;

template<class T>
class Array {
    // A simple, expandable sequence
    enum { INIT = 10 };
    T* data;
    size_t capacity;
    size_t count;
public:
    Array() {
        count = 0;
        data = new T[capacity = INIT];
    }
    ~Array() { delete [] data; }
    void push_back(const T& t) {
        if(count == capacity) {
            // Grow underlying array
            size_t newCap = 2 * capacity;
            T* newData = new T[newCap];
            for(size_t i = 0; i < count; ++i)
                newData[i] = data[i];
            delete [] data;
            data = newData;
            capacity = newCap;
        }
        data[count++] = t;
    }
    void pop_back() {
        if(count > 0)
            --count;
    }
    T* begin() { return data; }
    T* end() { return data + count; }
};

template<class T, template<class> class Seq>
class Container {
    Seq<T> seq;
public:
    void append(const T& t) { seq.push_back(t); }
    T* begin() { return seq.begin(); }
    T* end() { return seq.end(); }
};

int main() {
    Container<int, Array> container;
    container.append(1);
    container.append(2);
    int* p = container.begin();
    while(p != container.end())
        cout << *p++ << endl;
}
