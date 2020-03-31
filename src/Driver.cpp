#include "Driver.h"
#include "Data.h"

Driver::Driver() : data_(&Data::instance()) {}

Driver::~Driver()
{
//    delete data_;
}

void Driver::functional()
{

}
