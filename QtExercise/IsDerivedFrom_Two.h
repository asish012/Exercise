#ifndef ISDERIVEDFROM_TWO_H
#define ISDERIVEDFROM_TWO_H

#include "Cloneable.h"

template <typename D, typename B>
class IsDerivedFrom_Two {
  static void validate(D const* d) {
    B const* b = d;
  }

public:
  IsDerivedFrom_Two() {
    void (*fp)(D const*) = &validate;
  }
};

//template <typename D>
//class IsDerivedFrom_Two<D, void>
//{
//public:
//  IsDerivedFrom_Two() { char* p = (int*)0; /* error */ }
//};

template <typename T>
class IsClonable_Two : IsDerivedFrom_Two<T, Cloneable> {

};

#endif // ISDERIVEDFROM_TWO_H
