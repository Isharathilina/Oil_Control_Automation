//sketch created by Akshay Joseph
#include "HX711.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN  10
#define LOADCELL_SCK_PIN  11

#define LOADCELL_DOUT_PIN2  12
#define LOADCELL_SCK_PIN2  13

HX711 scaleA;
HX711 scaleB;
// lcd config
LiquidCrystal_I2C lcd(0x27, 16, 4);
//keypad config
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

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
// Globle variable
int solenoidA1 = A0;
int solenoidA2 = A1;
int solenoidB1 = A2;
int solenoidB2 = A3;

int weight;
int waitingTime;


void runTypeAweight()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Oil Type:- A");
  lcd.setCursor(-4,1);
  lcd.print("Enter Weight :-");

  lcd.setCursor(-4,2);
  char customKey='w';
  String inputString="";
  int enterdNum=0;
  while(!(customKey=='#'))
  {
    customKey = customKeypad.getKey();
    if (customKey >= '0' && customKey <= '9') {     // only act on numeric keys
      inputString += customKey; 
      lcd.print(customKey);              // append new character to input string
    }else if(customKey=='D'){ 
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cancelled");
      delay(500);
      setup();
      } // reset 
    //Serial.println(customKey);
  }
  if (inputString.length() > 0) {
      enterdNum = inputString.toInt(); // YOU GOT AN INTEGER NUMBER
      inputString = "";               // clear input
      weight = enterdNum;
      //Serial.println(enterdNum);
      }

  lcd.setCursor(2,3);
  lcd.print("Done");
  delay(500);

}

void runTypeBweight()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Oil Type:- B");
  lcd.setCursor(-4,1);
  lcd.print("Enter Weight :-");

  lcd.setCursor(-4,2);
  char customKey='w';
  String inputString="";
  int enterdNum=0;
  while(!(customKey=='#'))
  {
    customKey = customKeypad.getKey();
    if (customKey >= '0' && customKey <= '9') {     // only act on numeric keys
      inputString += customKey; 
      lcd.print(customKey);              // append new character to input string
    }else if(customKey=='D'){ 
      
       lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cancelled");
      delay(500);
      setup();
      } // reset
    //Serial.println(customKey);
  }
  if (inputString.length() > 0) {
      enterdNum = inputString.toInt(); // YOU GOT AN INTEGER NUMBER
      inputString = "";               // clear input
      weight = enterdNum;
      //Serial.println(enterdNum);
      }

  lcd.setCursor(2,3);
  lcd.print("Done");
  delay(500);

}


void runTypeAtime()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Oil Type:- A");
  lcd.setCursor(-4,1);
  lcd.print("Enter Time(S):-");

  lcd.setCursor(-4,2);
  char customKey='w';
  String inputString="";
  int enterdNum=0;
  while(!(customKey=='#'))
  {
    customKey = customKeypad.getKey();
    if (customKey >= '0' && customKey <= '9') {     // only act on numeric keys
      inputString += customKey; 
      lcd.print(customKey);              // append new character to input string
    }else if(customKey=='D'){ 
     
       lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cancelled");
      delay(500);
       setup();
      } // reset
    //Serial.println(customKey);
  }
  if (inputString.length() > 0) {
      enterdNum = inputString.toInt(); // YOU GOT AN INTEGER NUMBER
      inputString = "";               // clear input
      waitingTime = enterdNum;
      //Serial.println(enterdNum);
      }

  lcd.setCursor(2,3);
  lcd.print("Done");
  delay(500);
}

void runTypeBtime()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Oil Type:- B");
  lcd.setCursor(-4,1);
  lcd.print("Enter Time(S):-");

  lcd.setCursor(-4,2);
  char customKey='w';
  String inputString="";
  int enterdNum=0;
  while(!(customKey=='#'))
  {
    customKey = customKeypad.getKey();
    if (customKey >= '0' && customKey <= '9') {     // only act on numeric keys
      inputString += customKey; 
      lcd.print(customKey);              // append new character to input string
    }else if(customKey=='D'){ 
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cancelled");
      delay(500);
      setup();
      } // reset
    //Serial.println(customKey);
  }
  if (inputString.length() > 0) {
      enterdNum = inputString.toInt(); // YOU GOT AN INTEGER NUMBER
      inputString = "";               // clear input
      waitingTime = enterdNum;
      //Serial.println(enterdNum);
      }

  lcd.setCursor(2,3);
  lcd.print("Done");
  delay(500);
}



