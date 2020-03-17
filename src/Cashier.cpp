#include "Cashier.h"
#include "Data.h"

Cashier::Cashier() : data_(&Data::getInstance()) {}

Cashier::~Cashier()
{
    delete data_;
}

void Cashier::functional()
{

}




