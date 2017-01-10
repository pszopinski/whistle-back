#include "complex.h"
#include "reversed128.h"
const int FFT_CHUNK_SIZE = 128;
const int FFT_SAMPLING_RATE = 8217;
const int FFT_DURATION = int(double(FFT_CHUNK_SIZE) / FFT_SAMPLING_RATE * 1000 * 11.5);


void fft(Complex samples[]);
double dominant_frequency(Complex samples[]);
