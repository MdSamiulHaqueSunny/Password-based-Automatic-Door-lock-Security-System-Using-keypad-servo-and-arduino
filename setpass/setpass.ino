#include<Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo; 
int pos = 0;

const int combinationlenght = 4;
char rightnumber[combinationlenght] = {'1','5','6','9'};
char newrightnumber[combinationlenght];
char number[combinationlenght];
int right = 0;
int green = A1;
int red = A2;
int newcomb = 0;
byte fulllcd[8] = {B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111,};
int newfinalcomb = 0;
int kposition = 0;
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(13,12,11,10,1,0);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  lcd.createChar(0, fulllcd);
  lcd.begin(16,2);
  lcdstartup();
}

void loop() {
  // put your main code here, to run repeatedly:
  char k = keypad.getKey();
  if(k != 0){ //if you press something
   if(k == '0')
   {
    kposition = 0;
    lcdstartup();
    Serial.println(k);
  }
  else{
    number[kposition] = k; //save number in array
    kposition++; //add to the combination digit position
    lcd.setCursor(kposition - 1,1);
    lcd.print("*");//writes a * each time you enter in a charcter
    Serial.println(k);
  delay(50);  //delay just cause i can
  if(kposition == combinationlenght){ //checks if we pressed 4 numbers
   kposition = 0;  //sets array write position to 0
   for(int g=0;g<combinationlenght;g++){//if each digit is right, add to the variable "right"
    if(number[g] == rightnumber[g]){ right++;} //checks if all inputed digits are right
    }
    if(right == combinationlenght){
      rightaction();
      rightlcd();
      right = 0;
      }
    else{
      wrongaction();
      wronglcd();
      right = 0;
      }
   delay(100);
  }
  }
  }
}
void lcdstartup(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Combination :");
  Serial.println("Combination :");
}
void lcdenter(){
  lcd.clear();
  lcd.print("Enter new :");
  Serial.println("Enter new :");
}
void lcdgranted(){
 lcd.clear();
 lcd.print("*****ACESS******");
 Serial.println("access :");
 lcd.setCursor(0,1);
 lcd.print("****GRANTED*****");
 Serial.println("granted :");
}
void rightlcd(){
 lcdgranted();
 while(newfinalcomb == 0){
  delay(10);
  char o = keypad.getKey();
  if(o != 0){
    if(o == '*')
    {
      digitalWrite(green,LOW);
      lcdenter();
      while(newcomb == 0){
      enternewcode();}
      newcomb = 0;
    }
    if(o == '0')
    {
      newfinalcomb = 1;
      digitalWrite(green,LOW);
    }
  }
  }
  newfinalcomb = 0;
 lcd.clear();
 lcdstartup();
}
void enternewcode(){
 char newk = keypad.getKey();
 if(newk != 0){
    newrightnumber[kposition] = newk;
    kposition++;
    lcd.setCursor(kposition,1);
    lcd.print(newk);
    if(newk == '0')
    {
    lcd.setCursor(0,1);
    lcd.print("        ");
    kposition = 0;
    }
    if(kposition == combinationlenght){
      lcd.setCursor(kposition + 1,1);
      lcd.write(byte(0));
      delay(1000);
      kposition = 0;
      checknewcode();
    }
 }
}
void checknewcode(){
  lcd.clear();
  lcd.print("Are you sure ?");
  Serial.println("are you sure? :");
  while(newcomb == 0){
    char newc = keypad.getKey();
    if(newc != 0){
      if(newc == '#')
      {
        lcd.clear();
        lcd.print("New code");
        Serial.println("new code :");
        lcd.setCursor(0,1);
        lcd.print("Accepted");
        Serial.println("accepted :");
        newcomb = 1;
        newfinalcomb = 1;
        for(int j=0;j<combinationlenght;j++){
          rightnumber[j] = newrightnumber[j];
          }
          kposition = 0;
          delay(1500);
      }
      if(newc == '9')//B
      {
        delay(10);
        lcdgranted();
        newcomb = 1;
      }
    }
  }
}
void wronglcd(){
lcd.clear();
 lcd.print("*****ACESS******");
 Serial.println("access");
 lcd.setCursor(0,1);
 lcd.print("*****DENIED*****");
 Serial.println("denied");
 while(newfinalcomb == 0){
  delay(10);
  char o = keypad.getKey();
  if(o != 0){
    if(o == '0')//D
    {
      newfinalcomb = 1;
    }
  }
  }
  newfinalcomb = 0;
 lcd.clear();
 lcdstartup();
 digitalWrite(red,LOW);
}

void rightaction(){
      digitalWrite(green,HIGH);
      digitalWrite(red,LOW);
      for (pos = 0; pos <= 90; pos += 1) 
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
void wrongaction(){
      digitalWrite(red,HIGH);
      digitalWrite(green,LOW);
}

