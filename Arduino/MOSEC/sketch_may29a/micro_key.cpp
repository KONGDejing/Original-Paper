#include <FlexiTimer2.h>
#include "HID-Project.h"
#include "Arduino.h"
#include "micro_key.h"
#include "pins_arduino.h"
#include "serial_input.h"



#define BlinkLED1 A3
#define BlinkLED2 A4
#define BlinkLED3 A5
#define BlinkLED4 A1

#define BlinkLED5 A0
#define BlinkLED6 A2
#define BlinkLED7 7

#define pinButton2 13  //PC7
//#define pinButton3 31  //PE2  31
 
int time = 0;  //ms
int pinButton1_num = 0;
int pinButton2_num = 0;

char blinknum[7]={BlinkLED1,BlinkLED2,BlinkLED3,BlinkLED4,BlinkLED5,BlinkLED6,BlinkLED7};

void BlinkLED::pinSetup(){

  pinMode(BlinkLED1, OUTPUT);
  pinMode(BlinkLED2, OUTPUT);
  pinMode(BlinkLED3, OUTPUT);
  pinMode(BlinkLED4, OUTPUT);
  pinMode(BlinkLED5, OUTPUT);
  pinMode(BlinkLED6, OUTPUT);
  pinMode(BlinkLED7, OUTPUT);
  
  pinMode(pinButton2, INPUT);
  //  pinMode(pinButton3, INPUT);  
    DDRE &= ~(1 << 2); // input  //PE2  31引脚 也叫HWB引脚 设置PE2输入模式
    //DDRE |= (1<<2);//output  
    
//     Keyboard.begin();
};

//======定时器led中断回调函数=======//
void Blink_led1() 
{
   static boolean  lighting = true; 
   digitalWrite(BlinkLED1, lighting);
   digitalWrite(BlinkLED2, lighting);
   digitalWrite(BlinkLED3, lighting);
   digitalWrite(BlinkLED4, lighting);
   digitalWrite(BlinkLED5, lighting);
   digitalWrite(BlinkLED6, lighting);
   digitalWrite(BlinkLED7, lighting);
   lighting = !lighting;
}

void Blink_led2() 
{
   static boolean  lighting = true; 
   digitalWrite(BlinkLED1, lighting);
   digitalWrite(BlinkLED2, lighting);
   digitalWrite(BlinkLED3, lighting);
   digitalWrite(BlinkLED4, lighting);
   digitalWrite(BlinkLED5, lighting);
   digitalWrite(BlinkLED6, lighting);
   lighting = !lighting;
   digitalWrite(BlinkLED7, lighting);
}

void Blink_led3() 
{
   static boolean  lighting = true; 
   digitalWrite(BlinkLED1, lighting);
   digitalWrite(BlinkLED2, lighting);
   digitalWrite(BlinkLED3, lighting);
   digitalWrite(BlinkLED4, lighting);
   digitalWrite(BlinkLED7, lighting);
   lighting = !lighting;
   digitalWrite(BlinkLED5, lighting);
   digitalWrite(BlinkLED6, lighting);   
}

void Blink_led4()
{
   for(int i = 0; i<7;i++)
   {
      digitalWrite(blinknum[i], true);
   }
}
//======定时器呼吸灯中断回调函数=======//
void Fading_led()
{
  static int fadeValue = 0;
  static boolean direc = true;
  if(direc == true)
  {
    fadeValue++; 
    if(fadeValue >= 255)
    {
       direc = !direc;
       digitalWrite(BlinkLED7, direc);
    }
    
  }
  else
  {
    fadeValue--; 
    if(fadeValue <= 0)
    {
       direc = !direc;
       digitalWrite(BlinkLED7, direc);
    }
  }
  analogWrite(BlinkLED1, fadeValue);
  analogWrite(BlinkLED2, fadeValue);
  analogWrite(BlinkLED3, fadeValue);
  analogWrite(BlinkLED4, fadeValue);
  analogWrite(BlinkLED5, fadeValue);
  analogWrite(BlinkLED6, fadeValue);

}
 

void timer_led_blink(char mode) 
{
  FlexiTimer2::stop(); 
  switch(mode)
  {
    case 1: {
      time = 500; 
      FlexiTimer2::set(time, 1.0/1000, Blink_led1);
      FlexiTimer2::start(); 
      break;//500ms闪烁     
    }
    case 2:{
      time = 50; 
      FlexiTimer2::set(time, 1.0/1000, Blink_led1);
      FlexiTimer2::start();  
      break; //50ms闪烁    
    }
//    case 3:{
//      time = 30;
//      FlexiTimer2::set(time, 1.0/1000, Fading_led);
//      FlexiTimer2::start();        
//      break;
//    }
    case 3:{
      time = 100;
      FlexiTimer2::set(time, 1.0/1000, Blink_led2);
      FlexiTimer2::start();        
      break;
    } 
    case 4:{
      time = 100;
      FlexiTimer2::set(time, 1.0/1000, Blink_led3);
      FlexiTimer2::start();        
      break;
    } 
    case 5:{
      Blink_led4();   
      break;    
    }
    default: break;
  }
  
}




