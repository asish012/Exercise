#include <iostream>

template <typename T>
class Compare {};

template <>
class Compare<char> {
public:
  static bool eq (char const c1, char const c2) { return c1 == c2; }
  static bool lt (char const c1, char const c2) { return c1 < c2; }
};

// Generic compare function
template <typename T, typename cmp=Compare<char>>
void generic_compare (T const &s1, T const &s2) {

}

// "Partially Specialized" compare function.
// Remember: Member functions can't be partially specialised,
// only free functions can be if the return type remains same
template <typename cmp=Compare<char>>
void generic_compare (std::string const &s1, std::string const &s2) {

  cmp::eq(s1.at(0), s2.at(0)) ? std::cout << "=" : std::cout << "!=";
}

int main()
{
  generic_compare (std::string("Hello"), std::string("Aello"));
  return 0;
}
