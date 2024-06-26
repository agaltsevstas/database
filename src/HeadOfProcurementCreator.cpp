#include "HeadOfProcurement.h"
#include "AbstractFactory.h"


class HeadOfProcurementCreator final : public IAbstractFactory<std::string, IEmployee>
{
public:
    HeadOfProcurementCreator();
};

CREATOR_REGISTRATION(HeadOfProcurementCreator);

HeadOfProcurementCreator::HeadOfProcurementCreator()
{
    Add<HeadOfProcurement>("Начальник_отдела_закупок");
}
