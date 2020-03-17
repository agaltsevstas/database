#include "ChiefAccountant.h"
#include "Data.h"

ChiefAccountant::ChiefAccountant() : data_(&Data::getInstance()) {}

ChiefAccountant::~ChiefAccountant()
{
    delete data_;
}

void ChiefAccountant::functional()
{

}

