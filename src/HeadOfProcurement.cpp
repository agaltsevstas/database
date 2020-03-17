#include "HeadOfProcurement.h"
#include "Data.h"

HeadOfProcurement::HeadOfProcurement() : data_(&Data::getInstance()) {}

HeadOfProcurement::~HeadOfProcurement()
{
    delete data_;
}

void HeadOfProcurement::functional()
{

}
