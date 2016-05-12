#include <Keypad.h>
#include<LiquidCrystal.h>
#include<EEPROM.h>
#include <Servo.h>


Servo servo_Motor; 
int redPin = A2;
int greenPin = A1;

uint8_t trial = 0;


LiquidCrystal lcd(30, 31,10,11,12,13);

char password[4];
char pass[4],pass1[4];
char ckpass[4];  //for checking purpose

int i=0;

char customKey;
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
  //pinMode(redPin, OUTPUT);
  //pinMode(greenPin, OUTPUT);
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
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CHNAGE PASSWORD?");
    lcd.setCursor(0,1);
    lcd.print("1.YES 0.NO");
    while(1){
    customKey = customKeypad.getKey();
    if(customKey){
      if(customKey=='1'){
        change();
        break;  
      }
     if(customKey=='0'){
      routine();
      break;
      }
      }  
      }
      
    
  }
  if(customKey=='*')
  {
    lockdoor();
  }
  /*  for showing password
  if(customKey=='#')
  {
   for(i=0;i<4;i++){
       lcd.setCursor(i,1);
       char d = EEPROM.read(i);
       lcd.print(d);
    }
     i=0;
   }
   */
    
  if (customKey)
  {
     password[i++]=customKey;
     lcd.print("*");
  if(i==4){
  i=0;
  checkpassword();
  }
  }
  
  
}
void change()
{   
    //load the existing password for checking purpose
    for(int j=0;j<4;j++)
    pass[j]=EEPROM.read(j);
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
    trial++;
    if (trial == 3){
      delay(5 * 60 * 1000);
      trial = 0;
    }
    delay(1000);
  }
  else  //Change password
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
      //EEPROM.write(j,key);
      j++;
    }
  }
  int f=1;
  while(f!=0){
  //Now confirming the given password
  j=0;
  lcd.clear();
  lcd.print("CONFIRM PASSWORD");
  lcd.setCursor(0,1);
  while(j<4)
  {
    char key=customKeypad.getKey();
    if(key)
    {
      ckpass[j]=key;
      lcd.print("*");
      //EEPROM.write(j,key);
      j++;
    }
  }
  j=0;
  if(!(strncmp(pass, ckpass,4))){   //confirming and saving
     while(j<4){
      EEPROM.write(j,pass[j]);
      j++;
      }
  lcd.setCursor(0,1);
  lcd.print("DONE......");
  delay(1000); 
       f=0;   
    }
    else{
      f=1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PASS DONT MATCH");
      lcd.setCursor(0,1);
      lcd.print("PLZ TRY AGAIN");
      delay(2000);
      }
    }

  }
  lcd.clear();
  lcd.print("ENTER YOUR PASS:");
  lcd.setCursor(0,1);
  customKey=0;
}
 void lockdoor() {
      servo_Motor.write(17);
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
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DOOR IS UNLOCKED");
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


void routine(){
  lcd.clear();
  lcd.print("ENTER YOUR PASS:");
  lcd.setCursor(0,1);
  customKey=0;
  }
