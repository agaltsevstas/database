#ifndef PurchasingManager_h
#define PurchasingManager_h

#include "Employee.h"


class PurchasingManager final : public Employee
{
public:
    PurchasingManager() = default;
    void Functional() override;
};

#endif // PurchasingManager_h
