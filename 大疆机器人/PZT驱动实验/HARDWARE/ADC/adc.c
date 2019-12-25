 #include "adc.h"
 #include "delay.h"
 #include "sys.h"
// #include "stm32f10x_adc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//ADC 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	   
		   
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	
//----------------------使能GPIO/ADC1/ADC2通道时钟 -------------------------------------//
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2, ENABLE );	 
 
//----------------------------PA/PC 作为模拟通道输入引脚----------------------------------//                      
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
//-----------------------ADC configuration --------------------------------------------//
	  RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 ADC时钟频率(不是采样频率)为72M/6=12M,ADC最大时间不能超过14M
		
	  //---------------- ADC1 configuration 规则通道------------------------------------//
	  ADC_DeInit(ADC1);          //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值
	  ADC_InitStructure.ADC_Mode = ADC_Mode_RegInjecSimult ; //ADC工作模式:ADC1和ADC2工作在混合的同步规则+注入同步
	  ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在单通道模式
	  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //模数转换工作在单次转换模式
	  ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_T4_CC4;// 定时器4事件触发，属于外部事件，双ADC触发，主ADC是外部触发，从ADC是软件触发
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //ADC数据右对齐
	  ADC_InitStructure.ADC_NbrOfChannel = 2;
	  ADC_Init(ADC1, &ADC_InitStructure);  //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器，即将上面的6条设置赋给ADC1 
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_239Cycles5); // ADC1 regular channels configuration
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_239Cycles5); // ADC1 regular channels configuration
				 
	  //---------------- ADC2 configuration 规则通道------------------------------------//
	  ADC_DeInit(ADC2);  //复位ADC2,将外设 ADC2的全部寄存器重设为缺省值
	  ADC_InitStructure.ADC_Mode = ADC_Mode_RegInjecSimult;
	  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //软件触发(SWSTART)
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_NbrOfChannel = 2;
	  ADC_Init(ADC2, &ADC_InitStructure);   //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器，即将上面的6条设置赋给ADC2
	  ADC_RegularChannelConfig(ADC2, ADC_Channel_3, 1, ADC_SampleTime_239Cycles5);// 双ADC情况下，不要选择同一个通道
	  ADC_RegularChannelConfig(ADC2, ADC_Channel_14, 2, ADC_SampleTime_239Cycles5); // ADC2 regular channels configuration
	  
	
      //-----------------Initial for injected group 规则通道已经配置好，但是不采用-----------------//
	  ADC_ExternalTrigInjectedConvConfig(ADC1,ADC_ExternalTrigInjecConv_None); //
	  //ADC_ExternalTrigInjectedConvConfig(ADC2,ADC_ExternalTrigInjecConv_None);
      ADC_InjectedSequencerLengthConfig(ADC1, 1);
      //ADC_InjectedSequencerLengthConfig(ADC2, 1);
      ADC_InjectedChannelConfig(ADC1,ADC_Channel_16,1,ADC_SampleTime_239Cycles5);     //采集芯片内部温度
   	  //ADC_InjectedChannelConfig(ADC2,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);      //采集pt100温度电阻外部温度
	  ADC_TempSensorVrefintCmd(ENABLE);
      ADC_SetInjectedOffset(ADC1,ADC_InjectedChannel_1,0);
	  //ADC_SetInjectedOffset(ADC2,ADC_InjectedChannel_1,0);
      //ADC_ExternalTrigInjectedConvCmd(ADC2, ENABLE);

	
	//-------------------校准并使能ADC1/ADC2--------------//
    /* Enable ADC2 */
    ADC_Cmd(ADC2, ENABLE);    
    ADC_ResetCalibration(ADC2);      // Enable ADC2 reset calibaration register 
    while(ADC_GetResetCalibrationStatus(ADC2));//Check the end of ADC2 reset calibration register
    ADC_StartCalibration(ADC2);             //Start ADC2 calibaration 
    while(ADC_GetCalibrationStatus(ADC2));  //Check the end of ADC2 calibration
  
    /* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	ADC_ResetCalibration(ADC1);	//使能复位校准   
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	ADC_StartCalibration(ADC1);	 //开启ADC1校准状态
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
	
	//-------------------使能DMA传输----------------------//
	
	ADC_DMACmd(ADC1, ENABLE);
	
    //-------------------外部触发命令启动--针对规则通道的-------------------//  
	 
    ADC_ExternalTrigConvCmd(ADC1, ENABLE);
	ADC_ExternalTrigConvCmd(ADC2, ENABLE);  
	

	
 
}				  



























