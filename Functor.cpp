// Functor //
#include <iostream>
#include <string>
#include <vector>

#include <memory>
#include <algorithm>

class Message {
    public:
    Message(std::string const& header, std::string const& txt) : _txt(txt), _header(header) 
    {}
    std::string getHeader() const { return _header; }
    std::string getTxt() const { return _txt; }
    
    private:
    std::string _txt;
    std::string _header;
};

class Foo {
  public:
  Foo() {}
  bool operator() (Message const& first, Message const& second) const {
    return first.getHeader() < second.getHeader();
  }
};

int main()
{
  std::vector<std::shared_ptr<Message>> messages;
  messages.push_back(std::make_shared<Message>("foo2", "hello foo2"));
  messages.push_back(std::make_shared<Message>("foo5", "hello foo5"));
  messages.push_back(std::make_shared<Message>("foo3", "hello foo3"));
  messages.push_back(std::make_shared<Message>("foo1", "hello foo1"));
  messages.push_back(std::make_shared<Message>("foo4", "hello foo4"));
  
  Foo const foo;
  //std::sort(messages.begin(), messages.end(), [&](std::shared_ptr<Message> const& left, std::shared_ptr<Message> const& right) { return foo(*left, *right); });
  std::sort(messages.begin(), messages.end(), [&](auto const& left, auto const& right) { return foo(*left, *right); });
  
  for(auto m : messages) {
    std::cout << m->getHeader() << std::endl;
  }
}
