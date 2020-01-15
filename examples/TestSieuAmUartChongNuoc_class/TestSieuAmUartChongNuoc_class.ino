/*

Chuong trinh test Sieu AM chong nuoc Uart (chân Uart đấu chéo ), 

Echo(Tx)----12 (uno)
Trig(Rx)----11 (uno)

*/

#include "Hshop_Waterproof_Ultrasonic.h"

Hshop_Ultrasonic sieuAm(11,12);           // default Mode 1
//Hshop_Ultrasonic sieuAm(11,12,2);       // Mode 2: get data every 100ms (if the next read time has timing < 800ms)
//Hshop_Ultrasonic sieuAm(11,12,3);       // Mode 3: get data when we need (The best mode to get data)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println(sieuAm.ping_cm());
  delay(300);
}
