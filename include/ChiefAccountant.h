#ifndef ChiefAccoutant_h
#define ChiefAccoutant_h

#include "Employee.h"


class ChiefAccountant final : public Employee
{
public:
    ChiefAccountant() = default;
    void Functional() override;
};
#endif // ChiefAccoutant_h
