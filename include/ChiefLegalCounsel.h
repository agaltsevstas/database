#ifndef ChiefLegalCouncel_h
#define ChiefLegalCouncel_h

#include "Employee.h"

class Data;

class ChiefLegalCounsel : public Employee
{
public:
    ChiefLegalCounsel();
    const ChiefLegalCounsel& operator = (const Employee &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // ChiefLegalCouncel_h
