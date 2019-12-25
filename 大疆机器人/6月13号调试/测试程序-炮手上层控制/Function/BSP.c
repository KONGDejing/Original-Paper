#include "BSP.h"
/*****************************************
Author     :JasonLin
Version	   :V2.0			 Ownership-Reserved
Date       :2015/3/15
Description:MCIO Board support package  
*****************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ���2 ��λ��ռ��0-3��  ��λ��Ӧ��0-3��=

	
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

	

 
 /*���ȼ����飺���ȼ�������Ϊ�˸���ռʽ���ȼ�����Ӧ���ȼ����ж����ȼ��Ĵ����ĸ���λ���������ռ��λ��
               ��ͬһ�����������ȼ�����ֻ���趨һ�� */

 /*��ռ���ȼ�: ��һ���ж�����ִ�ж���һ�����и�����ռ���ȼ����жϵ���ʱ����ռ���ȼ��ߵľͻ���ռCPU����Ȩ
 			         ��ʱ�����жϾ�����Ƕ���жϹ�ϵ��������ͬ��ռ���ȼ����ж�û��Ƕ�׹�ϵ*/

 /*��Ӧ���ȼ����������ȼ�����������ռ���ȼ���ͬ���ж�ͬʱ������������Ӧ���ȼ��ߵ��ж����Ȼ��CPU�Ĵ���Ȩ
               ����жϲ���ͬʱ�������������Ҫ�ȴ�����ִ�е��жϴ�������ܻ����Ӧ*/

}








//***********************************************************************
static void Can_chassis_one_motor_gpio_conf(void)
{
 	GPIO_InitTypeDef Can_chassis_one_motor_gpio;
   	
  	/*����ʱ������*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

  	/*IO����*/
	  GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
	/* Configure CAN pin: RX */									               // PB8
    Can_chassis_one_motor_gpio.GPIO_Pin = GPIO_Pin_8;
    Can_chassis_one_motor_gpio.GPIO_Mode = GPIO_Mode_IPU;	             // ��������
    Can_chassis_one_motor_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB, &Can_chassis_one_motor_gpio);
    /* Configure CAN pin: TX */									               // PB9
    Can_chassis_one_motor_gpio.GPIO_Pin = GPIO_Pin_9;
    Can_chassis_one_motor_gpio.GPIO_Mode = GPIO_Mode_AF_PP;		         // �����������
    Can_chassis_one_motor_gpio.GPIO_Speed = GPIO_Speed_50MHz;    
	  GPIO_Init(GPIOB, &Can_chassis_one_motor_gpio);
	
}

/*
 * ��������Can_chassis_one_motor_nvic_conf
 * ����  ��CAN��NVIC ����,��1���ȼ��飬0��0���ȼ�
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void Can_chassis_one_motor_nvic_conf(void)
{
   	  NVIC_InitTypeDef Can_chassis_one_motor_nvic;

	 	/*�ж�����*/
	Can_chassis_one_motor_nvic.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	   //CAN1 RX0�ж�
    Can_chassis_one_motor_nvic.NVIC_IRQChannelPreemptionPriority = 0;		   //��ռ���ȼ�0
    Can_chassis_one_motor_nvic.NVIC_IRQChannelSubPriority = 1;			   //�����ȼ�Ϊ0
    Can_chassis_one_motor_nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&Can_chassis_one_motor_nvic);
}

