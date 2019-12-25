
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x_can.h" 
#include "RobotTask.h"
#include "FramWork.h"
#include "BSP.h"

extern RC_Ctl_t RC_Ctl; 
extern EncoderType GetEncoder;
extern MotorControlType MotorControl;
extern PID_AbsoluteType PidSpeedTypeOne,PidSpeedTypeTwo,PidSpeedTypeThr,PidSpeedTypeFou;

extern unsigned char sbus_rx_buffer[18];
CanRxMsg  RxMessage;
extern int table=0;
extern float up_uale=1000.0;
extern char mode;
extern char up_table=0;
int time=0;

char yuntai_value;
char mouse_press_r,mouse_press_l;
char fuhao=0;
char mochalun_mode=0;
int mochalun_time=0;
int yuntai=0,yuntai_last=0;
int yuntai_time=0;

////////////////////////////面向用户的中断

void TIM6_IRQHandler(void)//用户开发接口
{
	LED3=!LED3;
  TIM_ClearITPendingBit(TIM6,TIM_FLAG_Update);
}

///////////////////

void TIM7_IRQHandler(void)//内部底层驱动
{
    BFP_Configuration();
	
	DevelopmentFramwork();

 	PidSpeedTypeOne.ctrOut = 0;PidSpeedTypeTwo.ctrOut = 0;

if(RC_Ctl.rc.s2==0)
{
if(yuntai_last==yuntai)
yuntai=0;
if(fuhao==0)
{
yuntai=+yuntai_value;
yuntai_value=0;
yuntai_time++;
//yuntai_last=yuntai;
}
else
{
yuntai=-yuntai_value;
yuntai_value=0;
yuntai_time++;
//yuntai_last=yuntai;
}
if(yuntai_time>0&&yuntai_time<150)
{
yuntai_last=yuntai;
}
else
if(yuntai_time>250&&yuntai_time<30)
{
yuntai_time=0;

}
 if(yuntai_last==yuntai)
yuntai=0;

MotorControl.MotorSpeedOne-=yuntai*5;
 //      MotorControl.MotorSpeedOne = Vx;

	if(table==1)
	{
	if(mouse_press_l==0)
	{
    TIM8->CCR3=0;		  //拨弹
	TIM8->CCR4=0;	
	}
	else 
	if(mouse_press_l==1)
	{
    TIM8->CCR3=0;		  //拨弹
	TIM8->CCR4=5000;			
	}

 }

if(mouse_press_r==1)
{
mochalun_time++;
if(mochalun_time>400)
mochalun_mode=0;
else
{
mochalun_mode=1;
}

}
if(mouse_press_r==0)
mochalun_time=0;

	if(mochalun_mode==0)
	{
    TIM1->CCR1=1000;
	    TIM8->CCR3=0;		  //拨弹
		up_uale=1000;
		up_table=0;
	TIM8->CCR4=0;
	table=0;	
	}
	else 
	if(mochalun_mode==1)
	{
    if(up_table==0)
		up_uale+=0.7;
//	up_uale+=1;	   if(up_uale==1700)
	if(up_uale>1800.0)
	{
	up_uale=1800.0;
	up_table=1;
	}
    TIM1->CCR1=up_uale;	
	table=1;		
	}

}




else
if(RC_Ctl.rc.s2==2||RC_Ctl.rc.s2==3)
{


	if(RC_Ctl.rc.s2==3)
	{
    TIM1->CCR1=1000;
	    TIM8->CCR3=0;		  //拨弹
		up_uale=1000;
		up_table=0;
	TIM8->CCR4=0;
	table=0;	
	}
	else 
	if(RC_Ctl.rc.s2==2)
	{
    if(up_table==0)
		up_uale+=0.7;
//	up_uale+=1;	   if(up_uale==1700)
	if(up_uale>1800.0)
	{
	up_uale=1800.0;
	up_table=1;
	}
    TIM1->CCR1=up_uale;	
	table=1;		
	}




	if(table==1)
	{
	if(RC_Ctl.rc.s1==3)
	{
    TIM8->CCR3=0;		  //拨弹
	TIM8->CCR4=0;	
	}
	else 
	if(RC_Ctl.rc.s1==2)
	{
    TIM8->CCR3=0;		  //拨弹
	TIM8->CCR4=5000;			
	}
 }






} 




 if(time<200)
 {
 time++;
 TIM8->CCR1=0;	
 TIM8->CCR2=0; 
 }
 if(time==200)
 time=300;
 if(time>200)
	PidSpeedControlOne(MotorControl.MotorSpeedOne);	      //枪管

//  PidSpeedControlThr(MotorControl.MotorSpeedThr);
//  PidSpeedControlFou(MotorControl.MotorSpeedFou);

	LED1=!LED1;
    TIM_ClearITPendingBit(TIM7,TIM_FLAG_Update);
}

