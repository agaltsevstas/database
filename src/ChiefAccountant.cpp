#include "ChiefAccountant.h"

void ChiefAccountant::functional()
{

}

void ChiefAccountant::setPremium(int premium)
{
    salary_ += premium;
}
void ChiefAccountant::setFine(int fine)
{
    salary_ -= fine;
}
