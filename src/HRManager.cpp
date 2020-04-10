#include "HRManager.h"
#include "Data.h"
#include "Logger.h"

HRManager::HRManager() : data_(&Data::instance()) {}

HRManager::~HRManager()
{
    //    delete data_;
}

void HRManager::addNewEmployeeData()
{
    data_->newEmployeeData();
}

void HRManager::functional()
{

}
