

#ifndef _MICRO_KEY_H_
#define _MICRO_KEY_H_

extern char blinknum[7];
class BlinkLED{
public:
  // 将模块io设置为对应的输入输出模式
  void pinSetup();

private:
  int pin;

};

void Blink_led1();
void Blink_led2(); 
void Blink_led3(); 
void Fading_led();
void blink300(int time);
void blink300_(int time);
void blink600();
void _blink1500(int time);

void timer_led_blink(char mode);
void detect_key1();
void detect_key2();

#endif
