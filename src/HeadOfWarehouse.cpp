#include "HeadOfWarehouse.h"
#include "Data.h"

HeadOfWarehouse::HeadOfWarehouse() : data_(&Data::instance()) {}

HeadOfWarehouse::~HeadOfWarehouse()
{
    delete data_;
}

void HeadOfWarehouse::functional()
{

}
