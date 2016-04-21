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
                                                    // MyWidgetMgr wm;
                                                    // OpNewCreator<Widget>* p = &wm;
                                                    // delete p;    // causes: error: calling a protected destructor
                                                    */
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


class A
{
public:
    A() {}
    ~A() {}

};

class B: public A
{
public:
    B() {}
    ~B() {}

};

/*
 * Application Code
 *
 */
int main() {
    typedef WidgetManager< OpNewCreator > MyWidgetMgr;

    {
        MyWidgetMgr wm;
        // MyWidgetMgr* p = new MyWidgetMgr(wm);
        OpNewCreator<Widget>* p = &wm;
        delete p;
    }

}