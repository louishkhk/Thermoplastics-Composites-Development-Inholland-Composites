// this example is public domain. enjoy! https://learn.adafruit.com/thermocouple/

#include "max6675.h"

int thermo1DO = 5;
int thermo1CS = 6;
int thermo1CLK = 7;




MAX6675 thermocouple1(thermo1CLK, thermo1CS, thermo1DO);


void setup() {
  Serial.begin(9600);

  Serial.println("starting...");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp

  
  Serial.print("1C = "); 
  Serial.println(thermocouple1.readCelsius());



  // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(250);
}
