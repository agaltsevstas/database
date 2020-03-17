#include "Logistician.h"
#include "Data.h"

Logistician::Logistician() : data_(&Data::getInstance()) {}

Logistician::~Logistician()
{
    delete data_;
}

void Logistician::functional()
{

}

