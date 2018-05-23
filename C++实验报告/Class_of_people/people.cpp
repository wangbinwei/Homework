#include "people.hpp"
#include <cstdio>
#include <iostream>
using namespace std;

person::person(string n, int i,Date d)
{
    name = n;
    ID = i;
    birthday = d;
}
void person::setName(string n)
{
    name = n;
}
void person::setID(int i)
{
    ID = i;
}
void person::setBirthday(Date d)
{
    birthday = d;
}
void person::printPerson()
{
    cout<<"Name="<<name<<endl;
    printf("ID=%d\n",ID);
    printf("Birthday:%d-%d-%d\n",birthday.year,birthday.month,birthday.day);
}
string person::getName()
{
    return name;
}
int person::getID()
{
    return ID;
}
Date person::getBirthday()
{
    return birthday;
}



