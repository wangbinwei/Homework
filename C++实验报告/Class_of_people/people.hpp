#include <iostream>
#include <cstdio>
#include <math.h>
#include <string.h>

using namespace std;

class Date
{
    public:
        int year;
        int month;
        int day;
    public:
        void setDate(int , int , int );
        Date(int y = 2000, int m = 1, int d = 1);
        void printDate();
        int getYear();


};

class person
{
    public:
        person(string n, int i, Date d);
        void setName(string n);
        void setID(int i);
        void setBirthday(Date d);
        void printPerson();
        string getName();
        int getID();
        Date getBirthday();

    private:
        string name;
        int ID;
        Date birthday;

};


