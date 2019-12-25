#ifndef __BSP_H
#define __BSP_H	

#include "stm32f10x.h"
#include "BitBand.h"

#define PWMPeriod      7200			//10k HZ
#define ECDPeriod      20000
#define TIMPeriod	     5000
#define PWMLOSS        500	

#define MotorOneForward  0
#define MotorTwoForward  0
#define MotorOneBack     1
#define MotorTwoBack     1
#define MotorSpdZero     0

#define LED1  PBout(15)	
#define LED2  PBout(14)
#define LED3  PBout(13)	

#define Sys_us  72/8            
#define Sys_ms  Sys_us*1000

#define prd     ECDPeriod
#define Vbreak  ECDPeriod/2

/* ----------------------- RC Channel Definition---------------------------- */ 
#define RC_CH_VALUE_MIN              ((uint16_t)364 ) 
#define RC_CH_VALUE_OFFSET           ((uint16_t)1024) 
#define RC_CH_VALUE_MAX              ((uint16_t)1684) 
 
/* ----------------------- RC Switch Definition----------------------------- */ 
#define RC_SW_UP                     ((uint16_t)1) 
#define RC_SW_MID                    ((uint16_t)3) 
#define RC_SW_DOWN                   ((uint16_t)2) 
 
/* ----------------------- PC Key Definition-------------------------------- */ 
#define KEY_PRESSED_OFFSET_W         ((uint16_t)0x01<<0) 
#define KEY_PRESSED_OFFSET_S         ((uint16_t)0x01<<1) 
#define KEY_PRESSED_OFFSET_A         ((uint16_t)0x01<<2) 
#define KEY_PRESSED_OFFSET_D         ((uint16_t)0x01<<3) 
#define KEY_PRESSED_OFFSET_Q         ((uint16_t)0x01<<4) 
#define KEY_PRESSED_OFFSET_E         ((uint16_t)0x01<<5) 
#define KEY_PRESSED_OFFSET_SHIFT     ((uint16_t)0x01<<6) 
#define KEY_PRESSED_OFFSET_CTRL      ((uint16_t)0x01<<7) 
 
/* ----------------------- Data Struct ------------------------------------- */ 


typedef struct
{
	s16 V2;
	s16 V3;
	s16 V4;
	s16 V5;
	s16 cnt2;
	s16 cnt3;
	s16 cnt4;
	s16 cnt5;
	s16 rcnt2;
	s16 rcnt3;
	s16 rcnt4;
	s16 rcnt5;
	s32 CNT2;
	s32 CNT3;
	s32 CNT4;
	s32 CNT5;
}EncoderType;


typedef struct 
{ 
   struct 
    { 
        uint16_t ch0; 
        uint16_t ch1; 
        uint16_t ch2; 
        uint16_t ch3; 
        uint8_t  s1; 
        uint8_t  s2; 
    }rc; 
 
    struct 
    { 
        int16_t x; 
        int16_t y; 
        int16_t z; 
        uint8_t press_l; 
        uint8_t press_r; 
    }mouse; 
 
    struct 
    { 
        uint16_t v; 
    }key; 
}RC_Ctl_t; 


/*****************************************************************/
extern  RC_Ctl_t RC_Ctl; 	  
void NVIC_Configuration(void);
void TIM1_Configuration(void);
void TIM8_Configuration(void);
void TIM2_Configuration(void);
void TIM3_Configuration(void);
void TIM4_Configuration(void);
void TIM5_Configuration(void);
void TIM6_Configuration(void);
void TIM7_Configuration(void);
void TIM_Configuration(void) ;
void MotorSpeedSetOne(s32 MotorSpeed);
void MotorSpeedSetTwo(s32 MotorSpeed);
void MotorSpeedSetThr(s32 MotorSpeed);
void MotorSpeedSetFou(s32 MotorSpeed);
void Led_Configuration(void);
void BSP_Configuration(void);
void Systick_Configuration(void);
void SysDelay_ms(u16 nms);
void SysDelay_us(u32 nus);
void Get_Encoder_ONE(void);
void Get_Encoder_TWO(void);
void Get_Encoder_THR(void);
void Get_Encoder_FOU(void);
void BFP_Configuration(void);
void USART3_Config(void);
void DMA_Config(void);



#endif















