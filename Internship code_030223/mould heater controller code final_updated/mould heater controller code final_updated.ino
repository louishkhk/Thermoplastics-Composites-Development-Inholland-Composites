#include <max6675.h>

int tempHIGHlimit = 30;
int tempLOWlimit = 25;
int mouldtemprefreshrate = 4000; //miliseconds

//pins
int TcUpperDO = 30;
int TcUpperCS = 28;
int TcUpperCLK = 26;
int TcLowerDO = 31;
int TcLowerCS = 29;
int TcLowerCLK = 27;

int RelayUpper = 24;
int RelayLower = 25;

MAX6675 TcUpper(TcUpperCLK, TcUpperCS, TcUpperDO);
MAX6675 TcLower(TcLowerCLK, TcLowerCS, TcLowerDO);

void setup() {
  Serial.begin(9600);
  delay(500);

  pinMode(RelayUpper, OUTPUT);
  pinMode(RelayLower, OUTPUT);
}

void loop() {

  int tempUpper = TcUpper.readCelsius();
  int tempLower = TcLower.readCelsius();
  delay(250);
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
  delay(mouldtemprefreshrate);

  // //Dubugging code below 
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
