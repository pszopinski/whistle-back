#include "complex.h"
#include "fft.h"
/*
   Paweł Szopiński
   2016

   Perform a Fast Fourier Transfrom on a button press.

   Connect the wires as in diagram.png.
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
    for (int i = 0; i < FFT_CHUNK_SIZE; i++) {
      SAMPLES[i] = Complex(analogRead(MIC));
    }
    digitalWrite(LED_BUILTIN, LOW);

    // Do a FFT
    fft(SAMPLES);

    // Print the results
    for (int i = 1; i < FFT_CHUNK_SIZE / 2; i++) {
      Serial.println(SAMPLES[i].modulus());
    }
    Serial.println();

    // Print the dominan frequency
    Serial.print(F("Dominant frequency: "));
    Serial.println(dominant_frequency(SAMPLES));
    Serial.println();

    // Wait for one second
    delay(1000);
  }
}
