#include <iostream>
#include <cstdio>
#include "complex.hpp"
using namespace std;

complex::complex()
{
    real = 1;
    imag = 1;
}
complex::complex(float real1 ,float imag1)
{
    real = real1;
    imag = imag1;
}
void complex::setComplex(float real ,float imag)
{
    real = real;
    imag = imag;
}
float complex::getReal()
{
    return real;
}
float complex::getImag()
{
    return imag;
}
void complex::printComplex()
{
    printf("Real=%.2f and Imag=%.2f\n",real,imag);
    printf("Complex Module=%.2f\n",sqrt(real*real + imag*imag));
    printf("Complex argz=%.2f¶È\n",atan(imag/real)*180/3.14);
}


