#include "BSP.h"
//定义外部结构体变量，该结构体变量为发送结构体，名称：chassis_one_motor_txm
CanTxMsg chassis_one_motor_txm;
/*****************************************
//Author     :JasonLin
//Version	   :V2.0			 Ownership-Reserved
//Date       :2015/3/15
//Description:MCIO Board support package  
*****************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组2 两位抢占（0-3）  两位响应（0-3）=

	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  
	///////////////////////////////////////CAN			0 1
	
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 		  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure);

  //*****************************************************

  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 		 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //******************************************************
 
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 		 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure);

  //*******************************************************
 
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; 		 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	//*******************************************************

  NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn; 	
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //*******************************************************

  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; 	
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	

 
 /*优先级分组：优先级分组是为了给抢占式优先级和响应优先级在中断优先级寄存器的高四位分配各自所占的位数
               在同一个程序中优先级分组只能设定一次 */

 /*抢占优先级: 当一个中断正在执行而另一个具有更高抢占优先级的中断到来时，抢占优先级高的就会抢占CPU处理权
 			         此时两个中断就属于嵌套中断关系，具有相同抢占优先级的中断没有嵌套关系*/

 /*响应优先级：即副优先级，当两个抢占优先级相同的中断同时到来，具有响应优先级高的中断优先获得CPU的处理权
               如果中断不是同时到来，则后来的要等待正在执行的中断处理完才能获得响应*/

}



//CAN总线定义
//************************************************************



/*
 * 函数名：Can_chassis_one_motor_gpio_conf
 * 描述  ：CAN的GPIO 配置,PB8上拉输入，PB9推挽输出
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void Can_chassis_one_motor_gpio_conf(void)
{
 	GPIO_InitTypeDef Can_chassis_one_motor_gpio;
   	
  	/*外设时钟设置*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

  	/*IO设置*/
	  GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
	/* Configure CAN pin: RX */									               // PB8
    Can_chassis_one_motor_gpio.GPIO_Pin = GPIO_Pin_8;
    Can_chassis_one_motor_gpio.GPIO_Mode = GPIO_Mode_IPU;	             // 上拉输入
    Can_chassis_one_motor_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB, &Can_chassis_one_motor_gpio);
    /* Configure CAN pin: TX */									               // PB9
    Can_chassis_one_motor_gpio.GPIO_Pin = GPIO_Pin_9;
    Can_chassis_one_motor_gpio.GPIO_Mode = GPIO_Mode_AF_PP;		         // 复用推挽输出
    Can_chassis_one_motor_gpio.GPIO_Speed = GPIO_Speed_50MHz;    
	  GPIO_Init(GPIOB, &Can_chassis_one_motor_gpio);
	
}

/*
 * 函数名：Can_chassis_one_motor_nvic_conf
 * 描述  ：CAN的NVIC 配置,第1优先级组，0，0优先级
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void Can_chassis_one_motor_nvic_conf(void)
{
   	  NVIC_InitTypeDef Can_chassis_one_motor_nvic;

	 	/*中断设置*/
//	  Can_chassis_one_motor_nvic.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	   //CAN1 RX0中断
//    Can_chassis_one_motor_nvic.NVIC_IRQChannelPreemptionPriority = 0;		   //抢占优先级0
//    Can_chassis_one_motor_nvic.NVIC_IRQChannelSubPriority = 0;			   //子优先级为0
//    Can_chassis_one_motor_nvic.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&Can_chassis_one_motor_nvic);
	
	  Can_chassis_one_motor_nvic.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
      Can_chassis_one_motor_nvic.NVIC_IRQChannelPreemptionPriority = 0;
      Can_chassis_one_motor_nvic.NVIC_IRQChannelSubPriority = 1;
      Can_chassis_one_motor_nvic.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&Can_chassis_one_motor_nvic);
}

