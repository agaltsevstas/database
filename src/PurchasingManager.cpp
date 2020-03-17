#include "PurchasingManager.h"
#include "Data.h"

PurchasingManager::PurchasingManager() : data_(&Data::getInstance()) {}

PurchasingManager::~PurchasingManager()
{
    delete data_;
}

void PurchasingManager::functional()
{

}
