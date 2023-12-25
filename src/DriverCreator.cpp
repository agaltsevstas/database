#include "Driver.h"
#include "AbstractFactory.h"

class DriverCreator : public IAbstractFactory<std::string, IEmployee>
{
public:
    DriverCreator();
};

CREATOR_REGISTRATION(DriverCreator);

DriverCreator::DriverCreator()
{
    Add<Driver>("Водитель");
}

