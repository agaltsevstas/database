#include "Lawyer.h"
#include "AbstractFactory.h"

class LawyerCreator : public IAbstractFactory<std::string, IEmployee>
{
public:
    LawyerCreator();
};

CREATOR_REGISTRATION(LawyerCreator);

LawyerCreator::LawyerCreator()
{
    Add<Lawyer>("Юрист");
}