/*
 * ��������Can_chassis_one_motor_init_conf
 * ����  ��CAN��ģʽ ����
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void Can_chassis_one_motor_init_conf(void)
{
   	  CAN_InitTypeDef        Can_chassis_one_motor_init;
	 	/************************CANͨ�Ų�������**********************************/
	  /*CAN�Ĵ�����ʼ��*/
	  CAN_DeInit(CAN1);
	  CAN_StructInit(&Can_chassis_one_motor_init);
	  /*CAN��Ԫ��ʼ��*/
	  Can_chassis_one_motor_init.CAN_TTCM=DISABLE;			   //MCR-TTCM  �ر�ʱ�䴥��ͨ��ģʽʹ��
      Can_chassis_one_motor_init.CAN_ABOM=ENABLE;			   //MCR-ABOM  �Զ����߹��� 
      Can_chassis_one_motor_init.CAN_AWUM=ENABLE;			   //MCR-AWUM  ʹ���Զ�����ģʽ
      Can_chassis_one_motor_init.CAN_NART=DISABLE;			   //MCR-NART  ��ֹ�����Զ��ش�	  DISABLE-�Զ��ش�
      Can_chassis_one_motor_init.CAN_RFLM=DISABLE;			   //MCR-RFLM  ����FIFO ����ģʽ  DISABLE-���ʱ�±��ĻḲ��ԭ�б���  
      Can_chassis_one_motor_init.CAN_TXFP=DISABLE;			   //MCR-TXFP  ����FIFO���ȼ� DISABLE-���ȼ�ȡ���ڱ��ı�ʾ�� 
      Can_chassis_one_motor_init.CAN_Mode = CAN_Mode_Normal;  //��������ģʽ
      Can_chassis_one_motor_init.CAN_SJW=CAN_SJW_1tq;		   //BTR-SJW ����ͬ����Ծ��� 2��ʱ�䵥Ԫ
      Can_chassis_one_motor_init.CAN_BS1=CAN_BS1_5tq;		   //BTR-TS1 ʱ���1 ռ����6��ʱ�䵥Ԫ
      Can_chassis_one_motor_init.CAN_BS2=CAN_BS2_3tq;		   //BTR-TS1 ʱ���2 ռ����3��ʱ�䵥Ԫ
      Can_chassis_one_motor_init.CAN_Prescaler =4;		   ////BTR-BRP �����ʷ�Ƶ��  ������ʱ�䵥Ԫ��ʱ�䳤�� 36/(1+6+3)/4=0.8Mbps
	  CAN_Init(CAN1, &Can_chassis_one_motor_init);
}

/*
 * ��������Can_chassis_one_motor_filter_conf
 * ����  ��CAN�Ĺ����� ����
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void Can_chassis_one_motor_filter_conf(void)
{
    CAN_FilterInitTypeDef  Can_chassis_one_motor_filter;

	/*CAN��������ʼ��*/
	Can_chassis_one_motor_filter.CAN_FilterNumber=0;						//��������0
    Can_chassis_one_motor_filter.CAN_FilterMode=CAN_FilterMode_IdMask;	//�����ڱ�ʶ������λģʽ
	Can_chassis_one_motor_filter.CAN_FilterScale=CAN_FilterScale_32bit;	//������λ��Ϊ����32λ��
	/* ʹ�ܱ��ı�ʾ�����������ձ�ʾ�������ݽ��бȶԹ��ˣ���չID�������µľ����������ǵĻ��������FIFO0�� */
    Can_chassis_one_motor_filter.CAN_FilterIdHigh=0x0000; //(((u32)0x12<<21)&0xFFFF0000)>>16;				//Ҫ���˵�ID��λ 
    Can_chassis_one_motor_filter.CAN_FilterIdLow= 0x0000; //(((u32)0x12<<21)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF; //Ҫ���˵�ID��λ 
    Can_chassis_one_motor_filter.CAN_FilterMaskIdHigh= 0x0000;			//��������16λÿλ����ƥ��
    Can_chassis_one_motor_filter.CAN_FilterMaskIdLow= 0x0000;			//��������16λÿλ����ƥ��
	Can_chassis_one_motor_filter.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0 ;				//��������������FIFO0
	Can_chassis_one_motor_filter.CAN_FilterActivation=ENABLE;			//ʹ�ܹ�����
	CAN_FilterInit(&Can_chassis_one_motor_filter);
	/*CANͨ���ж�ʹ��*/
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);
}


