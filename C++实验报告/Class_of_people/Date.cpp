#include "people.hpp"
#include <cstdio>
#include <iostream>
using namespace std;

Date::Date(int y , int m , int d)
{
	year = y;
	month = m;
	day = d;
}
void Date::setDate(int y, int m, int d)
{
	year = y;
	month = m;
	day = d;
}
void Date::printDate()
{
	cout << year << "/" << month << "/" << day << endl;
}
int Date::getYear()
{
	return year;
}


