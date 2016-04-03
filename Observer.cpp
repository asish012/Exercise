#include <iostream>


/*
 *  Stock
 */

class Stock
{
public:
    Stock(std::string const& name, int price) : _name(name), _price(price) {}
    virtual ~Stock() {}

    void attach(Investor const* investor);
    void detach(Investor const* investor);
    void notify();

    void setPrice();
    int getPrice() { return _price; }
    std::string getName() { return _name; }

private:
    std::string _name;
    int _price;
    std::vector<Investor*> _investors;
};

void Stock::attach(Investor const* investor) {
    _investors.push_back(investor);
}

void Stock::detach(Investor const* investor) {
    std::vector<Investor const*>::const_iterator i = _investors.find(investor);
    if (i == _investors.end()) { return; }

    _investors.erase(i);
}

void Stock::notify() {
    for (std::vector<Investor const*>::const_iterator i; i != _investors.end(); ++i)
    {
        i->update();
    }
}

class BMW : public Stock
{
public:
    BMW(std::string const& name, int price) : _name(name), _price(price) {}
};

/*
 *  Investor
 */

 class Investor
 {
 public:
    virtual void update() = 0;
 };

 class GlobalInvestments : public Investor
 {
 public:
     GlobalInvestments(std::string const& name, Stock const& stock) : _name(name), _stock(stock) {}
     virtual void update();

 private:
    std::string _name;
    Stock _stock;
 };

 void GlobalInvestments::update() {
    std::cout << _stock.getName() << ": " << _stock.getPrice() << std::endl;
 }


int main() {


    return 0;
}















