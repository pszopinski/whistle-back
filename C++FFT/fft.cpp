#include "fft.h"

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