/*
 * ��������Can_chassis_one_motor_conf
 * ����  ����������CAN�Ĺ���
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void Can_chassis_one_motor_conf(void)
{
  Can_chassis_one_motor_gpio_conf();
  Can_chassis_one_motor_nvic_conf();
  Can_chassis_one_motor_init_conf();
  Can_chassis_one_motor_filter_conf();   
}

//***********************************************************************















///////////////////��ʱ�����ܳ�ʼ��

void TIM1_Configuration(void)//TIM1��ͨ���ֱ����PWM1/PWM2/PWM3/PWM4,��Ӧ����ΪPA8/PA9/PA10/PA11
{
  GPIO_InitTypeDef GPIO_InitStructure; 
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;    
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //�������������Ϊ3.3V      
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
	TIM_TimeBaseStructure.TIM_Prescaler = 72;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 20000;
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

void TIM8_Configuration(void)//TIM8��ͨ���ֱ����PWM1/PWM2/PWM3/PWM4,��Ӧ����ΪPC6/PC7/PC8/PC9
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

void TIM2_Configuration(void)//�������ӿ����ã�TIM2��/PA15-A��  PB3-B��
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;

	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //�ر�JTAG�ӿ�
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);  //�ر�JTAG�ӿ� ����SWD

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);       //TIM2�����ض��� 
	                                                      				
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
	
  TIM_TimeBaseStructure.TIM_Period = ECDPeriod; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
	//���ö�ʱ��2Ϊ������ģʽ  IT1 IT2Ϊ�����ؼ���
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;  //�����˲���
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);  //������б�־λ
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //�����жϸ���
  TIM2->CNT = 0;
	TIM_Cmd(TIM2, ENABLE);
}

///////////////////////////

void TIM3_Configuration(void)//�������ӿ����ã�TIM3��/PA6-A��  PA7-B��
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIOA����ʱ��
	                                                       				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //����Ϊ��������ģʽ 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //IO�ڵ�����Ϊ50M 
	GPIO_Init(GPIOA, &GPIO_InitStructure);				   //IO�����ú���
	GPIO_WriteBit(GPIOA, GPIO_Pin_6,Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_7,Bit_SET); 

  TIM_TimeBaseStructure.TIM_Period = ECDPeriod; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;     //����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	//���ö�ʱ��3Ϊ������ģʽ  IT1 IT2Ϊ�����ؼ���
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;      //�����˲���
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);      //������б�־λ
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //�����жϸ���
  TIM3->CNT = 0;
	TIM_Cmd(TIM3, ENABLE);
}

///////////////////////////

void TIM4_Configuration(void)//�������ӿ����ã�TIM4��/PB6-A��  PB7-B��
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��GPIOB����ʱ��
	                                                       				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //����Ϊ��������ģʽ 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   //IO�ڵ�����Ϊ50M 
	GPIO_Init(GPIOB, &GPIO_InitStructure);				   //IO�����ú���
	GPIO_WriteBit(GPIOB, GPIO_Pin_6,Bit_SET);
	GPIO_WriteBit(GPIOB, GPIO_Pin_7,Bit_SET); 

  TIM_TimeBaseStructure.TIM_Period = ECDPeriod; 
	TIM_TimeBaseStructure.TIM_Prescaler = 0; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
	
	//���ö�ʱ��3Ϊ������ģʽ  IT1 IT2Ϊ�����ؼ���
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_BothEdge,TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;      //�����˲���
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);      //������б�־λ
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //�����жϸ���
  TIM4->CNT = 0;
	TIM_Cmd(TIM4, ENABLE);
}

///////////////////////////

void TIM5_Configuration(void)//�������ӿ����ã�TIM5��/PA0-A��  PA1-B��
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
	
	//���ö�ʱ��3Ϊ������ģʽ  IT1 IT2Ϊ�����ؼ���
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

void TIM6_Configuration(void)//����ѭ���¼���ʱ��ʼ��
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

void TIM7_Configuration(void)//����ѭ���¼���ʱ��ʼ��
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

void TIM_Configuration(void)//TIM��ʼ��
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

///////////////////////����ٶ�д��ӿ�
  
void MotorSpeedSetOne(s32 MotorSpeed)//���1ת��/ת�����ã�TIM1��
{		
	s32 PwmOne_Set,PwmOne_Mode;

	if(MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;//���� CCR��ֵ����С�ڻ����ARR��ֵ
	if(MotorSpeed <-(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);//���� 

	if(MotorSpeed<0) { PwmOne_Set = -MotorSpeed; PwmOne_Mode = MotorOneBack;}
	else { PwmOne_Set = MotorSpeed; PwmOne_Mode = MotorOneForward;}
	
	if(PwmOne_Mode) {TIM1->CCR1 = MotorSpdZero; TIM1->CCR2 = PwmOne_Set;} //MotorOneForward
	else { TIM1->CCR1 = PwmOne_Set; TIM1->CCR2 = MotorSpdZero;} //MotorOneBack	
}

////////////////////////////////
 
void MotorSpeedSetTwo(s32 MotorSpeed)//���2ת��/ת�����ã�TIM1��
{
  s32 PwmTwo_Set,PwmTwo_Mode;

  if(MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;//���� CCR��ֵ����С�ڻ����ARR��ֵ
  if(MotorSpeed <-(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);//���� 

  if(MotorSpeed<0) { PwmTwo_Set = -MotorSpeed; PwmTwo_Mode = MotorTwoBack;}
  else { PwmTwo_Set = MotorSpeed; PwmTwo_Mode = MotorTwoForward;}

  if(PwmTwo_Mode) {TIM1->CCR3 = MotorSpdZero; TIM1->CCR4 = PwmTwo_Set;} //MotorTwoForward
  else { TIM1->CCR3 = PwmTwo_Set; TIM1->CCR4 = MotorSpdZero;}	//MotorTwoBack
}

////////////////////////////////

void MotorSpeedSetThr(s32 MotorSpeed)//���3ת��/ת������(TIM8)
{		
	s32 PwmOne_Set,PwmOne_Mode;

	if(MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;//���� CCR��ֵ����С�ڻ����ARR��ֵ
	if(MotorSpeed <-(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);//���� 

	if(MotorSpeed<0) { PwmOne_Set = -MotorSpeed; PwmOne_Mode = MotorOneBack;}
	else { PwmOne_Set = MotorSpeed; PwmOne_Mode = MotorOneForward;}

	if(PwmOne_Mode) {TIM8->CCR1 = MotorSpdZero; TIM8->CCR2 = PwmOne_Set;} //MotorOneForward
	else { TIM8->CCR1 = PwmOne_Set; TIM8->CCR2 = MotorSpdZero;} //MotorOneBack	
}

////////////////////////////////

void MotorSpeedSetFou(s32 MotorSpeed)//���4ת��/ת������(TIM8)
{
  s32 PwmTwo_Set,PwmTwo_Mode;

  if(MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;//���� CCR��ֵ����С�ڻ����ARR��ֵ
  if(MotorSpeed <-(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);//���� 

  if(MotorSpeed<0) { PwmTwo_Set = -MotorSpeed; PwmTwo_Mode = MotorTwoBack;}
  else { PwmTwo_Set = MotorSpeed; PwmTwo_Mode = MotorTwoForward;}

  if(PwmTwo_Mode) {TIM8->CCR3 = MotorSpdZero; TIM8->CCR4 = PwmTwo_Set;} //MotorTwoForward
  else { TIM8->CCR3 = PwmTwo_Set; TIM8->CCR4 = MotorSpdZero;}	//MotorTwoBack
}


///////////LED ��ʼ��

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

//////SYSTICK ��ʼ��

void Systick_Configuration(void)
{
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8	9M
}

//////��ʱд��ӿ�

void SysDelay_ms(u16 nms)//72M������,nms<=1864(2^24/9000)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*Sys_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL=0x01;           //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	    
}

void SysDelay_us(u32 nus)//72M������,nus<=2^24
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*Sys_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01;       //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
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

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//����DMAʱ��

 	/*����DMAԴ���ڴ��ַ&�������ݼĴ�����ַ*/
    DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)&(USART3->DR);	   

	/*�ڴ��ַ(Ҫ����ı�����ָ��)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sbus_rx_buffer;
	
	/*���򣺴����赽�ڴ�*/		
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC ;	
	
	/*�����СDMA_BufferSize=SENDBUFF_SIZE*/	
    DMA_InitStructure.DMA_BufferSize = 18;
	
	/*�����ַ����*/	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	
	/*�ڴ��ַ����*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	
	/*�������ݵ�λ*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/*�ڴ����ݵ�λ 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	
	/*DMAģʽ��ѭ��*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular ;	 
	
	/*���ȼ����ǳ���*/	
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
	
	/*��ֹ�ڴ浽�ڴ�Ĵ���	*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	/*����DMA1��3ͨ��*/		   
    DMA_Init(DMA1_Channel3, &DMA_InitStructure); 	   
	
	DMA_Cmd (DMA1_Channel3,ENABLE);					//ʹ��DMA
	DMA_ITConfig(DMA1_Channel3,DMA_IT_TC,ENABLE);  //����DMA������ɺ�����ж�

}



//////Board Support Package

void BSP_Configuration(void)
{
  NVIC_Configuration();
  TIM_Configuration();
  Led_Configuration();
  Systick_Configuration();
  Can_chassis_one_motor_conf();
//	USART3_Config();
//	DMA_Config();
//	USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);

}







///////////��������ȡ

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










