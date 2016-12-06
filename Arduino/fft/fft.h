#include <math.h>

#include "complex.h"
#include "reversed128.h"

const int FFT_CHUNK_SIZE = 128;
const int FFT_SAMPLE_RATE = 10000;

void fft(Complex data[]);

