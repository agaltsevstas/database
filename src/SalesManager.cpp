#include "SalesManager.h"
#include "Data.h"

SalesManager::SalesManager() : data_(&Data::getInstance()) {}

SalesManager::~SalesManager()
{
    delete data_;
}

void SalesManager::functional()
{

}
