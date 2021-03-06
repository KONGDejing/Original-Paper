 #include "sys.h"
 #include "timer.h"
 //output the frequency is 72000000/(50*360)=72000000/18000=72000/18=4000hz
 //that is the sample frequency is 4000hz
 void TIM4_Configuration(void) 
{ 
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
   TIM_OCInitTypeDef TIM_OCInitStructure; 

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
	
   TIM_TimeBaseStructure.TIM_Period = 100; //sample frequency is 2k
  //   TIM_TimeBaseStructure.TIM_Period = 99; //sample frequency is  2k  绝大部分时间都已经浪费，采样时钟达到12M�
   TIM_TimeBaseStructure.TIM_Prescaler = 179; //采样频率4K
  //  TIM_TimeBaseStructure.TIM_Prescaler = 360;
	
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
	
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //TIM_OutputState_Disable; ////
    TIM_OCInitStructure.TIM_Pulse = 50;                           //设置待装入捕获比较寄存器的脉冲值    
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);  
    
	TIM_Cmd(TIM4, ENABLE);  
    TIM_InternalClockConfig(TIM4);                                //用网络时间预分频
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);             //预装载使能
	TIM_UpdateDisableConfig(TIM4, DISABLE);                       // What this code use for ?  Nothing use.
}  
