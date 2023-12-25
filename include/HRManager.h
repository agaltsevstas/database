#ifndef HRManager_h
#define HRManager_h

#include "Employee.h"


class HRManager final : public Employee
{
public:
    HRManager() = default;
    void Functional() override;
};

#endif /* HRManager_h */
