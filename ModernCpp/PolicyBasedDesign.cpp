#include <iostream>

/*
 * Creator Policy Classes
 *
 */

template <class T>
struct OpNewCreator {
    static T* Create() {
        return new T;
    }

protected:
    ~OpNewCreator() {}
};

template <class T>
struct MallocCrator {
    static T* Create() {
        void* buff = std::malloc(sizeof(T));
        if (not buff) { return 0; }
        return new(buff) T;
    }
};

template <class T>
struct PrototypeCreator {
    PrototypeCreator(T* obj = 0) : prototype_(obj)
    { }

    T* Create() {
        return prototype_ ? prototype_->Clone() : 0;
    }

    T*   getPrototype()       { return prototype_; }
    void setPrototype(T* obj) { prototype_ = obj;  }

private:
    T* prototype_;

protected:
    ~PrototypeCreator() { delete prototype_; }      /* By making this destructor protected, we disallow dynamic polymorphism.
                                                     * MyWidgetMgr wm;
                                                     * OpNewCreator<Widget>* p = &wm;
                                                     * delete p;    // causes: error: calling a protected destructor */
};


/*
 * Library Code
 *
 */

struct Widget {
};

template < template<class> class CreationPolicy>
class WidgetManager : public CreationPolicy<Widget>
{
public:
    WidgetManager() {}
    ~WidgetManager() {}

    // because of using Template Template Parameter, WidgetManager can create Gadget if needed, with the same CreationPolicy:
    // void doSomething() {
    //    Gadget* g = CreationPolicy<Gadget>().Create();
    // }
};


/*
 * Combining Policy Classes
 *
 */
template<class T,
         template<class> class CheckingPolicy,
         template<class> class ThreadingModel
         >
class SmartPtr : public CheckingPolicy<T>, public ThreadingModel<T> {

public:
    T* operator->() {
        typename ThreadingModel<SmartPtr>::Lock guard(*this);
        CheckingPolicy<T>::Check(_pointee);
        return _pointee;
    }
private:
    T* _pointee;
};

template<class T>
class NoChecking {
    static void Check(T*) {}
};

template<class T>
class EnforceNotNull {
    class NullPointerException : public std::exception {};
    static void Check(T* ptr) {
        if (not ptr) { throw NullPointerException(); }
    }
};

template<class T>
class SingleThreaded {
};


/*
 * Application Code
 *
 */
int main() {
    // Destructor of Policy Classes
    // {
    //     typedef WidgetManager< OpNewCreator > MyWidgetMgr;
    //     MyWidgetMgr wm;
    //     // MyWidgetMgr* p = new MyWidgetMgr(wm);
    //     OpNewCreator<Widget>* p = &wm;
    //     delete p;
    // }

    // Combining Policy Classes
    typedef SmartPtr<Widget, NoChecking, SingleThreaded> WidgetPtr;
    typedef SmartPtr<Widget, EnforceNotNull, SingleThreaded> SafeWidgetPtr;


}