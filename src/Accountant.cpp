#include "Accountant.h"
#include "Data.h"
#include "Logger.h"

Accountant::Accountant() : data_(&Data::instance()) {}

Accountant::~Accountant()
{
//    delete data_;
}

void Accountant::functional()
{

}

