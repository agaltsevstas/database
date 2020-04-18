#ifndef ObjectFactory_h
#define ObjectFactory_h

#include <iostream>
#include <map>

template<class ID, class Base> class ObjectFactory
{
private:
    typedef Base* (*fInstantiator)();
    template<class Derived> static Base* instantiator()
    {
        return new Derived();
    }
    std::map<ID, fInstantiator> classes;
    
public:
    ObjectFactory() {}
    template<class Derived> void add(ID id)
    {
        classes[id] = &instantiator<Derived>;
    }
    fInstantiator get(ID id)
    {
        return classes[id];
    }
};
#endif /* ObjectFactory_h */
