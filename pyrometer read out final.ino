#include "max6675.h"

int thermoPyroDO = 5; //choose pin numbers 
int thermoPyroCS = 6;
int thermoPyroCLK = 7; 
MAX6675 thermocouplePyro(thermoPyroCLK, thermoPyroCS, thermoPyroDO);

float laminatetemp = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("starting...");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
   
  Serial.print("1C = "); 
  Serial.println(thermocouplePyro.readCelsius());// code to read out temp
  laminatetemp = thermocouplePyro.readCelsius();
}
