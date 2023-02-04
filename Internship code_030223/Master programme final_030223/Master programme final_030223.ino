#include <ezButton.h>
#include <max6675.h>

//variables
int mouldtemp = 50; // degree C
float laminatetemp = 30; // degree C
bool RelayUpper = HIGH; //off
bool RelayLower = HIGH; //off

//process parameters
int processtemp = 30; // degree C
int processtime = 10000; // miliseconds

//Pyrometer parameters
int pyrotemprefreshrate = 2000; //miliseconds

//Mould heat controller parameters
int mouldtempbuffer = 10; // degree C
int mouldtemprefreshrate = 2000; //miliseconds
int tempHIGHlimit = mouldtemp + mouldtempbuffer; // degree C
int tempLOWlimit = mouldtemp - mouldtempbuffer; // degree C

//Motor parameters
const int dutyCycle = 200;
int motor1Stopped = 0;  // 0 is not stopped, 1 is stopped forward, 2 is stopped backwards
bool motor1Ena = true;
int stepsFoward = 200;




//Pin numbers
//mould thermocouples 
int TcUpperDO = 30;
int TcUpperCS = 28;
int TcUpperCLK = 26;
int TcLowerDO = 31;
int TcLowerCS = 29;
int TcLowerCLK = 27;

//pin no. for dual relay
#define RelayUpperPin 24
#define RelayLowerPin 25

//pin no. for pyrometer
int TcPyroDO = 39;
int TcPyroCS = 37;
int TcPyroCLK = 35;

//pin no. for motor control
#define enaPin 46
#define dirPin 44
#define stepPin 45

//pin no. for buttons and switches (also object initaliazation)
ezButton stopButton(53);
ezButton goButton(52);
ezButton limit1(A1);  
ezButton limit2(A2);


//objects 
//t/c 
MAX6675 TcUpper(TcUpperCLK, TcUpperCS, TcUpperDO);
MAX6675 TcLower(TcLowerCLK, TcLowerCS, TcLowerDO);
MAX6675 TcPyro(TcPyroCLK, TcPyroCS, TcPyroDO);





void setup() {
  Serial.println("TCD sequence"); 
  Serial.begin(9600);
  delay(500); //stabilize MAX6675 chip

  pinMode(RelayUpperPin, OUTPUT);
  pinMode(RelayLowerPin, OUTPUT);
  pinMode(enaPin, OUTPUT);        //enable motor 1  
  pinMode(stepPin, OUTPUT);        // pulse motor 1 
  pinMode(dirPin, OUTPUT);        // dir motor 1

  limit1.setDebounceTime(1);
  limit2.setDebounceTime(1);
  goButton.setDebounceTime(1);
  stopButton.setDebounceTime(1);
  
  disable();
  enable();
  directionNegative();
  moveStepper();
  delay(500);
  disable();
  stopStepper();
  enable();
  directionPositive();
  moveStepper();
  delay(500);
  stopStepper();
  disable();
  //Serial.begin(9600); Use for debugging
}





void loop() {
  limit1.loop();
  limit2.loop();
  goButton.loop();
  stopButton.loop();

  int stateGo = goButton.getStateRaw();
  int stateStop = stopButton.getStateRaw();
  int state1 = limit1.getStateRaw();
  int state2 = limit2.getStateRaw();

  //pin testing code
  // Serial.print("Pyrometer readout: "); Serial.println(TcPyro.readCelsius());
  // Serial.print("Thermocouple Lower Mould readout: "); Serial.println(TcLower.readCelsius());
  // Serial.print("Thermocouple Upper Mould readout: "); Serial.println(TcUpper.readCelsius()); 
  // Serial.print("Mould heat controller status: "); Serial.print(RelayLower); Serial.println(RelayUpper); 
  // Serial.print("Go button: ");Serial.print(stateGo); Serial.print(" Stop button: "); Serial.print(stateStop);Serial.print(" switch 1: "); Serial.print(state1); Serial.print(" switch 2: "); Serial.println(state2);
  // Serial.println(); Serial.println();


  // start sequence

  //go button
  do{
    if (stateGo == HIGH & stateStop == LOW) {   
      Serial.print(" ");
      Serial.print(stateGo);
      //reset go button press
      goButton.loop();
      stateGo = goButton.getStateRaw();

      //start transfer to press, direction Negative/CCW
      toOven();
      
      //read for laminate temp while heating
      do{
        PyrometerReadout();
        MouldHeaterControl();  
        Serial.print("Mould temp upper limit "); Serial.println(tempHIGHlimit); 
        Serial.print("Mould temp lower limit: "); Serial.println(tempLOWlimit);    
        Serial.print("Thermocouple Lower Mould readout: "); Serial.println(TcLower.readCelsius());
        Serial.print("Thermocouple Upper Mould readout: "); Serial.println(TcUpper.readCelsius()); 
        Serial.print("Mould heat controller status: "); Serial.print(RelayLower); Serial.println(RelayUpper); Serial.println(); Serial.println();
        //stopButton.loop();
        //int stateStop = stopButton.getStateRaw();
        //if (stateStop = LOW) {
        //  toPress();
        //  break;
        // }
      }while(laminatetemp < processtemp);

      //start counting process time until transfer to press
      delay(processtime);

      //update limit switch states
      limit1.loop();
      limit2.loop();
      state1 = limit1.getStateRaw();
      state2 = limit2.getStateRaw();
  
      //start transfer to press
      toPress(); 
      
    }
  } while (stateStop == HIGH);
}




//Pyrometer readout
void PyrometerReadout(){
  laminatetemp = TcPyro.readCelsius();
  //Serial.println(laminatetemp)
  delay(pyrotemprefreshrate);
  return laminatetemp;
}




//Motor coding
void toOven(){
  enable();
  directionNegative();
  moveStepper();
  limit1.loop();
  int state1 = limit1.getState();  
  do{
    limit1.loop();
    state1 = limit1.getState();
  } while(state1 == HIGH);
    
  analogWrite(stepPin, 0);
  digitalWrite(enaPin, HIGH);      
  stopStepper();
  disable();
}

void toPress(){
  enable();
  directionPositive();
  moveStepper();
  limit2.loop();
  int state2 = limit2.getState();

  do{
    limit2.loop();
    state2 = limit2.getState();
  } while(state2 == HIGH);
    
  analogWrite(stepPin, 0);
  digitalWrite(enaPin, HIGH);      
  stopStepper();
  disable();  
}

//disbable/enable coding
void disable(){
  digitalWrite(enaPin, HIGH);
  delay(10);
}

void enable(){
  if(motor1Ena){
    digitalWrite(enaPin, LOW);
  }
  delay(10);
}

//Stop start stepper coding
void moveStepper(){
  analogWrite(stepPin, dutyCycle);
}

void stopStepper(){
  analogWrite(stepPin, 0);
}

//direction coding
// Motor dir: HIGH = Clockwise, LOW = Anti Clockwise
void directionPositive(){
  digitalWrite(dirPin, HIGH);
  delay(10);
}

void directionNegative(){
  digitalWrite(dirPin, LOW);
  delay(10);
}




//Mould heat controller
void MouldHeaterControl(){

  int tempUpper = TcUpper.readCelsius();
  int tempLower = TcLower.readCelsius();
  
  //Serial.print(TcUpper.readCelsius());
  //Serial.print(" ");
  //Serial.println(TcLower.readCelsius());
  
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
}