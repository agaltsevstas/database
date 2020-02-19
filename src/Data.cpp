#include "Data.h"

void Data::getAllOtherData() const
{
    Data &data = Data::getInstance();

    for (const auto &tradingCompany: data.tradingCompanyVector_)
    {
        cout << *tradingCompany << endl;
    }
}
