
#include "string.h" 
#include "stdio.h"
#include "Arduino.h"
#include <EEPROM.h>
#include "avr/boot.h"

byte DeviceNum;
const char readSerialbuf[30];
const char Flagbuffer[30];
char Flaghackbuf[30];
char inputString[30];         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

bool Crack_success_Flag = false;

void serial_initial(){
   Serial.begin(9600);
   
 //  EEPROM.write(510,11);
//   DeviceNum = EEPROM.read(510);
   memset(Flagbuffer,0x00,sizeof(Flagbuffer));
   sprintf(Flagbuffer,"W3LC0M4 T0 M0S8C%2d",(boot_signature_byte_get(16)+boot_signature_byte_get(23))%100);
   memcpy(Flaghackbuf,&Flagbuffer[11],7);
   if(EEPROM.read(503) == 53)//判断破解是否成功
   {
       Crack_success_Flag = true;
   }
   else
   {
       Crack_success_Flag = false;
   }
}

  
static int readserialNum = 0;
void serial_read(){

    if(Crack_success_Flag == false){
        while(Serial.available()) {
          // get the new byte:
          char inChar = (char)Serial.read();
          // add it to the inputString:
          inputString[readserialNum] = inChar;
          readserialNum++;
          if(readserialNum > 20){
            readserialNum = 0;
            memset(inputString, 0x00, sizeof(inputString));
            stringComplete = false;
            Serial.flush();//清空串口缓存            
          }
      
          if (inChar == '\n') {
            readserialNum = 0;
            stringComplete = true;
            Serial.flush();//清空串口缓存
          }
        }  
        
        if (stringComplete) {
          Serial.print("input:");//不换行
          Serial.println(inputString);//换行
          //Serial.print("psswo:");
          //Serial.println(Flaghackbuf);
          if(strncmp(inputString, Flaghackbuf, 7) != 0){
             Serial.println("\n  TRY AGAIN ");
          }
          else
          {
            Serial.println("      CRACK SUCESS    ");
            Serial.println("TRY TO PRESS LED BUTTON");
            Crack_success_Flag = true;
            EEPROM.write(503,53);
          }   
        
          memset(inputString, 0x00, sizeof(inputString));
          stringComplete = false;
          Serial.flush();//清空串口缓存
      }

    }
}


//void serialEvent() {
//
//  while(Serial.available()) {
//    // get the new byte:
//    char inChar = (char)Serial.read();
//    // add it to the inputString:
//    inputString[readserialNum] = inChar;
//    readserialNum++;
//    if(readserialNum > 18){
//      readserialNum = 0;
//      stringComplete = true;
//    }
//
//    if (inChar == '\n') {
//      stringComplete = true;
//    }
//  }
//}
