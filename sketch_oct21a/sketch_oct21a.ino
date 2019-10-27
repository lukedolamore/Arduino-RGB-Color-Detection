#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define s0 4 //Grey Wire
#define s1 5 //Purple 
#define s2 6 //Yellow
#define s3 7 //Green
#define outPin 8 //Orange

//RGB
int red_light = 12; //Red
int green_light = 11; //Green
int blue_light = 10; //Blue

//Buzzer
const int buzzer = 9; //Orange

//Button
const int button = 2; //White

int red, green, blue;
String color = "";
long start = 0;
long elapsed = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(outPin, INPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
  pinMode(red_light, OUTPUT);
  pinMode(green_light, OUTPUT);
  pinMode(blue_light, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  
  start = millis();
}

void loop() {

  while(digitalRead(button) == HIGH)
  {
    lcd.backlight();
    runProgram(); 
  }
  if(digitalRead(button) == LOW)
  {
    red = 255;
    green = 255;
    blue = 255;
    RGB_color(0, 0, 0);
    lcd.noBacklight();  
    lcd.clear();  
    noTone(buzzer);   
  }
}

void runProgram()
{
    findColor();
  elapsed = millis() - start;
  if (elapsed > 1000)
  {
    showDataLCD();
    start = millis();
  }
}

void readRGB()
{
  red = 0;
  green = 0;
  blue = 0;
  int n = 10;
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  red = red + pulseIn(outPin, LOW);

  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  green = green + pulseIn(outPin, LOW);

  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  blue = blue + pulseIn(outPin, LOW);
}//readRGB

void findColor()
{
  readRGB();
  if (red > 8 && red < 23 && green > 20 && green < 33 && blue > 24 && blue < 30)
  {
    color = "WHITE"; 
    RGB_color(255, 255, 255);
    noTone(buzzer);
  }
  else if (red > 20 && red < 31 && green > 57 && green < 70 && blue > 45 && blue < 59)
  {
    color = "RED";
    RGB_color(255, 0, 0);
    noTone(buzzer);
  }
  else if (red > 50 && red < 62 && green > 48 && green < 54 && blue > 54 && blue < 69)
  {
    color = "GREEN";
    RGB_color(0, 255, 0);
    noTone(buzzer);
  }
  else if (red > 10 && red < 25 && green > 10 && green < 36 && blue > 30 && blue < 55)
  {
    color = "YELLOW";
    RGB_color(255, 255, 0);
    noTone(buzzer);
  }
  else if (red > 60 && red < 125 && green > 65 && green < 115 && blue > 32 && blue < 65)
  {
    color = "BLUE";
    RGB_color(0, 0, 255);
    noTone(buzzer);
  }
  else if (red > 25 && red < 30 && green > 66 && green < 79 && blue > 39 && blue < 49)
  {
    color = "PINK";
    RGB_color(255, 125, 255);
    noTone(buzzer);
  }
  else if (red > 54 && red < 64 && green > 43 && green < 52 && blue > 29 && blue < 37)
  {
    color = "CYAN";
    RGB_color(0, 255, 255);
    noTone(buzzer);
  }
  else
  {
    color = "NO COLOR";
    RGB_color(0, 0, 0);
    tone(buzzer, 1000);
  }
}//findColor

void showDataLCD(void)
{
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print("R");
  lcd.setCursor (1,0);
  lcd.print("    ");
  lcd.setCursor (1,0);
  lcd.print(red);
  lcd.setCursor (5,0);
  lcd.print(" G");
  lcd.setCursor (7,0);
  lcd.print("    ");
  lcd.setCursor (7,0);
  lcd.print(green);
  lcd.setCursor (12,0);
  lcd.print("B");
  lcd.setCursor (13,0);
  lcd.print("    ");
  lcd.setCursor (13,0);
  lcd.print(blue);
  
  lcd.setCursor (0,1);
  lcd.print("Color: ");
  lcd.setCursor (7,1); 
  lcd.print("        ");
  lcd.setCursor (7,1);  
  lcd.print(color);
  
}//showDataLCD

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(red_light, red_light_value);
  analogWrite(green_light, green_light_value);
  analogWrite(blue_light, blue_light_value);
}//RGB_color
