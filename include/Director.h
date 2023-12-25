#ifndef Director_h
#define Director_h

#include "Employee.h"


class Director final : public Employee
{
public:
    Director() = default;
    void AddNewEmployeeData();
    void Functional() override;
};
#endif // Director_h
