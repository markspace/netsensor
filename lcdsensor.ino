/*
 * lcdsensor
 * Temp and light sensor
 * 
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// TMP36
int temperaturePin = 0;

//PhotoResistor Pin
int lightPin = 1; //the analog pin the photoresistor is 
                  //connected to
                  //the photoresistor is not calibrated to any units so
                  //this is simply a raw sensor value (relative light)
//LED Pin
int ledPin = 9;   //the pin the LED is connected to
                  //we are controlling brightness so 
                  //we use one of the PWM (pulse width
                  // modulation pins)
void setup()
{
  lcd.begin(16, 2);
}
 /*
 * loop() - this function will start after setup 
 * finishes and then repeat
 */
void loop()
{
 float lightVoltage = getVoltage(lightPin);
 float temperatureVoltage = getVoltage(temperaturePin);
 
 float temperature = (temperatureVoltage - 0.5) * 100.0;
 float lightKOhms = 10.0 / (5.0/lightVoltage - 1.0);
 float lightLux = 255.84 * pow(lightKOhms, -10/9);
 lcd.clear();
 
 lcd.print("Temp=");
 lcd.print(temperature);
 lcd.setCursor(0,1);
 lcd.print("LightLux=");
 lcd.print(lightLux);
 delay(1000);
}

float getVoltage(int pin) {
  return (analogRead(pin) * 0.004882814);
}
