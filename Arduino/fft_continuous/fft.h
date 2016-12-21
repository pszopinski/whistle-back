#include "complex.h"
#include "reversed128.h"
const int FFT_CHUNK_SIZE = 128;
const int FFT_SAMPLING_RATE = 8800;


void fft(Complex samples[]);
double dominant_frequency(Complex samples[]);
