#ifndef ObjectFactory_h
#define ObjectFactory_h

#include <iostream>
#include <map>

using namespace std;

template<class ID, class Base> class ObjectFactory
{
private:
    typedef Base* (*fInstantiator)();
    template<class Derived> static Base* instantiator()
    {
        return new Derived();
    }
    map<ID,fInstantiator> classes_;
    
public:
    ObjectFactory() {}
    template<class Derived> void add(ID id)
    {
        classes_[id] = &instantiator<Derived>;
    }
    fInstantiator get(ID id)
    {
        return classes_[id];
    }
    
};
#endif /* ObjectFactory_h */
