#ifndef __COMPLEX_H_INCLUDED__
#define __COMPLEX_H_INCLUDED__
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