///////////////////

void TIM2_IRQHandler(void)
{
  if (TIM2 -> CR1 & 0X0010)		  //小心注意
   {
    GetEncoder.rcnt2 -= 1;
   }
   else GetEncoder.rcnt2 += 1;

   TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
}

/////////////////

void TIM3_IRQHandler(void)
{
  if (TIM3 -> CR1 & 0X0010)		  //小心注意
   {
    GetEncoder.rcnt3 -= 1;
   }
   else GetEncoder.rcnt3 += 1;

   TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
}

//////////////////

void TIM4_IRQHandler(void)
{
  if (TIM4 -> CR1 & 0X0010)		  //小心注意
   {
    GetEncoder.rcnt4 -= 1;
   }
   else GetEncoder.rcnt4 += 1;
   TIM_ClearITPendingBit(TIM4, TIM_IT_Update); 
}

//////////////////

void TIM5_IRQHandler(void)
{
  if (TIM5 -> CR1 & 0X0010)		  //小心注意
   {
    GetEncoder.rcnt5 -= 1;
   }
   else GetEncoder.rcnt5 += 1;
   TIM_ClearITPendingBit(TIM5, TIM_IT_Update); 
}


void DMA1_Channel3_IRQHandler(void)
{	
//判断是否为DMA发送完成中断
   if(DMA_GetFlagStatus(DMA1_FLAG_TC3)==SET) 
   {  
//        mode=1;
//		    DMA_ClearFlag(DMA1_FLAG_TC3); 
//		    DMA_ClearITPendingBit(DMA1_IT_TC3);
//        RC_Ctl.rc.ch0 = (sbus_rx_buffer[0]| (sbus_rx_buffer[1] << 8)) & 0x07ff;           //!< Channel 0 
//        RC_Ctl.rc.ch1 = ((sbus_rx_buffer[1] >> 3) | (sbus_rx_buffer[2] << 5)) & 0x07ff;   //!< Channel 1 
//        RC_Ctl.rc.ch2 = ((sbus_rx_buffer[2] >> 6) | (sbus_rx_buffer[3] << 2) | (sbus_rx_buffer[4] << 10)) & 0x07ff;            //!< Channel 2 	 
//        RC_Ctl.rc.ch3 = ((sbus_rx_buffer[4] >> 1) | (sbus_rx_buffer[5] << 7)) & 0x07ff;   //!< Channel 3 
//        RC_Ctl.rc.s1  = ((sbus_rx_buffer[5] >> 4)& 0x000C) >> 2;                          //!< Switch left 
//        RC_Ctl.rc.s2  = ((sbus_rx_buffer[5] >> 4)& 0x0003);                               //!< Switch right 
//        RC_Ctl.mouse.x = sbus_rx_buffer[6] | (sbus_rx_buffer[7] << 8);                    //!< Mouse X axis 
//        RC_Ctl.mouse.y = sbus_rx_buffer[8] | (sbus_rx_buffer[9] << 8);                    //!< Mouse Y axis 
//        RC_Ctl.mouse.z = sbus_rx_buffer[10] | (sbus_rx_buffer[11] << 8);                  //!< Mouse Z axis 
//        RC_Ctl.mouse.press_l = sbus_rx_buffer[12];                                        //!< Mouse Left Is Press ? 
//        RC_Ctl.mouse.press_r = sbus_rx_buffer[13];                                        //!< Mouse Right Is Press ?  
//        RC_Ctl.key.v = sbus_rx_buffer[14] | (sbus_rx_buffer[15] << 8);                    //!< KeyBoard value 
	}	
//	 else
//		 mode=0;
}




void USB_LP_CAN1_RX0_IRQHandler(void)
{
 // CanRxMsg  RxMessage;
 /*从邮箱中读出报文*/
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);	
  /* 比较ID和数据是否为0x1314及DCBA */ 
  if((RxMessage.StdId==0x200) && (RxMessage.IDE==CAN_ID_STD ))
     //&& (RxMessage.DLC==2) && ((RxMessage.Data[1]|RxMessage.Data[0]<<8)==0xDCBA))
  {
  mode=1;
  yuntai_value=(RxMessage.Data[0]);
  fuhao=RxMessage.Data[1];
  mouse_press_l=RxMessage.Data[2];
  mouse_press_r=RxMessage.Data[3];

  RC_Ctl.rc.ch1=(uint16_t)(RxMessage.Data[4]<<8)|(uint16_t)(RxMessage.Data[5]);
  RC_Ctl.rc.s1=RxMessage.Data[6];
  RC_Ctl.rc.s2=RxMessage.Data[7];
    mode = 1; 					       //接收成功  
  }
  else
  {
    mode = 0; 					   //接收失败
  }
}










////////////////////////系统级中断，慎用！
 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
