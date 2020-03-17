#include "Driver.h"
#include "Data.h"

Driver::Driver() : data_(&Data::getInstance()) {}

Driver::~Driver()
{
    delete data_;
}

void Driver::functional()
{

}
