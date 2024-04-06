#include "ChiefLegalCounsel.h"
#include "AbstractFactory.h"


class ChiefLegalCounselCreator final : public IAbstractFactory<std::string, IEmployee>
{
public:
    ChiefLegalCounselCreator();
};

CREATOR_REGISTRATION(ChiefLegalCounselCreator);

ChiefLegalCounselCreator::ChiefLegalCounselCreator()
{
    Add<ChiefLegalCounsel>("Главный_юрист-консультант");
}

