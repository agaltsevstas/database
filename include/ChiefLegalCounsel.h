#ifndef ChiefLegalCouncel_h
#define ChiefLegalCouncel_h

#include "Employee.h"


class ChiefLegalCounsel final : public Employee
{
public:
    ChiefLegalCounsel() = default;
    void Functional() override;
};

#endif // ChiefLegalCouncel_h
