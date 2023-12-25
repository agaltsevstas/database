#include "Loader.h"
#include "AbstractFactory.h"

class LoaderCreator : public IAbstractFactory<std::string, IEmployee>
{
public:
    LoaderCreator();
};

CREATOR_REGISTRATION(LoaderCreator);

LoaderCreator::LoaderCreator()
{
    Add<Loader>("Грузчик");
}
