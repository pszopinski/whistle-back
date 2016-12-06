#include "complex.h"
#include "fft.h"
/*
 * Paweł Szopiński
 * 2016
 * 
 * When a button is pressed, record FFT_CHUNK_SIZE samples and
 * then print their Fourier transform.
 * 
 * Connect wires as in no_buzzer.svg.
 */

// Pull-up pin for the button
const int BUTTON = 5;

// Signal pin of the mic
const int MIC = A5;

// Array for storing samples
Complex SAMPLES[FFT_CHUNK_SIZE];

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Read the button's state
  int buttonState = digitalRead(BUTTON);

  // Record on a button press
  if (buttonState == LOW) {
    
    // Record
    digitalWrite(LED_BUILTIN, HIGH);
    for (int i=0; i<FFT_CHUNK_SIZE; i++) {
      SAMPLES[i] = Complex(analogRead(MIC));
      Serial.println(SAMPLES[i].modulus(), 0);    }
    digitalWrite(LED_BUILTIN, LOW);

    // Do a FFT
    fft(SAMPLES);

    // Find the dominant frequency
    double max_modulus = 0;
    int bin_number = 0;
    for (int i=1; i<FFT_CHUNK_SIZE/2; i++) {
      double modulus = SAMPLES[i].modulus();
      Serial.print(i, DEC);
      Serial.print(": ");
      Serial.println(modulus, 2);
      if (modulus > max_modulus) {
        max_modulus = modulus;
        bin_number = i;
      }
    }
    Serial.println();
    Serial.println(bin_number, DEC);
    Serial.println(bin_number * double(FFT_SAMPLE_RATE) / double(FFT_CHUNK_SIZE), 2);
    Serial.println();

    delay(500);
    
  }
}
