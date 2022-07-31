#ifndef HeadOfProcurement_h
#define HeadOfProcurement_h

#include "Employee.h"

class Data;

class HeadOfProcurement : public Employee
{
public:
    HeadOfProcurement();
    const HeadOfProcurement& operator = (const Employee &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // HeadOfProcurement_h
