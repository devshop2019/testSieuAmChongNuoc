/*

Chuong trinh test Sieu AM chong nuoc Uart (chân Uart đấu chéo ), 

Tx(cb)----11 (uno)
Rx(cb)----12 (uno)






























































*/
#include "SoftwareSerial.h"

SoftwareSerial sieuAm(11,12);
uint8_t sieuAm_Value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sieuAm.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(readSieuAm_available()){
    delay(120);
  }
}

bool readSieuAm_available(){
  uint8_t temBuffer[4];
  if(sieuAm.available()){
    sieuAm.readBytes(temBuffer, 4);

    int sum = temBuffer[0] + temBuffer[1] + temBuffer[2];
    if((uint8_t)sum == temBuffer[3]){
      sieuAm_Value = (temBuffer[1] << 8) + temBuffer[2];
      Serial.println(String(sieuAm_Value/10.0f) + " cm" );
      return true;
    }
  }
  return false;
}
