
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
CanTxMsg tx_message;
extern char mode;

int fuhao=0;
int vlaue=0;
int shubiao_time=0;
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

            tx_message.StdId = 0x200;
            tx_message.IDE = CAN_Id_Standard;
		    tx_message.RTR = CAN_RTR_Data;
		    tx_message.DLC = 0x08;




if(RC_Ctl.rc.s2==1)
{

if(RC_Ctl.mouse.y<0)
{
fuhao=0;
vlaue=-(RC_Ctl.mouse.y);
}
else
if(RC_Ctl.mouse.y>0)
{
fuhao=1;
vlaue=(RC_Ctl.mouse.y);
}
else
if(RC_Ctl.mouse.y==0)
{
vlaue=0;
}
		    tx_message.Data[0] = (unsigned char)(vlaue);
		    tx_message.Data[1] = (unsigned char) (fuhao);
		    tx_message.Data[2] = (unsigned char)(RC_Ctl.mouse.press_l);
		    tx_message.Data[3] = (unsigned char)(RC_Ctl.mouse.press_r);

			tx_message.Data[4] = 0;
		    tx_message.Data[5] = 0;
		    tx_message.Data[6] = 0;
		    tx_message.Data[7] = 0;
  
            CAN_Transmit(CAN1,&tx_message);

}

else
if(RC_Ctl.rc.s2==2||RC_Ctl.rc.s2==3)
{
		    tx_message.Data[0] = 0;
		    tx_message.Data[1] = 0;
		    tx_message.Data[2] = 0;
		    tx_message.Data[3] = 0;

			tx_message.Data[4] = (unsigned char)(RC_Ctl.rc.ch1>>8);
		    tx_message.Data[5] = (unsigned char) (RC_Ctl.rc.ch1&0xFF);
		    tx_message.Data[6] = (unsigned char)(RC_Ctl.rc.s1);
		    tx_message.Data[7] = (unsigned char)(RC_Ctl.rc.s2);
  
            CAN_Transmit(CAN1,&tx_message);



}
		   
	PidSpeedTypeOne.ctrOut = 0;PidSpeedTypeTwo.ctrOut = 0;
	PidSpeedTypeThr.ctrOut = 0;PidSpeedTypeFou.ctrOut = 0;
    PidSpeedControlOne(MotorControl.MotorSpeedOne);
    PidSpeedControlTwo(MotorControl.MotorSpeedTwo);
    PidSpeedControlThr(MotorControl.MotorSpeedThr);
    PidSpeedControlFou(MotorControl.MotorSpeedFou);
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
            mode=1;
		    DMA_ClearFlag(DMA1_FLAG_TC3); 
		    DMA_ClearITPendingBit(DMA1_IT_TC3);
            RC_Ctl.rc.ch0 = (sbus_rx_buffer[0]| (sbus_rx_buffer[1] << 8)) & 0x07ff;           //!< Channel 0 
            RC_Ctl.rc.ch1 = ((sbus_rx_buffer[1] >> 3) | (sbus_rx_buffer[2] << 5)) & 0x07ff;   //!< Channel 1 
            RC_Ctl.rc.ch2 = ((sbus_rx_buffer[2] >> 6) | (sbus_rx_buffer[3] << 2) | (sbus_rx_buffer[4] << 10)) & 0x07ff;            //!< Channel 2 	 
            RC_Ctl.rc.ch3 = ((sbus_rx_buffer[4] >> 1) | (sbus_rx_buffer[5] << 7)) & 0x07ff;   //!< Channel 3 
            RC_Ctl.rc.s1  = ((sbus_rx_buffer[5] >> 4)& 0x000C) >> 2;                          //!< Switch left 
            RC_Ctl.rc.s2  = ((sbus_rx_buffer[5] >> 4)& 0x0003);                               //!< Switch right 
            RC_Ctl.mouse.x = sbus_rx_buffer[6] | (sbus_rx_buffer[7] << 8);                    //!< Mouse X axis 
            RC_Ctl.mouse.y = sbus_rx_buffer[8] | (sbus_rx_buffer[9] << 8);                    //!< Mouse Y axis 
            RC_Ctl.mouse.z = sbus_rx_buffer[10] | (sbus_rx_buffer[11] << 8);                  //!< Mouse Z axis 
            RC_Ctl.mouse.press_l = sbus_rx_buffer[12];                                        //!< Mouse Left Is Press ? 
            RC_Ctl.mouse.press_r = sbus_rx_buffer[13];                                        //!< Mouse Right Is Press ?  
    		RC_Ctl.key.v = sbus_rx_buffer[14] | (sbus_rx_buffer[15] << 8);                    //!< KeyBoard value 
	 }		
	 else
		    mode=0;
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
