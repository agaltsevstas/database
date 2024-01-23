#include "Director.h"
#include "AbstractFactory.h"

class DirectorCreator final : public IAbstractFactory<std::string, IEmployee>
{
public:
    DirectorCreator();
};

CREATOR_REGISTRATION(DirectorCreator);

DirectorCreator::DirectorCreator()
{
    Add<Director>("Директор");
}
