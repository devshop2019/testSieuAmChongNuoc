/*
[link]: https://hshop.vn/products/cam-bien-sieu-am-chong-nuoc-ultrasonic-jsn-sr04t

Chuong trinh test Sieu AM chong nuoc Uart (chân Uart đấu chéo ), 

Echo(Tx)----12 (uno)
Trig(Rx)----11 (uno)

*/

#include "Hshop_Waterproof_Ultrasonic.h"

Hshop_Ultrasonic Hshop_Waterproof_Ultrasonic(11,12);           // default Mode 1
//Hshop_Ultrasonic Hshop_Waterproof_Ultrasonic(11,12,2);       // Mode 2: get data every 100ms (if the next read time has timing < 800ms)
//Hshop_Ultrasonic Hshop_Waterproof_Ultrasonic(11,12,3);       // Mode 3: get data when we need (The best mode to get data)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hshop.vn test Waterproof Ultrasonic");
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("Testing with Mode " + Hshop_Waterproof_Ultrasonic.getMode() + ",with R27 = " + Hshop_Waterproof_Ultrasonic.getR27() + "\tvalue: ");
  Serial.println(Hshop_Waterproof_Ultrasonic.ping_cm());
  delay(300);
}