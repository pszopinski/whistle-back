#include "complex.h"

Complex::Complex(float re, float im) {
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

float Complex::modulus() {
  return sqrt(real * real + imag * imag);
}
