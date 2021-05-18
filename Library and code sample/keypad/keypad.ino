#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'4', '6', '5', 'B'},
  {'1', '3', '2', 'A'},
  {'7', '9', '8', 'C'},
  {'*', '#', '0', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

//byte rowPins[ROWS] = {9, 8, 7, 6}; old
//byte colPins[COLS] = {5, 4, 3, 2}; 


Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
}
