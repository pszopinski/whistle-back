#include "complex.h"

Complex::Complex(double re, double im) {
  real = re;
  imag = im;
}

Complex Complex::operator+(const Complex& c) {
  return Complex(real + c.real, imag + c.imag);
}

Complex Complex::operator-(const Complex& c) {
  return Complex(real - c.real, imag - c.imag);
}

Complex Complex::operator*(const Complex& c) {
  return Complex(real * c.real - imag * c.imag,
                 real * c.imag + imag * c.real);
}

double Complex::modulus() {
  return sqrt(real * real + imag * imag);
}
