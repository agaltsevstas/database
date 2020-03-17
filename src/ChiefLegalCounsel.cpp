#include "ChiefLegalCounsel.h"
#include "Data.h"

ChiefLegalCounsel::ChiefLegalCounsel() : data_(&Data::getInstance()) {}

ChiefLegalCounsel::~ChiefLegalCounsel()
{
    delete data_;
}

void ChiefLegalCounsel::functional()
{

}
