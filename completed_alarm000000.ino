
#include<EEPROM.h>
#include <RTClib.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 5, 4, 3, 2);
RTC_DS1307 RTC;
int temp, inc, hours1, minut, add = 11;

int next = 10;
int INC = 9;
int set_mad = 8;
int reset = A2;
#define LED1 A0//you can write it as buzzer also, in the place of LED
#define LED2 A1
#define LED3 A3
#define LED4 11
#define buzzer 7

int HOUR, MINUT, SECOND;


void setup()
{
  
  RTC.begin();
  lcd.begin(16, 2);
  pinMode(INC, INPUT);//buttons
  pinMode(next, INPUT);//buttons
  pinMode(set_mad, INPUT);//buttons
   pinMode(reset, INPUT);
  pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
   pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
   pinMode(buzzer, OUTPUT);//buzzer out put pin 6//you can write it as buzzer also, in the place of LED
  digitalWrite(next, HIGH);
  digitalWrite(set_mad, HIGH);
  digitalWrite(INC, HIGH);
   digitalWrite(reset, HIGH);
  digitalWrite(LED1, LOW);//you can write it as buzzer also, in the place of LED
   digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
     digitalWrite(buzzer, LOW);
  lcd.setCursor(3, 0);
  lcd.print("SKILL SKU ");
  delay(3000);

 // if (!RTC.isrunning())
  //{
   RTC.adjust(DateTime(__DATE__, __TIME__));//set the date manually
    RTC.adjust(DateTime(2019, 2, 5, 13,11, 0));//set the date manually
  //}
}

void loop()
{
  DateTime now = RTC.now(   );
   if(digitalRead(set_mad) == 0)      //set medicine time
   { 
     lcd.setCursor(0,0);
   lcd.print("****(set)*******");
   lcd.setCursor(0,1);
   lcd.print("####[Alarms]######");
    delay(1000);
     lcd.print("alarm 1");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Alarm 1");
    delay(1000);
    defualt();
    time(1);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Alarm 2");
    defualt();
    delay(1000);
    time(2);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Alarm 3");
     delay(1000);
    defualt();    
    time(3);
    //delay(1000);
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Alarm 4");
     delay(1000);
    defualt();
    time(4);
    lcd.clear();
     lcd.setCursor(4,0);
   lcd.print("Alarm");
   lcd.setCursor(2,1);
   lcd.print("has been set  ");
    delay(2000);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time:");
  lcd.setCursor(6, 0);
  lcd.print(HOUR = now.hour(), DEC);
  lcd.print(":");
  lcd.print(MINUT = now.minute(), DEC);
  lcd.print(":");
  lcd.print(SECOND = now.second(), DEC);
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  lcd.print(now.day(), DEC);
  lcd.print("-");
  lcd.print(now.month(), DEC);
  lcd.print("-");
  lcd.print(now.year(), DEC);
  match();//very important. if it is delay then doesn't beep beep...
  delay(200);
}
void defualt()
{
  lcd.setCursor(0,1);
  lcd.print(HOUR);
  lcd.print(":");
  lcd.print(MINUT);
  lcd.print(":");
  lcd.print(SECOND);
}

void time(int x)
{
  int temp = 1; //minuts = 0, hours = 0, seconds = 0;//important ,because if it is delay or comment ,you doesn't set alarm
while (temp == 1)
  {
    if (digitalRead(INC) == 0)//change for hours on alarm,don't comment this
    {
      HOUR++;
      if (HOUR == 24)//per day 24 hours
      {
        HOUR = 0;//don't comment this because,hours starts with 0hours
      }
      while (digitalRead(INC) == 0);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter hour");
   // lcd.clear();//lcd.print(x); 
    lcd.setCursor(0, 1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
  if (digitalRead(next) == 0)
    {
      hours1 = HOUR;
      EEPROM.write(add++, hours1);//stores the hours data
      temp = 2;//don't change the value
     while (digitalRead(next) == 0);//dont't comment this because ,it doesn't move hours to minuts at the time of alarm setting
    }
  }

  while (temp == 2)
  {
    if (digitalRead(INC) == 0)
    {
      MINUT++;
     if (MINUT == 60)
      { 
       MINUT = 0;
      }
      while (digitalRead(INC) == 0);
    }
    // lcd.print("alarm 1");                          
    //delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
   
    //lcd.clear();
    lcd.print("Enter minuts   ");
    lcd.setCursor(0,1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
    if (digitalRead(next) == 0)
    {
      minut = MINUT;
      EEPROM.write(add++, minut);
      temp = 0;
      while (digitalRead(next) == 0);
    }
  }
  delay(1000);
}

void match()
{
  int tem[20];
  for (int i =11; i < 20; i++)
  {
    tem[i] = EEPROM.read(i);
  }
  if (HOUR == tem[11] && MINUT == tem[12])
  {
    
    beep();//indicates times of sound
    beep();
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Before");
    lcd.setCursor(4, 1);
    lcd.print("breakfast");
     beep();
    beep();
    digitalWrite(LED1, HIGH);
    delay(100);//delay(100);
    digitalWrite(LED1, LOW);
    delay(100);
    while (digitalRead(reset) == 0)
      {
    
      digitalWrite(LED1, LOW);
       delay(50000);
           lcd.setCursor(0, 0);
      lcd.print("system reset");
      lcd.setCursor(0, 1);
       lcd.print("reset");
        //delay(6000);
  }
    
  }
   if (HOUR == tem[13] && MINUT == tem[14])
  {  
   beep();//indicates times of sound
    beep();
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("After");
    lcd.setCursor(3, 1);
   lcd.print("breakfast");
    ///delay(100);
    beep();
   beep();

    digitalWrite(LED2, HIGH);
    delay(100);//delay(100);
    digitalWrite(LED2, LOW);
    delay(100);
     while (digitalRead(reset) == 0)
  {
      digitalWrite(LED2, LOW);
      delay(50000);
           lcd.setCursor(0, 0);
      lcd.print("system reset");
      lcd.setCursor(0, 1);
       lcd.print("reset");
  }
  }
 if (HOUR == tem[15] && MINUT == tem[16])
 {
   beep();//indicates times of sound
    beep();
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Before");
    lcd.setCursor(4, 1);
    lcd.print("Lunch");
    //delay(100);
  beep();
      beep();
       digitalWrite(LED3, HIGH);
    delay(100);//delay(100);
    digitalWrite(LED3, LOW);
   delay(100);
    while (digitalRead(reset) == 0)
  {
      digitalWrite(LED3, LOW);
      delay(50000);
           lcd.setCursor(0, 0);
      lcd.print("system reset");
      lcd.setCursor(0, 1);
       lcd.print("reset");
  }
  
  }
   if (HOUR == tem[17] && MINUT == tem[18])
  {
    
   beep();//indicates times of sound
   beep();
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("After");
    lcd.setCursor(4, 1);
    lcd.print("Lunch");
    //delay(100);
    beep();
   beep();

   digitalWrite(LED4, HIGH);
   delay(100);delay(100);
    digitalWrite(LED4, LOW);
    delay(100);
    while (digitalRead(reset) == 0)
  {
      digitalWrite(LED4, LOW);
      delay(50000);
           lcd.setCursor(0, 0);
      lcd.print("system reset");
      lcd.setCursor(0, 1);
       lcd.print("reset");
     
  }

  }
}


void beep()
{

  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
}
