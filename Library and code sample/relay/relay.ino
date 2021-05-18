

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(A0, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(A0, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(A0, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
