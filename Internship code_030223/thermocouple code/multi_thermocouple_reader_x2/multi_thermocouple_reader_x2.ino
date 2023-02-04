// this example is public domain. enjoy! https://learn.adafruit.com/thermocouple/

//check pins no.s, optimezed for 2 readers rn

#include "max6675.h"

int thermo1DO = 4;
int thermo1CS = 5;
int thermo1CLK = 6;

int thermo2DO = 8;
int thermo2CS = 9;
int thermo2CLK = 10;



MAX6675 thermocouple1(thermo1CLK, thermo1CS, thermo1DO);
MAX6675 thermocouple2(thermo2CLK, thermo2CS, thermo2DO);

void setup() {
  Serial.begin(9600);

  
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp

  
  Serial.print("1C = "); 
  Serial.println(thermocouple1.readCelsius());
 
  Serial.print("2C = "); 
  Serial.println(thermocouple2.readCelsius());


  // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(5000);
}
