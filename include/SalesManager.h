#ifndef SalesManager_h
#define SalesManager_h

#include "Employee.h"

class Data;

class SalesManager : public Employee
{
public:
    SalesManager();
    const SalesManager& operator = (const Employee &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // SalesManager_h
