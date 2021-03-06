#include <iostream>
#include <assert.h>

template <typename T>
class HasClone
{
public:
    HasClone() {
        T* (T::*test)() const = &T::Clone;
        std::cout << "HasClone::HasClone()\n";
    }
};

template <typename T>
class C : HasClone<T> {

public:
    C() {
        assert(validate());
        std::cout << "C::C()\n";
    }

private:
    bool validate() const {
        // T* (T::*check_cloneable)() const = &T::Clone;
        std::cout << "C::validate()\n";
        return true;
    }
};

class Cloneable
{
public:
    Cloneable();
    ~Cloneable();

    Cloneable* Clone() const { std::cout << "Cloneable::Clone()\n"; return nullptr; }
};

int main() {
    C<Cloneable> c;

    return 0;
}