//=================key1=================//
void detect_key1()//for LED mode change
{
    //if(Crack_success_Flag == true)//破解成功后才能进入
    {
        if (!(PINE & (1 << 2))){  //PE2  31引脚 也叫HWB引脚 读取是否是低电平 //
           pinButton1_num +=1;
           if(pinButton1_num == 6)
           {
             pinButton1_num = 1;
           }
           timer_led_blink(pinButton1_num);
        }
    }
}

//=================key2=================//

static String text1="cls & color 2 & echo The Mobile Security Conference (MOSEC) is organized by Team Pangu and PoC and was first started in 2015. MOSEC 2019 will be held on May 30-31, 2019 at the Shanghai Marriott Hotel City Centre, in Shanghai, China. & ping 127.0.0.1 -t &title Welcome To MOSEC";

//"cls & title Welcome To MOSEC & color 6 & echo MOSEC focuses on cutting-edge research topics the area of mobile security, fosters information exchange among researchers and practitioners,";
//"cls & title Welcome To MOSEC & color b & echo and received high praise from both the attendees and the community.";

void detect_key2()//for hid mode change
{
    //if(Crack_success_Flag == true)
    {
        if (!digitalRead(pinButton2)) 
        {
          pinButton2_num +=1;
          switch(pinButton2_num)
          {  
              case 1://打开记事本
//                Keyboard.press(KEY_LEFT_GUI);//win键
//                delay(50);
//                Keyboard.press('r');//r键
//                delay(50);
//                Keyboard.release(KEY_LEFT_GUI);//释放win按键
//                Keyboard.release('r');//释放r按键
//                delay(500);
//                Keyboard.println("cmd");//打开记事本是win+r+notepad
//                delay(1000);
                //Keyboard.end();
//              
//                BootKeyboard.println(text1);
//                delay(1000);

                
                //BootKeyboard.println("notepad /a d:\kdj.txt");
//                BootKeyboard.press(KEY_LEFT_ALT);//
//                delay(50);
//                BootKeyboard.press(KEY_SPACE);
//                delay(50);
//                BootKeyboard.press(KEY_X);
//                delay(50);
//                BootKeyboard.release(KEY_LEFT_ALT);
//                BootKeyboard.release(KEY_SPACE);
//                BootKeyboard.release(KEY_X);
//                BootKeyboard.releaseAll();
//                delay(1000);
//                BootKeyboard.println("\n\n\n\n\n\n\n\n");
//                BootKeyboard.println(" The  Mobile  Security  Conference  (MOSEC)  Is  Organized  By  TeamPangu  And  PoC  ");
//                delay(500);
//                BootKeyboard.println("\n  And  Was  First  Started  In  2015.  MOSEC Focuses On Cutting-edge  \n");
//                delay(500);                
//                BootKeyboard.println("\n Research Topics The Area Of Mobile Security,\n");
//                delay(500);                
//                BootKeyboard.println(" Fosters Information Exchange Among  Researchers And  Practitioners,  ");
//                delay(500);
//                BootKeyboard.println("\n\n And Received High Praise From Both The Attendees And The Community. \n\n");
//                delay(500);
//                BootKeyboard.println(" Welcome    To    MOSEC   Security   Conference     SHANG      HAI");
                
                break;
                
//              case 2: 
//                BootKeyboard.press(KEY_LEFT_GUI);//win键
//                delay(50);
//                BootKeyboard.press('r');//r键
//                delay(50);
//                BootKeyboard.release(KEY_LEFT_GUI);//释放win按键
//                BootKeyboard.release('r');//释放r按键
//                delay(500);
//                BootKeyboard.println("powershell ");//打开记事本是win+r+notepad
//                delay(500);
//                BootKeyboard.println("cd D:\\Arduino\\HackCube-Special-master");//cmd中启动脚本  C:\\Users\\lenovo\\Desktop\\HID-master\\examples\\Keyboard\\KeyboardLed\\run.bat  
//                BootKeyboard.println(".\\Hack.ps1 ");  
//                delay(3000);  
//                break;
              
//              case 3: 
//                BootKeyboard.press(KEY_LEFT_GUI);//win键
//                delay(50);
//                BootKeyboard.press('r');//r键
//                delay(50);
//                BootKeyboard.release(KEY_LEFT_GUI);//释放win按键
//                BootKeyboard.release('r');//释放r按键
//                delay(500);
//                BootKeyboard.println("powershell ");//打开记事本是win+r+notepad
//                delay(500);
//                BootKeyboard.println("start D:\\Arduino\\HackCube-Special-master\\Searchweb.bat");//powershell中启动脚本              
//                delay(3000);
//                break;  
                
             case 2: 
//                Keyboard.press(KEY_LEFT_GUI);//win键
//                delay(50);
//                Keyboard.press('l');//r键
//                delay(50);
//                Keyboard.release(KEY_LEFT_GUI);//释放win按键
//                Keyboard.release('l');//释放r按键
//                delay(500);
                
//                BootKeyboard.println("powershell ");//打开记事本是win+r+notepad
//                delay(500);
//                BootKeyboard.println("start D:\\Arduino\\HackCube-Special-master\\LockWindow.bat");//powershell中启动脚本  
//                delay(3000);            
                break;  
    
             default:pinButton2_num =5; break;
          } 
             
      }
      
    }  
}
