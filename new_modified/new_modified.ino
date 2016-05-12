#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Password.h>
#include <Servo.h>

Servo servo_Motor; 
char* password = "123";
int position = 0;
const byte ROWS = 4; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[ROWS] = { 5,4,3,2 };
byte colPins[COLS] = { 8,7,6 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int redPin = A2;
int greenPin = A1;

LiquidCrystal lcd(30, 31,10,11,12,13);
#define LCD_CLEAR 0b00000001

void setup()
{
  Serial.begin(9600);
    lcd.begin(16, 2);
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
servo_Motor.attach(9);
setLocked(true);
}

void loop()
{
char key = keypad.getKey();
if (key == '*' || key == '#')
{
position = 0;
setLocked(true);
}
if (key == password[position])
{
position ++;
}
if (position == 3)
{
setLocked(false);
}
delay(50);
}
void setLocked(int locked)
{
if (locked)
{
digitalWrite(redPin, HIGH);
digitalWrite(greenPin, LOW);
servo_Motor.write(9);
Serial.println("LOCKED");
lcd.setCursor(0, 0);
lcd.print("*****SORRY******");
lcd.setCursor(0, 1);
lcd.print("****LOCKED******");

}
else
{
digitalWrite(redPin, LOW);
digitalWrite(greenPin, HIGH);
servo_Motor.write(93);
Serial.println("ACCESS GRANTED");
lcd.setCursor(0, 0);
lcd.print("****WELLCOME****");
lcd.setCursor(0, 1);
lcd.print("*ACCESS GRANTED*");
}
}
