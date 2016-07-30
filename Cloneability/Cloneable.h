#ifndef CLONEABLE_H
#define CLONEABLE_H

class Cloneable {
public:
  Cloneable* Clone() { std::cout << "Cloneable::Clone()\n"; return nullptr; }
};

#endif // CLONEABLE_H
