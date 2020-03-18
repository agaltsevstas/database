#include "Stevedore.h"
#include "Data.h"

Stevedore::Stevedore() : data_(&Data::instance()) {}

Stevedore::~Stevedore()
{
    delete data_;
}

void Stevedore::functional()
{

}
