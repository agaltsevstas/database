#include "Logistician.h"
#include "AbstractFactory.h"

class LogisticianCreator : public IAbstractFactory<std::string, IEmployee>
{
public:
    LogisticianCreator();
};

CREATOR_REGISTRATION(LogisticianCreator);

LogisticianCreator::LogisticianCreator()
{
    Add<Logistician>("Логист");
}
