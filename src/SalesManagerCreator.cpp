#include "SalesManager.h"
#include "AbstractFactory.h"

class SalesManagerCreator : public IAbstractFactory<std::string, IEmployee>
{
public:
    SalesManagerCreator();
};

CREATOR_REGISTRATION(SalesManagerCreator);

SalesManagerCreator::SalesManagerCreator()
{
    Add<SalesManager>("Менеджер_по_продажам");
}
