#include "max6675.h"

//Check pins align with corresponding ports on thermocouple and are powered correctly
 
int thermo1SO = 53;
int thermo1CS = 51;
int thermo1SCK = 49;

int thermo2SO = 52;
int thermo2CS = 50;
int thermo2SCK = 48;

int thermo3SO = 47;
int thermo3CS = 45;
int thermo3SCK = 43;

int thermo4SO = 46;
int thermo4CS = 44;
int thermo4SCK = 42;

int thermo5SO = 41;
int thermo5CS = 39;
int thermo5SCK = 37;

int thermo6SO = 40;
int thermo6CS = 38;
int thermo6SCK = 36;

MAX6675 thermocouple1(thermo1SCK, thermo1CS, thermo1SO);
MAX6675 thermocouple2(thermo2SCK, thermo2CS, thermo2SO);
MAX6675 thermocouple3(thermo3SCK, thermo3CS, thermo3SO);
MAX6675 thermocouple4(thermo4SCK, thermo4CS, thermo4SO);
MAX6675 thermocouple5(thermo5SCK, thermo5CS, thermo5SO);
MAX6675 thermocouple6(thermo6SCK, thermo6CS, thermo6SO);


void setup() {
  Serial.begin(9600);

  Serial.println("MAX 6675 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
 
 
  Serial.print(thermocouple1.readCelsius());
  Serial.print(","); 
  Serial.print(thermocouple2.readCelsius());
  Serial.print(","); 
  Serial.print(thermocouple3.readCelsius());
  Serial.print(","); 
  Serial.print(thermocouple4.readCelsius());
  Serial.print(","); 
  Serial.print(thermocouple5.readCelsius());
  Serial.print(","); 
  Serial.println(thermocouple6.readCelsius());

// For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(5000);
}
