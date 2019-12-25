
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

extern char mode;

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
	if(RC_Ctl.rc.s1==3)
	{
    PidSpeedControlTwo(0);		  //拨弹	
	}
	else 
	if(RC_Ctl.rc.s1==1||RC_Ctl.rc.s1==2)
	{
    PidSpeedControlTwo(20);		  //拨弹		
	}

	if(RC_Ctl.rc.s2==3)
	{
    TIM1->CCR1=1000;	
	}
	else 
	if(RC_Ctl.rc.s2==1||RC_Ctl.rc.s2==2)
	{
    TIM1->CCR1=1600;		
	}



// 	PidSpeedTypeThr.ctrOut = 0;PidSpeedTypeFou.ctrOut = 0;
//右轮
// TIM8->CCR1=3000;	
// TIM8->CCR2=0;	
// 	TIM8->CCR3=3000;	
// TIM8->CCR4=0;
//MotorControl.MotorSpeedOne
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

//             temp_yaw = (uint16_t)(rx_message.Data[0]<<8)|(uint16_t)(rx_message.Data[1]);
//            temp_pitch = (uint16_t)(rx_message.Data[2]<<8)|(uint16_t)(rx_message.Data[3]);
//            shooting_flag = (uint8_t)rx_message.Data[4];   
//			      mode_flag = (uint8_t)rx_message.Data[6];//S2 开关
//table[0]=	RxMessage.Data[0];
//table[1]=	RxMessage.Data[1];	
//table[2]=	RxMessage.Data[2];
//table[3]=	RxMessage.Data[3];
//table[4]=	RxMessage.Data[4];	
  /* 比较ID和数据是否为0x1314及DCBA */ 
  if((RxMessage.StdId==0x200) && (RxMessage.IDE==CAN_ID_STD ))
     //&& (RxMessage.DLC==2) && ((RxMessage.Data[1]|RxMessage.Data[0]<<8)==0xDCBA))
  {
  RC_Ctl.rc.ch1=(uint16_t)(RxMessage.Data[0]<<8)|(uint16_t)(RxMessage.Data[1]);
  RC_Ctl.rc.s1=RxMessage.Data[2];
  RC_Ctl.rc.s2=RxMessage.Data[3];
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
