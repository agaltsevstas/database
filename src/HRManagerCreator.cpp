#include "HRManager.h"
#include "AbstractFactory.h"

class HRManagerCreator : public IAbstractFactory<std::string, IEmployee>
{
public:
    HRManagerCreator();
};

CREATOR_REGISTRATION(HRManagerCreator);

HRManagerCreator::HRManagerCreator()
{
    Add<HRManager>("Менеджер_по_персоналу");
}
