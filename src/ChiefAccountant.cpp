#include "ChiefAccountant.h"
#include "Data.h"

ChiefAccountant::ChiefAccountant() : data_(&Data::instance()) {}

ChiefAccountant::~ChiefAccountant()
{
    delete data_;
}

void ChiefAccountant::functional()
{

}

