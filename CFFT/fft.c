#include <stdio.h>
#include <math.h>

#define SAMPLE_RATE 16000
#define SAMPLE_COUNT 3000
#define CHUNK_SIZE 1024
#include "reversed1024.h"

typedef struct complex {
    double re;
    double im;
} complex;

complex complex_add(complex a, complex b) {
    complex result = {a.re + b.re, a.im + b.im};
    return result;
}

complex complex_substract(complex a, complex b) {
    complex result = {a.re - b.re, a.im - b.im};
    return result;
}

complex complex_multiply(complex a, complex b) {
    complex result = {a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re};
    return result;
}

double modulus(complex a) {
    return sqrt(a.re * a.re + a.im * a.im);
}

// Fill a portion of samples with sine wave of given frequency.
void generate_frequency(int* samples, int offset, int size, double frequency) {
    for (int i=0; i<size; i++) {
        double sin_value = sin(i * (2 * M_PI) * frequency / SAMPLE_RATE);
        
        // map sin_value to 0-1023 range
        // this is how Arduino would read the signal
        int int_value = 511.5 * sin_value + 512;
        
        samples[i + offset] = int_value;
    }
}

// Enumerate and print the whole data array.
void print_data(complex* data) {
    for (int i=0; i<CHUNK_SIZE; i++) {
        printf("%d\t%f\t%f\n", i, data[i].re, data[i].im);
    }
}

// Enumerate data and print the modulus.
void print_fft(complex* data) {
    for (int i=0; i<CHUNK_SIZE; i++) {
        printf("%d\t%f\n", i, modulus(data[i]));
    }
}

// Perform a FFT on data.
// http://www.katjaas.nl/FFT/FFT.html
// Data reordering takes place, but value normalisation does not.
void fft(complex* data) {
    // Do FFT in place
    int n = 0;
    for (int span=CHUNK_SIZE/2; span > 0; span/=2) {
        for (int submatrix=0; submatrix < CHUNK_SIZE / (span * 2); submatrix++) {
            for (int node=0; node < span; node++) {
                complex temp = complex_add(data[n], data[n + span]);
                data[n + span] = complex_substract(data[n], data[n + span]);
                data[n] = temp;
                
                double angle = M_PI / span * node;
                complex twiddle = {cos(angle), sin(angle)};
                data[n + span] = complex_multiply(data[n + span], twiddle);
                
                n++;
            }

            n = (n + span) & (CHUNK_SIZE - 1);

        }
    }
    
    // Reorder the results
    complex temp[CHUNK_SIZE];
    for (int i=0; i<CHUNK_SIZE; i++) {
        temp[i] = data[REVERSED[i]];
    }
    for (int i=0; i<CHUNK_SIZE; i++) {
        data[i] = temp[i];
    }
}

int main() {
    int samples[SAMPLE_COUNT];
    
    // Fill the first half of samples with 1 kHz and the other with 1.5 kHz
    generate_frequency(samples, 0, SAMPLE_COUNT / 2, 300);
    generate_frequency(samples, SAMPLE_COUNT / 2, SAMPLE_COUNT / 2, 200);
    
    complex data[CHUNK_SIZE];
    for (int i=0; i<SAMPLE_COUNT/CHUNK_SIZE; i+=1) {
        printf("Chunk #%d\n", i + 1);
        for (int j=0; j<CHUNK_SIZE; j++) {
            data[j].re = samples[i * CHUNK_SIZE + j];
            data[j].im = 0;
        }

        // Perform a FFT
        fft(data);
        
        // Print FFT results
        print_fft(data);
        
        printf("\n");
    }
}
