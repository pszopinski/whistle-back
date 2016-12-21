#include <iostream>
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

const int REVERSED[128] = {
  0,
  64,
  32,
  96,
  16,
  80,
  48,
  112,
  8,
  72,
  40,
  104,
  24,
  88,
  56,
  120,
  4,
  68,
  36,
  100,
  20,
  84,
  52,
  116,
  12,
  76,
  44,
  108,
  28,
  92,
  60,
  124,
  2,
  66,
  34,
  98,
  18,
  82,
  50,
  114,
  10,
  74,
  42,
  106,
  26,
  90,
  58,
  122,
  6,
  70,
  38,
  102,
  22,
  86,
  54,
  118,
  14,
  78,
  46,
  110,
  30,
  94,
  62,
  126,
  1,
  65,
  33,
  97,
  17,
  81,
  49,
  113,
  9,
  73,
  41,
  105,
  25,
  89,
  57,
  121,
  5,
  69,
  37,
  101,
  21,
  85,
  53,
  117,
  13,
  77,
  45,
  109,
  29,
  93,
  61,
  125,
  3,
  67,
  35,
  99,
  19,
  83,
  51,
  115,
  11,
  75,
  43,
  107,
  27,
  91,
  59,
  123,
  7,
  71,
  39,
  103,
  23,
  87,
  55,
  119,
  15,
  79,
  47,
  111,
  31,
  95,
  63,
  127
};

const int FFT_CHUNK_SIZE = 128;

void fft(Complex data[]);

void fft(Complex data[]) {
  int n = 0;
  for (int span = FFT_CHUNK_SIZE / 2; span > 0; span /= 2) {
    for (int submatrix = 0; submatrix < FFT_CHUNK_SIZE / (span * 2); submatrix++) {
      for (int node = 0; node < span; node++) {
        Complex temp = data[n] + data[n + span];
        data[n + span] = data[n] - data[n + span];
        data[n] = temp;

        float angle = M_PI / span * node;
        Complex twiddle = Complex(cos(angle), sin(angle));
        data[n + span] = data[n + span] * twiddle;

        n++;
      }

      n = (n + span) & (FFT_CHUNK_SIZE - 1);

    }
  }

  // Reorder the results
  Complex temp[FFT_CHUNK_SIZE];
  for (int i = 0; i < FFT_CHUNK_SIZE; i++) {
    temp[i] = data[REVERSED[i]];
  }
  for (int i = 0; i < FFT_CHUNK_SIZE; i++) {
    data[i] = temp[i];
  }
}

Complex SAMPLES[FFT_CHUNK_SIZE] = {
    557,
    392,
    529,
    439,
    515,
    575,
    612,
    558,
    492,
    481,
    504,
    496,
    470,
    436,
    418,
    471,
    534,
    580,
    560,
    521,
    523,
    559,
    567,
    531,
    465,
    426,
    453,
    504,
    527,
    508,
    488,
    506,
    559,
    589,
    556,
    492,
    457,
    484,
    517,
    515,
    474,
    450,
    480,
    538,
    573,
    553,
    506,
    491,
    517,
    546,
    533,
    480,
    444,
    465,
    517,
    547,
    525,
    488,
    490,
    533,
    569,
    553,
    497,
    461,
    478,
    521,
    533,
    502,
    464,
    473,
    524,
    565,
    553,
    504,
    475,
    497,
    538,
    541,
    496,
    455,
    465,
    516,
    554,
    538,
    497,
    484,
    516,
    554,
    552,
    503,
    460,
    469,
    515,
    543,
    521,
    479,
    474,
    519,
    562,
    555,
    504,
    468,
    485,
    526,
    541,
    505,
    463,
    464,
    512,
    553,
    544,
    499,
    475,
    501,
    544,
    551,
    506,
    461,
    466,
    514,
    546,
    530,
    486,
    473,
    511,
    555,
    556,
    509
};

int main() {
    fft(SAMPLES);
    
    for (int i = 1; i < FFT_CHUNK_SIZE / 2; i++) {
        std::cout << SAMPLES[i].modulus() << std::endl;
    }
}
