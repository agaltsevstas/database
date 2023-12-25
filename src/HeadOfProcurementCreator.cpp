#include "HeadOfProcurement.h"
#include "AbstractFactory.h"

class HeadOfProcurementCreator : public IAbstractFactory<std::string, IEmployee>
{
public:
    HeadOfProcurementCreator();
};

CREATOR_REGISTRATION(HeadOfProcurementCreator);

HeadOfProcurementCreator::HeadOfProcurementCreator()
{
    Add<HeadOfProcurement>("Начальник_отдела_закупок");
}
