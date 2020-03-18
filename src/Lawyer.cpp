#include "Lawyer.h"
#include "Data.h"

Lawyer::Lawyer() : data_(&Data::instance()) {}

Lawyer::~Lawyer()
{
    delete data_;
}

void Lawyer::functional()
{

}
