/*
   Paweł Szopiński
   2016

   Connect 3.3 V to REF (external analog reference).
   Connect the buzzer to the ground, 3.3 V and MIC analog pin.
   Connect the button to the ground and BUTTON pin.
*/

// Pull-up pin for the button
const int BUTTON = 5;

// Signal pin of the mic
const int MIC = A5;

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  // Read the button's state
  int buttonState = digitalRead(BUTTON);

  // Stream on a button press
  if (buttonState == LOW) {

    // Print out a sample
    Serial.println(analogRead(MIC), DEC);

  }
}


