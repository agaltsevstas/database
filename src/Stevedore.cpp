#include "Stevedore.h"
#include "Data.h"

Stevedore::Stevedore() : data_(&Data::getInstance()) {}

Stevedore::~Stevedore()
{
    delete data_;
}

void Stevedore::functional()
{

}
