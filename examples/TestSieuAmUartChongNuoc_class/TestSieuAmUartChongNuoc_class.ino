/*

Chuong trinh test Sieu AM chong nuoc Uart (chân Uart đấu chéo ), 

Tx(cb)----11 (uno)
Rx(cb)----12 (uno)






























































*/

#define db_sa(...)        { Serial.println(__VA_ARGS__); }
#define db_sa_t(...)      {Serial.print(__VA_ARGS__);Serial.print("\t");}
#define db_sa_t(...)

#include "SoftwareSerial.h"

class Hshop_Ultrasonic{
  public:
    Hshop_Ultrasonic(uint8_t _Trig_RX_, uint8_t _Echo_TX_, uint8_t _mode_ = 1);
    int ping_cm();
    void begin();
  private:
    unsigned long lastTime;
    uint8_t trigRX;
    uint8_t echoTX;
    uint8_t mode;
    int value_mm;
    int lastvalue_mm;
    
    const uint8_t numReadings = 4;
    int readings[4];      // the readings from the Serial
    int readIndex = 0;              // the index of the current reading
    int total = 0;                  // the running total
    
    SoftwareSerial * sieuam;
    
    bool readSieuAm_available2(){
      if(!sieuam)this->begin();
      while(sieuam->available()){
        total = total - readings[readIndex];
        // read from the serial:
        readings[readIndex] = sieuam->read();
        // add the reading to the total:
        total = total + readings[readIndex];
        // advance to the next position in the array:
        readIndex = readIndex + 1;
      
        // if we're at the end of the array...
        if (readIndex >= numReadings) {
          readIndex = 0;
        }
        
        db_sa_t(readings[3], HEX);
        db_sa_t(readings[2], HEX);
        db_sa_t(readings[1], HEX);
        db_sa_t(readings[0], HEX);
//          db_sa(value_mm);
        if(readings[0] != 0xff) return false;
        int sum = readings[3] + readings[1] + readings[2];
        if((uint8_t)sum == readings[0]){
          value_mm = (readings[2] << 8) + readings[1];
          lastvalue_mm = value_mm;
          
          return true;
        }
      }
      return false;
    }
    
    bool readSieuAm_available(){
      uint8_t temBuffer[4];
      if(sieuam->available()){
        sieuam->readBytes(temBuffer, 4);
        db_sa_t(temBuffer[0], HEX);
        db_sa_t(temBuffer[1], HEX);
        db_sa_t(temBuffer[2], HEX);
//          db_sa(value_mm);
    
        int sum = temBuffer[0] + temBuffer[1] + temBuffer[2];
        if((uint8_t)sum == temBuffer[3]){
//          while(sieuam->available())sieuam->read();
          value_mm = (temBuffer[1] << 8) + temBuffer[2];
          lastvalue_mm = value_mm;
          
//          Serial.println(sieuAm_Value);
          return true;
        }
      }
      return false;
    }
    
    
};

Hshop_Ultrasonic::Hshop_Ultrasonic(uint8_t _Trig_RX_, uint8_t _Echo_TX_, uint8_t _mode_){
  trigRX = _Trig_RX_;
  echoTX = _Echo_TX_;
  mode = _mode_;
  
}

void Hshop_Ultrasonic::begin(){
  if((mode == 2) || (mode == 3))
    if(!sieuam){
      delete sieuam;
      sieuam = new SoftwareSerial(trigRX, echoTX);
      sieuam->begin(9600);
    }
}

int Hshop_Ultrasonic::ping_cm(){
  switch(mode){
    case 3:
    
    case 2:
      readSieuAm_available();
      return lastvalue_mm/10;
      break;
    default:
    return 0;
      break;
  }
}

Hshop_Ultrasonic sieuAm(11,12,2);
//SoftwareSerial sieuAm(11,12);
uint8_t sieuAm_Value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sieuAm.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
//  if(readSieuAm_available()){
//    delay(100);
//  }
  Serial.println(sieuAm.ping_cm());
  delay(50);
}

//bool readSieuAm_available(){
//  uint8_t temBuffer[4];
//  if(sieuAm.available()){
//    sieuAm.readBytes(temBuffer, 4);
//
//    int sum = temBuffer[0] + temBuffer[1] + temBuffer[2];
//    if((uint8_t)sum == temBuffer[3]){
//      sieuAm_Value = (temBuffer[1] << 8) + temBuffer[2];
//      Serial.println(sieuAm_Value);
//      return true;
//    }
//  }
//  return false;
//}
