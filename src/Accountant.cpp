#include "Accountant.h"

void Accountant::functional()
{

}

void Accountant::setPremium(int premium)
{
    salary_ += premium;
}
void Accountant::setFine(int fine)
{
    salary_ -= fine;
}

