#include <Keypad.h>
#include<LiquidCrystal.h>
#include<EEPROM.h>
#include <Servo.h>
Servo servo_Motor; 
int redPin = A2;
int greenPin = A1;
LiquidCrystal lcd(30, 31,10,11,12,13);
char password[4];
char pass[4],pass1[4];
int i=0;
char customKey=0;
const byte ROWS = 4; 
const byte COLS = 3; 
char hexaKeys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[ROWS] = { 5,4,3,2 };
byte colPins[COLS] = { 8,7,6 };
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
void setup()
{
  lcd.begin(16,2);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  servo_Motor.attach(9);
  lcd.setCursor(0,1);
  lcd.clear();
  lcd.print("ENTER YOUR PASS:");
  lcd.setCursor(0,1);
  /*for(int j=0;j<4;j++)
  EEPROM.write(j, j+49);
  for(int j=0;j<4;j++)
  pass[j]=EEPROM.read(j);*/
}
  
void loop()
{
  customKey = customKeypad.getKey();
  if(customKey=='0')
  change();
  if(customKey=='*')
  lockdoor();
  if (customKey)
  {
     password[i++]=customKey;
     lcd.print("*");
  }
  if(i==4)
  checkpassword();
}
void change()
{
  int j=0;
  lcd.clear();
  lcd.print("CURRENT PASSWORD");
  lcd.setCursor(0,1);
  while(j<4)
  {
    char key=customKeypad.getKey();
    if(key)
    {
      pass1[j++]=key;
      lcd.print("*");
    }
    key=0;
  }
  delay(500);
  
  if((strncmp(pass1, pass, 4)))
  {
    lcd.clear();
    lcd.print("WRONG");
    lcd.setCursor(0,1);
    lcd.print("Better Luck Again");
    delay(1000);
  }
  else
  {
    j=0;
    
  lcd.clear();
  lcd.print("ENTER NEW:");
  lcd.setCursor(0,1);
  while(j<4)
  {
    char key=customKeypad.getKey();
    if(key)
    {
      pass[j]=key;
      lcd.print("*");
      EEPROM.write(j,key);
      j++;
    }
  }
  lcd.setCursor(0,1);
  lcd.print("DONE......");
  delay(1000);
  }
  lcd.clear();
  lcd.print("ENTER YOUR PASS:");
  lcd.setCursor(0,1);
  customKey=0;
}
 void lockdoor() {
      servo_Motor.write(171);
      digitalWrite(redPin,HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("****DOOR****");
      lcd.setCursor(0, 1);
      lcd.print("****LOCKED****");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ENTER YOUR PASS:");
      lcd.setCursor(0,1);
      customKey=0;
  }
 void checkpassword() {
    delay(200);
    for(int j=0;j<4;j++)
    pass[j]=EEPROM.read(j);
    if(!(strncmp(password, pass,4)))
    {
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
      servo_Motor.write(93);
      Serial.println("ACCESS GRANTED");
      lcd.setCursor(0, 0);
      lcd.print("****WELLCOME****");
      lcd.setCursor(0, 1);
      lcd.print("*ACCESS GRANTED*");
      i=0;
    }
    else
    { 
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, LOW);
      Serial.println("LOCKED");
      lcd.setCursor(0, 0);
      lcd.print("*****SORRY******");
      lcd.setCursor(0, 1);
      lcd.print("****LOCKED******");
      i=0;
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ENTER YOUR PASS:");
      lcd.setCursor(0,1);
      customKey=0;
    }
  }

