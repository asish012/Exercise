#ifndef HASCLONEFUNCTION_H
#define HASCLONEFUNCTION_H

/* USAGE: Compile time validation
 * Tells you if the template class has "Clone()" function or not
 *
 * HasCloneFunction<Cloneable> isClonable1;
 * HasCloneFunction<NotCloneable> isClonable2;
 *
 */

template <typename T>
class CloneConstraint {
public:
  CloneConstraint() {
    T* (T::*fp)() = &T::Clone;
    std::cout << "CloneConstraint::CloneConstraint()\n";
  }
};

template <typename T>
class HasCloneFunction : CloneConstraint<T> {
public:
  HasCloneFunction() {
    assert(validate());
  }

  bool validate() {
    return true;
  }
};

#endif // HASCLONEFUNCTION_H
