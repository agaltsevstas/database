#include "HRManager.h"
#include "Data.h"

HRManager::HRManager() : data_(&Data::instance()) {}

HRManager::~HRManager()
{
    //    delete data_;
}

void HRManager::addNewEmployeeData()
{
    data_->newEmployeeData(this);
}

void HRManager::functional()
{

}
