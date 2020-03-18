#include "PurchasingManager.h"
#include "Data.h"

PurchasingManager::PurchasingManager() : data_(&Data::instance()) {}

PurchasingManager::~PurchasingManager()
{
    delete data_;
}

void PurchasingManager::functional()
{

}
