#include "complex.h"
#include "fft.h"
/*
   Paweł Szopiński
   2016
*/

// Pull-up pin for the button
const int BUTTON = 5;

// Buzzer pin
const int BUZZER = 10;

// Signal pin of the mic
const int MIC = A5;

// Array for storing samples
Complex SAMPLES[FFT_CHUNK_SIZE];

// Array for storing results
const int LEN = 30;
double RESULTS[LEN];

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {

    // Turn the LED on
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print(F("Recording... "));

    for (int i = 0; i < LEN; i++) {
      // Record
      for (int j = 0; j < FFT_CHUNK_SIZE; j++) {
        SAMPLES[j] = Complex(analogRead(MIC));
      }

      // Do a FFT
      fft(SAMPLES);

      // Save the dominant frequency
      RESULTS[i] = dominant_frequency(SAMPLES);
      Serial.println(RESULTS[i]);
    }

    // Turn the LED off
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print(F("Done. "));
    
    // Play a tune
    Serial.print(F("Playing... "));
    for (int i = 0; i < LEN; i++) {
      double frequency = RESULTS[i];
      if (frequency > 0) {
        tone(BUZZER, frequency);
      }
      delay(FFT_DURATION);
      noTone(BUZZER);
    }
    Serial.println(F("Done."));

    // Blink the LED
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}
