// Define pin numbers
#include<LiquidCrystal.h>
#include <Servo.h>
Servo servoStart;
LiquidCrystal lcd(11,10, 7, 6, 5, 4);
const int sensorPin = 3;// Pin connected to the button  
const int servo= A1;
const int Redled = 12;
const int Blueled = 9;
const int Greenled = 8;
const int alarmPin= 13;
int state = 0;

void setup() {
  pinMode(sensorPin, INPUT);// Set the sensor pin as input
  pinMode(alarmPin, OUTPUT);
  servoStart.attach(servo);
  servoStart.write(0);
  pinMode(Redled, OUTPUT);// Set the alarm pin as output
  pinMode(Blueled, OUTPUT);
  pinMode(Greenled, OUTPUT);
  lcd.begin(16, 2);
  
 attachInterrupt(digitalPinToInterrupt(sensorPin), change1, FALLING);
}

void change1(){
    tone(alarmPin, 252);// Turn on the alarm
    setColor(255,0,0);
    servoStart.write(180);
  	state = 1;
}

void setColor(int red,int blue,int green){
  analogWrite(Redled, red);
  analogWrite(Blueled, blue);
  analogWrite(Greenled, green);
  
}

void loop() {
  if (state == 1){
    lcd.setCursor(0,0);          
  	lcd.print("Door is Opened!!");
    lcd.setCursor(0,1);
    lcd.print("Door is Closing!");
  	delay(3000);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Door is Closed");
	noTone(alarmPin);// Turn off the alarm
	setColor(0,0,255);
    servoStart.write(0);
    state = 0;
 
}
  else {
	noTone(alarmPin);// Turn off the alarm
	setColor(0,0,255);
    servoStart.write(0);
    lcd.setCursor(1,0);
  	lcd.print("Door is Closed"); 
  }
}

