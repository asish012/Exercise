#ifndef ISDERIVEDFROM_ONE_H
#define ISDERIVEDFROM_ONE_H

/* USAGE: Runtime validation
 *
 * IsDerivedFrom<DerivedFromClonable, Cloneable> isDerived;
 * isDerived.Is ? std::cout << "Derived\n": std::cout << "Not Derived\n";
 *
 */

#include "Cloneable.h"
#include "HasCloneFunction.h"

template <typename D, typename B>
class IsDerivedFrom {
  class No {};
  class Yes { No no[2]; };

  static Yes test(B*);
  static No test(...);

public:
  enum { Is = sizeof( test(static_cast<D*>(0)) ) == sizeof(Yes) };

};

/* USAGE: Runtime validation
 *
 * IsCloneable<Cloneable> one;    // works
 * IsCloneable<NotClonable> two;  // runtime error
 *
 */

template <typename T>
class IsCloneable {
  bool validate() {
    typedef IsDerivedFrom<T, Cloneable> Result;
    assert(Result::Is);
    return true;
  }

public:
  IsCloneable() {
    assert(validate());
  }
};

#endif // ISDERIVEDFROM_ONE_H
