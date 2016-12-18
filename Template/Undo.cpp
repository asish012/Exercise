#include <iostream>
#include <string>
#include <cassert>

template <typename T>
class undo {
public:
    undo(T& value) : _value(value), _p(&value) { }
    ~undo() { *_p = _value; }
    private:
        T _value;
        T* _p;
};


int main ()
{

  int x = 10;
  std::string s = "Hello World!";

  {
    undo < int > a ( x );
    undo < std::string > b ( s );

    x = 5;
    s = "Goodbye!";

    // Expected output: "5 Goodbye!";
    std::cout << x << " " << s << "\n";
    assert ( x == 5 );
    assert ( s == "Goodbye!" );
  }

  // Expected output: "10 Hello World!";
  std::cout << x << " " << s << "\n";
  assert ( x == 10 );
  assert ( s == "Hello World!" );

  return 0;
}

