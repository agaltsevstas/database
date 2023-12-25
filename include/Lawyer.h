#ifndef Lawyer_h
#define Lawyer_h

#include "Employee.h"


class Lawyer final : public Employee
{
public:
    Lawyer() = default;
    void Functional() override;
};

#endif // Lawyer_h
