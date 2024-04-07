#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
Servo servo_12;
#define led 13
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {8, 9, 10, 11}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A1, A2, A3, A4}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char StorePass[]="*AC#090"; //The correct password
int i=0,count=0,number=sizeof(StorePass)-1;
char pass[sizeof(StorePass)-1];

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(" Enter Password ");
  lcd.setCursor(0, 1);
  pinMode(led,OUTPUT);
}

void loop() 
{
  char key = keypad.getKey();
  
  if (key && key!='D')
  {
    lcd.print('*'); //print "*" for any clicken key from the keypad for more security
    pass[i]=key;
    i++;
  }else if(key=='D') //"D" is like Enter button when entering the password in any website
  {
    if(i==number)
    {
      for(int j=0;j<number;j++)
      {
        if(pass[j]==StorePass[j])count++;
      }
      if(count==number)
      {
        lcd.clear();
        digitalWrite(led,HIGH);
        lcd.setCursor(0,0);
        lcd.print("Correct Password");
        servo_12.attach(12);
        servo_12.write(90);
        delay(2000);
        i=0;
        count=0;
        lcd.setCursor(0,0);
        lcd.print(" Enter Password ");
        lcd.setCursor(0,1);
      }else
      {
        printt();
      }
    }else
    {
      printt();
    }
  }
}

void printt()
{
        lcd.clear();
        digitalWrite(led,LOW);
        lcd.setCursor(0,0);
        lcd.print(" Wrong Password");
        servo_12.write(0);
        delay(2000);
        lcd.setCursor(0,1);
        lcd.print("Try Again In");
        lcd.setCursor(13,1);
        lcd.print("10!");
        delay(1000);
        for(int k=9;k>=0;k--)
        {
          lcd.setCursor(13,1);
    lcd.print(0);
            lcd.print(k);
    delay(1000);
    }
        lcd.clear();
        i=0;
        count=0;
        lcd.setCursor(0,0);
        lcd.print(" Enter Password ");
        lcd.setCursor(0,1);
}
