#ifndef HeadOfProcurement_h
#define HeadOfProcurement_h

#include "Employee.h"


class HeadOfProcurement final : public Employee
{
public:
    HeadOfProcurement() = default;
    void Functional() override;
};

#endif // HeadOfProcurement_h
