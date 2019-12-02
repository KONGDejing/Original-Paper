#include "micro_key.h"
#include "serial_input.h"
#include "morse.h"
//#include "Keyboard.h"


BlinkLED Blinkled;


void setup() {

  serial_initial();
  Blinkled.pinSetup();//初始化模块引脚
  
  morse_initial();//摩斯码初始化


}
void loop() {

  //serial_read();
  morse_ledblink();
  detect_key1();
  detect_key2();    

}
