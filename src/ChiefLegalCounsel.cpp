#include "ChiefLegalCounsel.h"
#include "Data.h"

ChiefLegalCounsel::ChiefLegalCounsel() : data_(&Data::instance()) {}

ChiefLegalCounsel::~ChiefLegalCounsel()
{
    delete data_;
}

void ChiefLegalCounsel::functional()
{

}
