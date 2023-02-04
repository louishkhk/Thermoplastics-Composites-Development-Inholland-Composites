#include <ezButton.h>


ezButton Button1(A1);
ezButton Button2(A2);
ezButton Limit1(A3);

void setup() {
 delay(10);
 Serial.begin(9600);

 Button1.setDebounceTime(5);
 Button2.setDebounceTime(5);
 Limit1.setDebounceTime(5);
}

void loop() {
  Limit1.loop();
  Button1.loop();
  Button2.loop();

 int stateb1 = Button1.getState();
 int stateb2 = Button2.getState();
 int statelimit = Limit1.getState();


  Serial.print(stateb1);
  Serial.print("      ");
  Serial.print(stateb2);
  Serial.print("      ");
  Serial.println(statelimit);
}
