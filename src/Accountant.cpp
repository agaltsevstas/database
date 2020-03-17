#include "Accountant.h"
#include "Data.h"

Accountant::Accountant() : data_(&Data::getInstance()) {}

Accountant::~Accountant()
{
    delete data_;
}

void Accountant::functional()
{

}

