/*
 * Netsensor
 * Temp and lught sensor on the net
 * 
 */

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0xFC, 0xA0};
IPAddress ip(192,168,100,87);

int doserial = 0;

EthernetServer server(80);

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
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); //sets the led pin to output
  Ethernet.begin(mac, ip);
  server.begin();
}
 /*
 * loop() - this function will start after setup 
 * finishes and then repeat
 */
void loop()
{
 float lightVoltage = getVoltage(lightPin);
 float temperatureVoltage = getVoltage(temperaturePin);
 
 int temperature = (temperatureVoltage - 0.5) *100;
 float lightKOhms = 10.0 / (5.0/lightVoltage - 1.0);
 float lightLux = 255.84 * pow(lightKOhms, -10/9);
 
 if (doserial) {
  Serial.print("Temp=");
  Serial.print(temperature);
  Serial.print("  Light=");
  Serial.println(lightVoltage);
  Serial.print("  LightKOhms=");
  Serial.print(lightKOhms); 
  Serial.print("  LightLux=");
  Serial.println(lightLux);
  delay(1000);
 }
 //lightLevel = map(lightLevel, 500, 900, 0, 255); 
         //adjust the value 0 to 900 to
         //span 0 to 255

 //lightLevel = constrain(lightLevel, 0, 255);//make sure the 
                                           //value is betwween 
                                           //0 and 255
 //analogWrite(ledPin, lightLevel);  //write the value

 EthernetClient client = server.available();
 if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.print("Temperature: ");
          client.print(temperature);
          client.println(" C<br />");
          client.print("Light: ");
          client.print(lightLux);
          client.println(" lux<br />");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}

float getVoltage(int pin) {
  return (analogRead(pin) * 0.004882814);
}