/*
 * 函数名：Can_chassis_one_motor_init_conf
 * 描述  ：CAN的模式 配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void Can_chassis_one_motor_init_conf(void)
{
   	  CAN_InitTypeDef        Can_chassis_one_motor_init;
	 	/************************CAN通信参数设置**********************************/
	  /*CAN寄存器初始化*/
	  CAN_DeInit(CAN1);
	  CAN_StructInit(&Can_chassis_one_motor_init);
	  /*CAN单元初始化*/
	  Can_chassis_one_motor_init.CAN_TTCM=DISABLE;			   //MCR-TTCM  关闭时间触发通信模式使能
      Can_chassis_one_motor_init.CAN_ABOM=ENABLE;			   //MCR-ABOM  自动离线管理 
      Can_chassis_one_motor_init.CAN_AWUM=ENABLE;			   //MCR-AWUM  使用自动唤醒模式
      Can_chassis_one_motor_init.CAN_NART=DISABLE;			   //MCR-NART  禁止报文自动重传	  DISABLE-自动重传
      Can_chassis_one_motor_init.CAN_RFLM=DISABLE;			   //MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文  
      Can_chassis_one_motor_init.CAN_TXFP=DISABLE;			   //MCR-TXFP  发送FIFO优先级 DISABLE-优先级取决于报文标示符 
      Can_chassis_one_motor_init.CAN_Mode = CAN_Mode_Normal;  //正常工作模式
      Can_chassis_one_motor_init.CAN_SJW=CAN_SJW_1tq;		   //BTR-SJW 重新同步跳跃宽度 2个时间单元
      Can_chassis_one_motor_init.CAN_BS1=CAN_BS1_5tq;		   //BTR-TS1 时间段1 占用了6个时间单元
      Can_chassis_one_motor_init.CAN_BS2=CAN_BS2_3tq;		   //BTR-TS1 时间段2 占用了3个时间单元
      Can_chassis_one_motor_init.CAN_Prescaler =4;		   ////BTR-BRP 波特率分频器  定义了时间单元的时间长度 36/(1+6+3)/4=0.8Mbps
	  CAN_Init(CAN1, &Can_chassis_one_motor_init);
}

/*
 * 函数名：Can_chassis_one_motor_filter_conf
 * 描述  ：CAN的过滤器 配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void Can_chassis_one_motor_filter_conf(void)
{
    CAN_FilterInitTypeDef  Can_chassis_one_motor_filter;

	/*CAN过滤器初始化*/
	Can_chassis_one_motor_filter.CAN_FilterNumber=0;						//过滤器组0
    Can_chassis_one_motor_filter.CAN_FilterMode=CAN_FilterMode_IdMask;	//工作在标识符屏蔽位模式
	Can_chassis_one_motor_filter.CAN_FilterScale=CAN_FilterScale_32bit;	//过滤器位宽为单个32位。
	/* 使能报文标示符过滤器按照标示符的内容进行比对过滤，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */
    Can_chassis_one_motor_filter.CAN_FilterIdHigh=0x0000; //(((u32)0x12<<21)&0xFFFF0000)>>16;				//要过滤的ID高位 
    Can_chassis_one_motor_filter.CAN_FilterIdLow= 0x0000; //(((u32)0x12<<21)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF; //要过滤的ID低位 
    Can_chassis_one_motor_filter.CAN_FilterMaskIdHigh= 0x0000;			//过滤器高16位每位必须匹配
    Can_chassis_one_motor_filter.CAN_FilterMaskIdLow= 0x0000;			//过滤器低16位每位必须匹配
	Can_chassis_one_motor_filter.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0 ;				//过滤器被关联到FIFO0
	Can_chassis_one_motor_filter.CAN_FilterActivation=ENABLE;			//使能过滤器
	CAN_FilterInit(&Can_chassis_one_motor_filter);
	/*CAN通信中断使能*/
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);
}


/*
 * 函数名：Can_chassis_one_motor_conf
 * 描述  ：完整配置CAN的功能
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void Can_chassis_one_motor_conf(void)
{
  Can_chassis_one_motor_gpio_conf();
//  Can_chassis_one_motor_nvic_conf();
  Can_chassis_one_motor_init_conf();
  Can_chassis_one_motor_filter_conf();   
}


/*
 * 函数名：CAN_SetMsg
 * 描述  ：CAN通信报文内容设置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */	 
