//Code by Leonard Henry Phelan IV
//Currently all rights reserved
//leonardhphelaniv@gmail.com

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

//Defenitions for I2C display

#define I2C_ADDR       0x3F
#define BACKLIGHT_PIN  3
#define En_pin         2
#define Rw_pin         1
#define Rs_pin         0
#define D4_pin         4
#define D5_pin         5
#define D6_pin         6
#define D7_pin         7

//Pin variables, preprocesor directive for speed

//Button
#define btn            10

//Pezio Buzzer
#define pez            8

//LED
#define led            13

//Coin acceptor
#define cac            12

//Credit reset button
#define rst            6

//Servo pin
#define svo            9

//Credit counter
int credits = 0;

//Used for For(){} statements
int i = 0;

//[P]ulse [C]ount
int pc = 0;

//[D]elay [C]ount
int dc = 0;

Servo servo;

boolean once = false;

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

//Various title screens of LCD

void title1 ()
{
  lcd.clear();
  lcd.home();
  lcd.print("Welcome to Lenny's");
  lcd.setCursor(0,1);
  lcd.print("Bathroom! There is a");
  lcd.setCursor(0,2);
  lcd.print("50c admission fee.");
  lcd.setCursor(0,3);
  lcd.print("Please insert coins.");
}

void title2 ()
{
  lcd.clear();
  lcd.home();
  lcd.print("In event of theft,");
  lcd.setCursor(0,1);
  lcd.print("buzzer will sound");
  lcd.setCursor(0,2);
  lcd.print("until your visit");
  lcd.setCursor(0,3);
  lcd.print("has been paid for.");
}

void title3 ()
{
  lcd.clear();
  lcd.home();
  lcd.print("Design copyright (C)");
  lcd.setCursor(0,1);
  lcd.print("2014 by Leonard");
  lcd.setCursor(0,2);
  lcd.print("Henry Phelan IV.");
  lcd.setCursor(0,3);
  lcd.print("(774) 994-3082");
}

//Screen when coins are inserted... Constantly refreshes

void credit1 ()
{
  lcd.home();
  lcd.print(" :Credits inserted:");
  lcd.setCursor(1,2);
  lcd.print("<<===--    --===>>");
  lcd.setCursor(9,2);
  if (credits < 10) {lcd.print("0");}
  lcd.print(credits);
}

/*
int pulse ()
{
  while (!digitalRead(cac) && once == false) {}
  once = true;
  while (digitalRead(cac)) {}
  while (!digitalRead(cac)) {
    delay(1);
    i++;
    if (i > 100) {
      if (pc == 1) {return 25;}
      if (pc == 2) {return 10;}
      if (pc == 3) {return 5;}
    }
  }
  pc++;
}*/

int pulse ()
{
  pc = 0;
pcloop:
  while (!digitalRead(cac)) {}
  dc = 0; pc++;
  while (digitalRead(cac))  {
    delay(1)
    dc++;
    if (dc > 100 || pc == 3) {
      goto end;
    }
  }
  goto pcloop;
end:
  if (pc == 1) {return 25;}
  if (pc == 2) {return 10;}
  if (pc == 3) {return  5;}
}

void setup()
{
  servo.attach(svo);
  lcd.begin (20,4,LCD_5x8DOTS);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  pinMode(btn, INPUT_PULLUP);
  pinMode(pez, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(cac, INPUT);
  pinMode(rst, INPUT_PULLUP);
}

void loop()
{
  while(!digitalRead(cac)) {
    title1();
    timeout();
    title2();
    timeout();
    title3();
    timeout();
    lcd.clear();
  }
  while (credits < 50) {
    credits += pulse();
    credit1();
  }
}

void timeout()
{
  for (int i = 0; i <= 5000; i++) {
    if (digitalRead(cac)) {
      break;
    }
    delay(1);
  }
}
