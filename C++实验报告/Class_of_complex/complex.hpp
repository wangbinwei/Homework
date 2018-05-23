#include <iostream>
#include <cstdio>
#include <math.h>
using namespace std;

class complex
{
    public:
    complex();
    complex(float real ,float imag);
    void setComplex(float real, float imag);
    float getReal();
    float getImag();
    void printComplex();
    private:
        float imag;
        float real;
};
