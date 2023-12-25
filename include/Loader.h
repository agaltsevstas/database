#ifndef Loader_h
#define Loader_h

#include "Employee.h"


class Loader final : public Employee
{
public:
    Loader() = default;
    void Functional() override;
};

#endif // Loader_h

