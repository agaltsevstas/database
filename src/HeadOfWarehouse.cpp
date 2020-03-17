#include "HeadOfWarehouse.h"
#include "Data.h"

HeadOfWarehouse::HeadOfWarehouse() : data_(&Data::getInstance()) {}

HeadOfWarehouse::~HeadOfWarehouse()
{
    delete data_;
}

void HeadOfWarehouse::functional()
{

}
