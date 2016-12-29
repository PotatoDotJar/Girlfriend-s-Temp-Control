#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// You'll need these ^^^


#define ONE_WIRE_BUS 8 // Pin for temperature sensor

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int heaterGate = 9; // Pin for PWM Mosfet drive

float desiredTemp = 70; // Set your temp here!
//float error = 0;

void setup(void)
{
  Serial.begin(9600);
  pinMode(heaterGate, OUTPUT);
  sensors.begin();
  lcd.begin(16, 2);
}
int control = 0;
void loop(void)
{
  sensors.requestTemperatures();
  lcd.clear();
  float temp = sensors.getTempFByIndex(0);
  lcd.setCursor(0, 0);
  lcd.print(temp);
  //error = abs(desiredTemp-temp);
  if(temp > 85) {
    control = 0;
  }
  else {
    if(desiredTemp > temp && control < 100) {
      control+=10;
    }
    else if(temp > desiredTemp && control > 0) {
      control-=10;
    }
    setHeatOutput(constrain(control, 0, 100));
  }
  lcd.setCursor(0, 1);
  lcd.print(control);

  delay(500);
  
}
int output = 0;
void setHeatOutput(int percentage) {
  output= map(percentage, 0, 100, 0, 255);
  analogWrite(heaterGate, output);
}