void CAN_SetMsg(int k)
{	  
  chassis_one_motor_txm.StdId=0x55;						 
  chassis_one_motor_txm.IDE=CAN_ID_STD ;				//标准模式
  chassis_one_motor_txm.RTR=CAN_RTR_DATA;			//发送的是数据
  chassis_one_motor_txm.DLC=5;							//数据长度为5字节
  chassis_one_motor_txm.Data[0]=k;
  chassis_one_motor_txm.Data[1]=k+1;
  chassis_one_motor_txm.Data[2]=k+2;
  chassis_one_motor_txm.Data[3]=k+3;
  chassis_one_motor_txm.Data[4]=k+4;
 
}
/**************************END OF FILE************************************/
//************************************************************




















///////////////////定时器功能初始化

void TIM1_Configuration(void)//TIM1四通道分别输出PWM1/PWM2/PWM3/PWM4,对应引脚为PA8/PA9/PA10/PA11
{
  GPIO_InitTypeDef GPIO_InitStructure; 
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;    
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //复用满负载输出为3.3V      
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = PWMPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	
	TIM1->CCR1 = 0; 
	TIM1->CCR2 = 0;  
	TIM1->CCR3 = 0;  
	TIM1->CCR4 = 0; 

	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
}
////////////////////////////

void TIM8_Configuration(void)//TIM8四通道分别输出PWM1/PWM2/PWM3/PWM4,对应引脚为PC6/PC7/PC8/PC9
{
	GPIO_InitTypeDef GPIO_InitStructure; 
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;    
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
	   
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = PWMPeriod;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);
	
	TIM8->CCR1 = 0;    
	TIM8->CCR2 = 0; 
	TIM8->CCR3 = 0; 
	TIM8->CCR4 = 0; 

	TIM_Cmd(TIM8, ENABLE);
	TIM_CtrlPWMOutputs(TIM8, ENABLE);	

}

/////////////////////////////

void TIM2_Configuration(void)//编码器接口设置（TIM2）/PA15-A相  PB3-B相
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;

	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //关闭JTAG接口
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //关闭JTAG接口 开启SWD

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);       //TIM2引脚重定向 
	                                                      				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;			   //PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   
	GPIO_Init(GPIOA, &GPIO_InitStructure);				  
	GPIO_WriteBit(GPIOA, GPIO_Pin_15,Bit_SET);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			   //PB3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   
	GPIO_Init(GPIOB, &GPIO_InitStructure);				   
	GPIO_WriteBit(GPIOB, GPIO_Pin_3,Bit_SET);
	
  TIM_TimeBaseStructure.TIM_Period = ECDPeriod; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	//设置定时器2为编码器模式  IT1 IT2为上升沿计数
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;  //输入滤波器
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);  //清除所有标志位
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //允许中断更新
  TIM2->CNT = 0;
	TIM_Cmd(TIM2, ENABLE);
}

///////////////////////////

void TIM3_Configuration(void)//编码器接口设置（TIM3）/PA6-A相  PA7-B相
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIOA外设时钟
	                                                       				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //设置为上拉输入模式 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //IO口的速率为50M 
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   //IO口配置函数
	GPIO_WriteBit(GPIOA, GPIO_Pin_6,Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_7,Bit_SET); 

  TIM_TimeBaseStructure.TIM_Period = ECDPeriod; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;     //设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	//设置定时器3为编码器模式  IT1 IT2为上升沿计数
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;      //输入滤波器
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);      //清除所有标志位
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //允许中断更新
  TIM3->CNT = 0;
	TIM_Cmd(TIM3, ENABLE);
}

///////////////////////////

void TIM4_Configuration(void)//编码器接口设置（TIM4）/PB6-A相  PB7-B相
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIOB外设时钟
	                                                       				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //设置为上拉输入模式 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //IO口的速率为50M 
	GPIO_Init(GPIOB, &GPIO_InitStructure);				   //IO口配置函数
	GPIO_WriteBit(GPIOB, GPIO_Pin_6,Bit_SET);
	GPIO_WriteBit(GPIOB, GPIO_Pin_7,Bit_SET); 

  TIM_TimeBaseStructure.TIM_Period = ECDPeriod; 
	TIM_TimeBaseStructure.TIM_Prescaler = 0; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
	
	//设置定时器3为编码器模式  IT1 IT2为上升沿计数
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;      //输入滤波器
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);      //清除所有标志位
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //允许中断更新
  TIM4->CNT = 0;
	TIM_Cmd(TIM4, ENABLE);
}

