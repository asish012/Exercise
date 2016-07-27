#ifndef ISDERIVEDFROM_COMBINED_H
#define ISDERIVEDFROM_COMBINED_H

#include "Cloneable.h"

template <typename D, typename B>
class IsDerivedFrom_Combined {
  class No {};
  class Yes { No no[2]; };

  static No test(...);
  static Yes test(B* d);

public:
  static void constraints(D const* d) { B const* b = d; }

  enum { Is = sizeof( test(static_cast<D*>(0)) ) == sizeof(Yes) };

  IsDerivedFrom_Combined() {
    void (*fp)(D const*) = &constraints;
  }
};

template <typename T, int>
class IsCloneableImpl {
  // General case: T is not derived from Cloneable
public:
  IsCloneableImpl() { std::cout << "Not Cloneable\n"; }
};

template <typename T>
class IsCloneableImpl<T, 1> {
  // T is derived from Cloneable
public:
  IsCloneableImpl() { std::cout << "Cloneable\n"; }
};

template <typename T>
class IsCloneable {
  IsCloneableImpl<T, IsDerivedFrom_Combined<T, Cloneable>::Is> isCloneable;
};

#endif // ISDERIVEDFROM_COMBINED_H
