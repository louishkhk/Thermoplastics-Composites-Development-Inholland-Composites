#include <max6675.h>

int tempHIGHlimit = 30;
int tempLOWlimit = 25;

//pins
int thermoUpperDO = 4;
int thermoUpperCS = 5;
int thermoUpperCLK = 6;
int thermoLowerDO = 8;
int thermoLowerCS = 9;
int thermoLowerCLK = 10;

int RelayUpper = 11;
int RelayLower = 12;

MAX6675 TcUpper(thermoUpperCLK, thermoUpperCS, thermoUpperDO);
MAX6675 TcLower(thermoLowerCLK, thermoLowerCS, thermoLowerDO);

void setup() {
  Serial.begin(9600);
  delay(500);

  pinMode(RelayUpper, OUTPUT);
  pinMode(RelayLower, OUTPUT);
  }

void loop() {

  int tempUpper = TcUpper.readCelsius();
  int tempLower = TcLower.readCelsius();
  
  Serial.print(TcUpper.readCelsius());
  Serial.print(" ");
  Serial.println(TcLower.readCelsius());
  
  // LOW = ON, HIGH = OFF

  if (tempUpper > tempHIGHlimit) {
    digitalWrite(RelayUpper, HIGH); //Off
  }

  if (tempLower > tempHIGHlimit) {
    digitalWrite(RelayLower, HIGH); //off
  }

  if (tempUpper < tempLOWlimit) {
    digitalWrite(RelayUpper, LOW); //on
  }

  if (tempLower < tempLOWlimit) {
    digitalWrite(RelayLower, LOW); //on
  }
  delay(5000);
  // digitalWrite(RelayUpper, LOW);
  // digitalWrite(RelayLower, HIGH);
  // delay(5000);
  // digitalWrite(RelayUpper, HIGH);
  // digitalWrite(RelayLower, LOW);
  // delay(5000);
  // digitalWrite(RelayUpper, HIGH);
  // digitalWrite(RelayLower, HIGH);
  // delay(5000);
  // digitalWrite(RelayUpper, LOW);
  // digitalWrite(RelayLower, LOW);
  // delay(5000);
}
