#include <math.h>

#include "fft.h"


void fft(Complex samples[]) {
  int n = 0;
  for (int span = FFT_CHUNK_SIZE / 2; span > 0; span /= 2) {
    for (int submatrix = 0; submatrix < FFT_CHUNK_SIZE / (span * 2); submatrix++) {
      for (int node = 0; node < span; node++) {
        Complex temp = samples[n] + samples[n + span];
        samples[n + span] = samples[n] - samples[n + span];
        samples[n] = temp;

        float angle = M_PI / span * node;
        Complex twiddle = Complex(cos(angle), sin(angle));
        samples[n + span] = samples[n + span] * twiddle;

        n++;
      }

      n = (n + span) & (FFT_CHUNK_SIZE - 1);

    }
  }

  // Reorder the results
  Complex temp[FFT_CHUNK_SIZE];
  for (int i = 0; i < FFT_CHUNK_SIZE; i++) {
    int new_index = pgm_read_word_near(REVERSED + i);
    temp[i] = samples[new_index];
  }
  for (int i = 0; i < FFT_CHUNK_SIZE; i++) {
    samples[i] = temp[i];
  }
}

double dominant_frequency(Complex samples[]) {
  // Find the maximum modulus
  double max_modulus = 0;
  int bin_number = 0;
  for (int i = 1; i < FFT_CHUNK_SIZE / 2; i++) {
    double modulus = samples[i].modulus();
    if (modulus > max_modulus) {
      max_modulus = modulus;
      bin_number = i;
    }
  }

  // Compute the main frequency based on the bin number
  double frequency = bin_number / double(FFT_CHUNK_SIZE) * FFT_SAMPLING_RATE;

  // Reject too quiet and out of range frequencies
  if (max_modulus < 200 || frequency < 550 || frequency > 2100) {
    return -1;
  }
  return frequency;
}

