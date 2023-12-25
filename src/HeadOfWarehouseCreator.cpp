#include "HeadOfWarehouse.h"
#include "AbstractFactory.h"

class HeadOfWarehouseCreator : public IAbstractFactory<std::string, IEmployee>
{
public:
    HeadOfWarehouseCreator();
};

CREATOR_REGISTRATION(HeadOfWarehouseCreator);

HeadOfWarehouseCreator::HeadOfWarehouseCreator()
{
    Add<HeadOfWarehouse>("Начальник_склада");
}
