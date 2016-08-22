// VariadicTemplate //
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

template <typename T>
std::string to_string_impl(T const& t) {
  std::stringstream ss;
  ss << t;
  return ss.str();
}

template <typename ... Param>
std::vector<std::string> to_string(Param const& ... param) {
  return { to_string_impl(param)... };
}

int main() {

  std::vector<std::string> res = to_string("hello", 12.6f, '*', "foo");

  for (auto const& i: res) {
    std::cout << i << std::endl;
  }

}
