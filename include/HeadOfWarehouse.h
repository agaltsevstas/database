#ifndef HeadOfWarehouse_h
#define HeadOfWarehouse_h

#include "Employee.h"


class HeadOfWarehouse final : public Employee
{
public:
    HeadOfWarehouse() = default;
    void Functional() override;
};

#endif // HeadOfWarehouse_h
