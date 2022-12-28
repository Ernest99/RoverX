#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial bt(8, 9); // RX, TX
#define TempSen A0
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 16, 2);
int buzzer = 11;
int GasA0 = A3;
int sensorThreshold = 400;
int greenLed = 6;
int redLed = 7;
int blueLed = 13;




void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(GasA0, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  Serial.begin(9600);
  bt.begin(9600);
  lcd.begin();//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print(" WELCOME :)");
  lcd.setCursor(0, 1);
  lcd.print("I Am RoverX...");
  delay(5000);
  lcd.clear();

}
void loop() {
  int analogSensor = analogRead(GasA0);

  float TempValue = analogRead(TempSen);
  float TempRead = (TempValue * 500) / 1023;
  //  Serial.println(TempRead);
  delay(200);


  //  Serial.print("Pin A0: ");
  //  Serial.println(analogSensor);

  //gas start
  if (analogSensor > sensorThreshold)
  {
    tone(buzzer, 1000);
    digitalWrite(redLed, HIGH);
    //    Serial.print("Danger \n");
    lcd.setCursor(0, 0);
    lcd.print("Gas Detected   ");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(TempRead);
    lcd.print((char)223); //degree symbol
    lcd.print("C ");
    //    lcd.print("           ");
    digitalWrite(greenLed, LOW);
  }
  else
  {
    noTone(buzzer);
    //    Serial.print("Safe \n");
    lcd.setCursor(0, 0);
    lcd.print("No Gas Detected");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(TempRead);
    lcd.print((char)223); //degree symbol
    lcd.print("C ");
    //    lcd.print("           ");
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
  }

  //gas end



  //temperature start
  if (TempRead >= 40) {
    digitalWrite(greenLed, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Temp High");
    lcd.print("           ");
    tone(buzzer, 1000);
    digitalWrite(redLed, HIGH);
    delay(500);
    digitalWrite(redLed, LOW);
    noTone(buzzer);
    digitalWrite(blueLed, LOW);
  }

  else if (TempRead <= 25) {
    digitalWrite(greenLed, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Temp Low");
    lcd.print("           ");
    tone(buzzer, 1000);
    digitalWrite(blueLed, HIGH);
    delay(500);
    digitalWrite(blueLed, LOW);
    noTone(buzzer);
    digitalWrite(blueLed, LOW);
  }

  else {
    digitalWrite(blueLed, HIGH);
  }
  //temperature end

  //bluetooth Start
  bt.print(TempRead); //send distance to MIT App
  bt.print(";");
  bt.print(analogSensor); //send distance to MIT App
  bt.println(";");

  delay(1000);

}
