#include "PurchasingManager.h"
#include "AbstractFactory.h"


class PurchasingManagerCreator final : public IAbstractFactory<std::string, IEmployee>
{
public:
    PurchasingManagerCreator();
};

CREATOR_REGISTRATION(PurchasingManagerCreator);

PurchasingManagerCreator::PurchasingManagerCreator()
{
    Add<PurchasingManager>("Менеджер_по_закупкам");
}
