#include "Lawyer.h"
#include "Data.h"

Lawyer::Lawyer() : data_(&Data::getInstance()) {}

Lawyer::~Lawyer()
{
    delete data_;
}

void Lawyer::functional()
{

}