///////////////////////////

void TIM5_Configuration(void)//编码器接口设置（TIM5）/PA0-A相  PA1-B相
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); 
	                                                       				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
	GPIO_Init(GPIOA, &GPIO_InitStructure);				 
	GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_1,Bit_SET); 

  TIM_TimeBaseStructure.TIM_Period = ECDPeriod;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 
	
	//设置定时器3为编码器模式  IT1 IT2为上升沿计数
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;  
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM5, TIM_FLAG_Update); 
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
  TIM5->CNT = 0;
	TIM_Cmd(TIM5, ENABLE);
}

/////////////////////

void TIM6_Configuration(void)//周期循环事件定时初始化
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = TIMPeriod-1;
  TIM_TimeBaseStructure.TIM_Prescaler =72-1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;       
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
  TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
   
  TIM_UpdateRequestConfig(TIM6,TIM_UpdateSource_Regular);
  TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
  TIM_Cmd(TIM6,ENABLE);

}
////////////////////

void TIM7_Configuration(void)//周期循环事件定时初始化
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = TIMPeriod-1;
  TIM_TimeBaseStructure.TIM_Prescaler =72-1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;       
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
  TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);
   
  TIM_UpdateRequestConfig(TIM7,TIM_UpdateSource_Regular);
  TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
  TIM_Cmd(TIM7,ENABLE);

}

//////////////////////////

void TIM_Configuration(void)//TIM初始化
{
  TIM1_Configuration();
	TIM8_Configuration();
	TIM2_Configuration();
	TIM3_Configuration();
	TIM4_Configuration();
	TIM5_Configuration();
	TIM6_Configuration();
	TIM7_Configuration();
	
}

///////////////////////电机速度写入接口
  
