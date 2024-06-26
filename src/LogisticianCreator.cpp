#include "Logistician.h"
#include "AbstractFactory.h"


class LogisticianCreator final : public IAbstractFactory<std::string, IEmployee>
{
public:
    LogisticianCreator();
};

CREATOR_REGISTRATION(LogisticianCreator);

LogisticianCreator::LogisticianCreator()
{
    Add<Logistician>("Логист");
}
