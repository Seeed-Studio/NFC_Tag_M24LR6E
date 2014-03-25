/* power on/off your led with NFC_TAG
 * created by lawliet zou (lawliet.zou@gmail.com)
 * Data: 2014/03/25   version: 1.0
 *
 * Usage: 
 * please follow the steps as following
 * 1. Install the APK file which is under NfcTag_M24LR6E/Resources 
 * in your Android Mobile.
 * 2. Connect your NFC TAG and led to your Arduino board
 * 3. Open the application and move your NFC TAG close to your mobile
 * 4. Enter the "BASIC FORMAT" menu, and click "READ" button
 * 5. Block should be writen as 0x7FF(we use the last byte in EEPROM)
 * 6. write last value as 0xFF, the led will turn bright and write 0x00
 * to turn off the led. Have fun!
 */
 
#include "NfcTag.h"
#include <Wire.h>

NfcTag nfcTag;
int led = 5;
bool flag = false;
bool preFlag = false;
void setup(){
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  nfcTag.init();
}

void loop(){
  flag = nfcTag.readByte(EEPROM_I2C_LENGTH-1) == 0xff?true:false;
  if(flag != preFlag){
    Serial.println("get remote NFC control signal!");
    if(flag == true){
      Serial.println("led will light up!");
      digitalWrite(led,HIGH);
    }else{
      Serial.println("led will turn dark!");
      digitalWrite(led,LOW);
    }
    preFlag = flag;
  }
  delay(5*1000);
}


