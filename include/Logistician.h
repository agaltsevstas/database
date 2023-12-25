#ifndef Logistician_h
#define Logistician_h

#include "Employee.h"


class Logistician final : public Employee
{
public:
    Logistician() = default;
    void Functional() override;
};

#endif // Logistician_h
