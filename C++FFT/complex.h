#ifndef COMPLEX_H
#define COMPLEX_H
#include <cmath>

class Complex {
  public:
    Complex(float re = 0, float im = 0);
    Complex operator+(const Complex& c);
    Complex operator-(const Complex& c);
    Complex operator*(const Complex& c);
    float modulus();

  private:
    float real;
    float imag;
};

#endif