void MotorSpeedSetOne(s32 MotorSpeed)//电机1转速/转向设置（TIM1）
{		
	s32 PwmOne_Set,PwmOne_Mode;

	if(MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;//上限 CCR的值必须小于或等于ARR的值
	if(MotorSpeed <-(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);//下限 

	if(MotorSpeed<0) { PwmOne_Set = -MotorSpeed; PwmOne_Mode = MotorOneBack;}
	else { PwmOne_Set = MotorSpeed; PwmOne_Mode = MotorOneForward;}
	
	if(PwmOne_Mode) {TIM8->CCR1 = MotorSpdZero; TIM8->CCR2 = PwmOne_Set;} //MotorOneForward
	else { TIM8->CCR1 = PwmOne_Set; TIM8->CCR2 = MotorSpdZero;} //MotorOneBack	
}

////////////////////////////////
 
void MotorSpeedSetTwo(s32 MotorSpeed)//电机2转速/转向设置（TIM1）
{
  s32 PwmTwo_Set,PwmTwo_Mode;

  if(MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;//上限 CCR的值必须小于或等于ARR的值
  if(MotorSpeed <-(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);//下限 

  if(MotorSpeed<0) { PwmTwo_Set = -MotorSpeed; PwmTwo_Mode = MotorTwoBack;}
  else { PwmTwo_Set = MotorSpeed; PwmTwo_Mode = MotorTwoForward;}

  if(PwmTwo_Mode) {TIM8->CCR3 = MotorSpdZero; TIM8->CCR4 = PwmTwo_Set;} //MotorTwoForward
  else { TIM8->CCR3 = PwmTwo_Set; TIM8->CCR4 = MotorSpdZero;}	//MotorTwoBack
}

////////////////////////////////

void MotorSpeedSetThr(s32 MotorSpeed)//电机3转速/转向设置(TIM8)
{		
	s32 PwmOne_Set,PwmOne_Mode;

	if(MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;//上限 CCR的值必须小于或等于ARR的值
	if(MotorSpeed <-(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);//下限 

	if(MotorSpeed<0) { PwmOne_Set = -MotorSpeed; PwmOne_Mode = MotorOneBack;}
	else { PwmOne_Set = MotorSpeed; PwmOne_Mode = MotorOneForward;}

	if(PwmOne_Mode) {TIM1->CCR1 = MotorSpdZero; TIM1->CCR2 = PwmOne_Set;} //MotorOneForward
	else { TIM1->CCR1 = PwmOne_Set; TIM1->CCR2 = MotorSpdZero;} //MotorOneBack	
}

////////////////////////////////

void MotorSpeedSetFou(s32 MotorSpeed)//电机4转速/转向设置(TIM8)
{
  s32 PwmTwo_Set,PwmTwo_Mode;

  if(MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;//上限 CCR的值必须小于或等于ARR的值
  if(MotorSpeed <-(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);//下限 

  if(MotorSpeed<0) { PwmTwo_Set = -MotorSpeed; PwmTwo_Mode = MotorTwoBack;}
  else { PwmTwo_Set = MotorSpeed; PwmTwo_Mode = MotorTwoForward;}

  if(PwmTwo_Mode) {TIM1->CCR3 = MotorSpdZero; TIM1->CCR4 = PwmTwo_Set;} //MotorTwoForward
  else { TIM1->CCR3 = PwmTwo_Set; TIM1->CCR4 = MotorSpdZero;}	//MotorTwoBack
}


///////////LED 初始化

void Led_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13;				
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
  GPIO_Init(GPIOB, &GPIO_InitStructure);				
  GPIO_ResetBits(GPIOB,GPIO_Pin_15);					
  GPIO_ResetBits(GPIOB,GPIO_Pin_14);
  GPIO_ResetBits(GPIOB,GPIO_Pin_13);
}

//////SYSTICK 初始化

void Systick_Configuration(void)
{
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8	9M
}

//////延时写入接口

void SysDelay_ms(u16 nms)//72M条件下,nms<=1864(2^24/9000)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*Sys_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL=0x01;           //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
}

void SysDelay_us(u32 nus)//72M条件下,nus<=2^24
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*Sys_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01;       //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}


///////Board Communication Package

unsigned char sbus_rx_buffer[18];
RC_Ctl_t RC_Ctl;

void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/* config USART1 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3  | RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
	/* USART3 mode config */
	USART_InitStructure.USART_BaudRate = 100000;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_Even ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx ;
	USART_Init(USART3, &USART_InitStructure); 
	USART_Cmd(USART3, ENABLE); 
}

void DMA_Config(void)
{
   DMA_InitTypeDef DMA_InitStructure;

	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//开启DMA时钟

 	/*设置DMA源：内存地址&串口数据寄存器地址*/
    DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)&(USART3->DR);	   

	/*内存地址(要传输的变量的指针)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sbus_rx_buffer;
	
	/*方向：从外设到内存*/		
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC ;	
	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
    DMA_InitStructure.DMA_BufferSize = 18;
	
	/*外设地址不增*/	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	
	/*内存地址自增*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	
	/*外设数据单位*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/*内存数据单位 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	
	/*DMA模式：循环*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular ;	 
	
	/*优先级：非常高*/	
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
	
	/*禁止内存到内存的传输	*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	/*配置DMA1的3通道*/		   
    DMA_Init(DMA1_Channel3, &DMA_InitStructure); 	   
	
	DMA_Cmd (DMA1_Channel3,ENABLE);					//使能DMA
	DMA_ITConfig(DMA1_Channel3,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断

}



//////Board Support Package

void BSP_Configuration(void)
{
    NVIC_Configuration();
    TIM_Configuration();
    Led_Configuration();
	Systick_Configuration();
	USART3_Config();
	DMA_Config();
	USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
	Can_chassis_one_motor_conf();

}







///////////编码器读取

EncoderType GetEncoder;

void Get_Encoder_ONE(void)
{
  s32 CNT2_temp,CNT2_last;
  
  GetEncoder.cnt2 = TIM2 -> CNT;
  CNT2_last = GetEncoder.CNT2;
  CNT2_temp = GetEncoder.rcnt2 * prd + GetEncoder.cnt2;  
  GetEncoder.V2 = CNT2_temp - CNT2_last;		
  
  while ((s32)(GetEncoder.V2)>Vbreak)				 
  {							      
   GetEncoder.rcnt2--;					      
   CNT2_temp = GetEncoder.rcnt2 * prd + GetEncoder.cnt2;
   GetEncoder.V2 = CNT2_temp - CNT2_last;		 
  }							     
  while ((s32)(GetEncoder.V2)<-Vbreak)			   
  {							      
   GetEncoder.rcnt2++;					      
   CNT2_temp = GetEncoder.rcnt2 * prd + GetEncoder.cnt2;
   GetEncoder.V2 = CNT2_temp - CNT2_last;		 
  }
  GetEncoder.CNT2 = CNT2_temp;						 
  
}

///////////////////

void Get_Encoder_TWO(void)
{
  s32 CNT3_temp,CNT3_last;
 
  GetEncoder.cnt3 = TIM3 -> CNT;
  CNT3_last = GetEncoder.CNT3;
  CNT3_temp = GetEncoder.rcnt3 * prd + GetEncoder.cnt3; 
  GetEncoder.V3 = CNT3_temp - CNT3_last;		
  
  while ((s32)(GetEncoder.V3)>Vbreak)				 
  {							      
   GetEncoder.rcnt3--;					      
   CNT3_temp = GetEncoder.rcnt3 * prd + GetEncoder.cnt3;
   GetEncoder.V3 = CNT3_temp - CNT3_last;		 
  }							     
  while ((s32)(GetEncoder.V3)<-Vbreak)			   
  {							      
   GetEncoder.rcnt3++;					      
   CNT3_temp = GetEncoder.rcnt3 * prd + GetEncoder.cnt3;
   GetEncoder.V3 = CNT3_temp - CNT3_last;		 
  }
  GetEncoder.CNT3 = CNT3_temp;						 
  
}

///////////////////

void Get_Encoder_THR(void)
{
  s32 CNT4_temp,CNT4_last;
  
  GetEncoder.cnt4 = TIM4 -> CNT;
  CNT4_last = GetEncoder.CNT4;
  CNT4_temp = GetEncoder.rcnt4 * prd + GetEncoder.cnt4;  
  GetEncoder.V4 = CNT4_temp - CNT4_last;		 
  
  while ((s32)(GetEncoder.V4)>Vbreak)				 
  {							      
   GetEncoder.rcnt4--;					     
   CNT4_temp = GetEncoder.rcnt4 * prd + GetEncoder.cnt4;
   GetEncoder.V4 = CNT4_temp - CNT4_last;		 
  }							      
  while ((s32)(GetEncoder.V4)<-Vbreak)			   
  {							    
   GetEncoder.rcnt4++;					      
   CNT4_temp = GetEncoder.rcnt4 * prd + GetEncoder.cnt4;
   GetEncoder.V4 = CNT4_temp - CNT4_last;		  
  }
  GetEncoder.CNT4 = CNT4_temp;						
  
}

///////////////////

void Get_Encoder_FOU(void)
{
  s32 CNT5_temp,CNT5_last;
  
  GetEncoder.cnt5 = TIM5 -> CNT;
  CNT5_last = GetEncoder.CNT5;
  CNT5_temp = GetEncoder.rcnt5 * prd + GetEncoder.cnt5;  
  GetEncoder.V5 = CNT5_temp - CNT5_last;		  
  
  while ((s32)(GetEncoder.V5)>Vbreak)				  
  {							      
   GetEncoder.rcnt5--;					      
   CNT5_temp = GetEncoder.rcnt5 * prd + GetEncoder.cnt5;
   GetEncoder.V5 = CNT5_temp - CNT5_last;		 
  }							      
  while ((s32)(GetEncoder.V5)<-Vbreak)			    
  {							     
   GetEncoder.rcnt5++;					      
   CNT5_temp = GetEncoder.rcnt5 * prd + GetEncoder.cnt5;
   GetEncoder.V5 = CNT5_temp - CNT5_last;		 
  }
  GetEncoder.CNT5 = CNT5_temp;					
  
}

////Board Function Package

void BFP_Configuration(void)
{
	Get_Encoder_ONE();
  Get_Encoder_TWO();
  Get_Encoder_THR();
  Get_Encoder_FOU();
}










