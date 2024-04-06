#include "ChiefAccountant.h"
#include "AbstractFactory.h"


class ChiefAccountantCreator final : public IAbstractFactory<std::string, IEmployee>
{
public:
    ChiefAccountantCreator();
};

CREATOR_REGISTRATION(ChiefAccountantCreator);

ChiefAccountantCreator::ChiefAccountantCreator()
{
    Add<ChiefAccountant>("Главный_бухгалтер");
}

