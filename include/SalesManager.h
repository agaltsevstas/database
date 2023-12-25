#ifndef SalesManager_h
#define SalesManager_h

#include "Employee.h"


class SalesManager final: public Employee
{
public:
    SalesManager() = default;
    void Functional() override;
};

#endif // SalesManager_h
