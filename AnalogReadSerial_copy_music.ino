/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/

// Define pins
const int buzzerPin = 10;
const int potPin = A1;
const int buttonPin = 2;

const int led4 = 6;
const int led1 = 7;
const int led2 = 8;
const int led3 = 9;
 // NEW: extra LED for high pitch

bool isPlaying = false;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Use internal pull-up

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT); // NEW

  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin); // 0 - 1023
  int freq = map(potValue, 0, 1023, 100, 1200); // Map pot to frequency
  int buttonState = digitalRead(buttonPin);

  // Toggle play state when button is pressed
  if (buttonState == LOW) {
    delay(100); // debounce
    isPlaying = !isPlaying;
    while (digitalRead(buttonPin) == LOW); // wait for button release
  }

  if (isPlaying) {
    tone(buzzerPin, freq);

    // Light pattern (based on frequency range)
    digitalWrite(led1, HIGH); // Always on when sound is playing

    digitalWrite(led2, freq > 400 ? HIGH : LOW);
    digitalWrite(led3, freq > 700 ? HIGH : LOW);
    digitalWrite(led4, freq > 950 ? HIGH : LOW); // NEW: lights up at highest pitch
  } else {
    noTone(buzzerPin);

    // Turn off all LEDs
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW); // NEW
  }

  delay(10);
}