#include <iostream>
#include <vector>
#include <assert.h>

#include "Cloneable.h"
//#include "HasCloneFunction.h"
//#include "IsDerivedFrom_One.h"
#include "IsDerivedFrom_Two.h"
#include "IsDerivedFrom_Combined.h"

class NotCloneable {};

class DerivedFromClonable : public Cloneable {};

int main()
{
//  {
//    HasCloneFunction<Cloneable> isClonable;
//    HasCloneFunction<NotCloneable> isClonable2;
//  }

//  {
//    IsDerivedFrom<DerivedFromClonable, Cloneable> isDerived;
//    isDerived.Is ? std::cout << "Derived\n": std::cout << "Not Derived\n";
//  }

//  {
//    IsCloneable<Cloneable> one;
//  }

//  {
//    IsClonable_Two<Cloneable> isDerived;
//    IsClonable_Two<NotCloneable> isNotDerived;
//  }

  {
    IsCloneable<NotCloneable> isCloneable;
    IsCloneable<Cloneable> isNotCloneable;
  }

  return 0;
}
