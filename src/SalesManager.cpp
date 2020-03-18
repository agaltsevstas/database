#include "SalesManager.h"
#include "Data.h"

SalesManager::SalesManager() : data_(&Data::instance()) {}

SalesManager::~SalesManager()
{
    delete data_;
}

void SalesManager::functional()
{

}
