#include "Cashier.h"
#include "AbstractFactory.h"


class CashierCreator final : public IAbstractFactory<std::string, IEmployee>
{
public:
    CashierCreator();
};

CREATOR_REGISTRATION(CashierCreator);

CashierCreator::CashierCreator()
{
    Add<Cashier>("Кассир");
}