void waiting(int duration)
{
  for(int i=0; i<=duration; i++){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Waiting : ");
    lcd.print(i);
    delay(1000);
    char customKey = customKeypad.getKey();
    if(customKey=='D'){ 
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cancelled");
      delay(500);
      setup();
      } // rese
  }

}

void fillingTypeAtank()
{
  // on sol A1
  digitalWrite(solenoidA1, LOW); // on
  digitalWrite(solenoidA2, HIGH); // off
  float loadCell =0;
  while(loadCell<=weight)
  {
    loadCell = scaleA.get_units();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Filling :- ");
    lcd.setCursor(-4,1);
    lcd.print(loadCell);
    lcd.print(" g");
    delay(500);
    char  customKey = customKeypad.getKey();
    if(customKey=='D'){ 
    
     lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cancelled");
      delay(500);
      setup();
    } // reset
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Filling :- ");
  lcd.setCursor(-4,1);
  lcd.print(float(weight));
  lcd.print(" g");
  lcd.setCursor(2,3);
  lcd.print("Filled"); 
   delay(1000);
  
   // off sol A1 and on sol A2
  digitalWrite(solenoidA1, HIGH); // off
  digitalWrite(solenoidA2, LOW); // on


}

void fillingTypeBtank()
{
  // on sol A1
  digitalWrite(solenoidB1, LOW); // on
  digitalWrite(solenoidB2, HIGH); // off
  float loadCell =0;
  while(loadCell<=weight)
  {
    loadCell = scaleB.get_units();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Filling :- ");
    lcd.setCursor(-4,1);
    lcd.print(loadCell);
    lcd.print(" g");
    delay(500);

    char  customKey = customKeypad.getKey();
    if(customKey=='D'){ 
       lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cancelled");
      delay(500);
      setup();
      
      } // reset
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Filling :- ");
  lcd.setCursor(-4,1);
  lcd.print(float(weight));
  lcd.print(" g");
  lcd.setCursor(2,3);
  lcd.print("Filled"); 
   delay(1000);

   // off sol A1 and on sol A2
  digitalWrite(solenoidB1, HIGH); // off
  digitalWrite(solenoidB2, LOW); // on


}





void setup()
{
  pinMode(solenoidA1, OUTPUT);
  pinMode(solenoidA2, OUTPUT);
  pinMode(solenoidB1, OUTPUT);
  pinMode(solenoidB2, OUTPUT);
  digitalWrite(solenoidA1, HIGH); // off
  digitalWrite(solenoidA2, HIGH); // off
  digitalWrite(solenoidB1, HIGH); // off
  digitalWrite(solenoidB2, HIGH); // off

  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.clear();

  scaleA.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scaleA.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scaleA.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  scaleB.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);
  scaleB.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scaleB.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  //runTypeAweight(); // temp
  //runTypeAtime();
  //waiting(waitingTime);
  //fillingTypeAtank();

  //Serial.println();
  //Serial.print("w ");
  //Serial.print(weight);
  //Serial.print(" T ");
  //Serial.println(waitingTime);


  lcd.setCursor(4,0);
  lcd.print("Welcome");
  delay(1000);
  lcd.setCursor(-4,1);
  for(int i=0;i<16;i++){
    lcd.print("*");
    delay(150);
    }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Oil Type:-");

  char customKey;
  while(!(customKey=='A' || customKey=='B'))
  {
    customKey = customKeypad.getKey();
     if(customKey=='D'){ 
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cancelled");
      delay(500);
      setup();
      
      } 
    //Serial.println(customKey);
  }
  
  lcd.setCursor(-4,1);
  lcd.print(customKey);
  delay(500);
  //Serial.println(customKey);
  if(customKey=='A'){
    lcd.setCursor(-4,2);
    lcd.print("Type A Selected !");
    delay(500);

    runTypeAweight(); // get weight
    runTypeAtime();  // get time
    waiting(waitingTime); // wait
    fillingTypeAtank(); // start fill
  
  }else if(customKey=='B'){
    lcd.setCursor(-4,2);
    lcd.print("Type B Selected !");
    delay(500);

    runTypeBweight(); // get weight
    runTypeBtime();  // get time
    waiting(waitingTime); // wait
    fillingTypeBtank(); // start fill
      
  }else  if(customKey=='D'){
     lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cancelled");
      delay(500);
    setup();
  }

  
}

void loop()
{
  char  customKey = customKeypad.getKey();
  if(customKey=='D'){
     if(customKey=='D'){ 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cancelled");
      delay(500);
      setup();
       
      
      }
    
    setup();
  }
  
}
