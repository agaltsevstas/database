#ifndef Driver_h
#define Driver_h

#include "Employee.h"


class Driver final : public Employee
{
public:
    Driver() = default;
    void Functional() override;
};

#endif // Driver_h
