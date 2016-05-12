#include <Password.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
LiquidCrystal lcd(2,3,4,9,10,11,12);
Password password = Password( "4321" );
const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3',},
  {'4','5','6',},
  {'7','8','9',},
  {'*','0',' ',}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = {25, 24, 23, 22}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {28, 27, 26}; //connect to the column pinouts of the keypad
const int buttonPin = 7;
int buttonState = 0;

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define ledPin 13

void setup(){
   pinMode(buttonPin, INPUT);
lcd.begin(16, 2);
digitalWrite(ledPin, LOW); // sets the LED on
Serial.begin(9600);
keypad.addEventListener(keypadEvent); //add an event listener for this keypad
keypad.setDebounceTime(250);
}

void loop(){
keypad.getKey();
buttonState = digitalRead(buttonPin);
if (buttonState == HIGH) {
lcd.clear();
}
}

//take care of some special events
void keypadEvent(KeypadEvent eKey){
switch (keypad.getState()){
case PRESSED:
lcd.print(eKey);
switch (eKey){
case ' ': guessPassword(); break;
default:
password.append(eKey);
}
}}

void guessPassword(){
if (password.evaluate()){
digitalWrite(ledPin,HIGH); //activates garaged door relay
delay(500);
digitalWrite(ledPin,LOW); //turns off door relay after .5 sec
lcd.print("VALID PASSWORD "); //
password.reset(); //resets password after correct entry
delay(600);
lcd.print("Welcome");
delay(2000);
lcd.clear();
}


else{
digitalWrite(ledPin,LOW);
lcd.print("INVALID PASSWORD ");
password.reset(); //resets password after INCORRECT entry
delay(600);
lcd.clear();
}
}
