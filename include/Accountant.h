#ifndef Accountant_h
#define Accountant_h

#include "Employee.h"


class Accountant final : public Employee
{
public:
    Accountant() = default;
    void Functional() override;
};

#endif // Accountant_h
