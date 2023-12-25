#include "AbstractFactory.h"
#include "Accountant.h"

class AccountantCreator : public IAbstractFactory<std::string, IEmployee>
{
public:
    AccountantCreator();
};

CREATOR_REGISTRATION(AccountantCreator);

AccountantCreator::AccountantCreator()
{
    Add<Accountant>("Бухгалтер");
}

