#include <iostream>
#include "people.hpp"
using namespace std;

int main()
{
    Date Birthday(1998,4,30);
    //Birthday.printDate();
    person WBW("WangBinWei",201616070213,Birthday);
    WBW.printPerson();

    return 0;
}
