#ifndef COMPLEX_H
#define COMPLEX_H
#include <math.h>

class Complex {
  public:
    Complex(double re = 0, double im = 0);
    Complex operator+(const Complex& c);
    Complex operator-(const Complex& c);
    Complex operator*(const Complex& c);
    double modulus();

  private:
    double real;
    double imag;
};

#endif
