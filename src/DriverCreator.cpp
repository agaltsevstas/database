#include "Driver.h"
#include "AbstractFactory.h"

class DriverCreator final : public IAbstractFactory<std::string, IEmployee>
{
public:
    DriverCreator();
};

CREATOR_REGISTRATION(DriverCreator);

DriverCreator::DriverCreator()
{
    Add<Driver>("Водитель");
}

