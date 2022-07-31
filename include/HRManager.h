#ifndef HRManager_h
#define HRManager_h

#include "Employee.h"

class Data;

class HRManager : public Employee
{
public:
    HRManager();
    const HRManager& operator = (const Employee &object);
    void AddNewEmployeeData();
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif /* HRManager_h */
