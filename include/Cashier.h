#ifndef Cashier_h
#define Cashier_h

#include "Employee.h"


class Cashier final : public Employee
{
public:
    Cashier() = default;
    void Functional() override;
};

#endif // Cashier_h
