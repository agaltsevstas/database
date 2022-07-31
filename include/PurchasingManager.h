#ifndef PurchasingManager_h
#define PurchasingManager_h

#include "Employee.h"

class Data;

class PurchasingManager : public Employee
{
public:
    PurchasingManager();
    const PurchasingManager& operator = (const Employee &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // PurchasingManager_h
