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

std::vector<std::string> to_string() { return {}; }

template <typename P, typename ... Param>
std::vector<std::string> to_string(P const& p, Param const& ... param) {
  std::vector<std::string> results;
  results.push_back( to_string_impl(p) );

  std::vector<std::string> reminder = to_string(param ...);
  results.insert( results.end(), reminder.begin(), reminder.end());

  return results;
}

int main() {

  std::vector<std::string> res = to_string("hello", 12.6f, '*', "world");

  for (auto const& i: res) {
    std::cout << i << std::endl;
  }

}
