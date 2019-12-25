 #include "adc.h"
 #include "delay.h"
 #include "sys.h"
// #include "stm32f10x_adc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	   
		   
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	
//----------------------ʹ��GPIO/ADC1/ADC2ͨ��ʱ�� -------------------------------------//
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2, ENABLE );	 
 
//----------------------------PA/PC ��Ϊģ��ͨ����������----------------------------------//                      
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
//-----------------------ADC configuration --------------------------------------------//
	  RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 ADCʱ��Ƶ��(���ǲ���Ƶ��)Ϊ72M/6=12M,ADC���ʱ�䲻�ܳ���14M
		
	  //---------------- ADC1 configuration ����ͨ��------------------------------------//
	  ADC_DeInit(ADC1);          //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	  ADC_InitStructure.ADC_Mode = ADC_Mode_RegInjecSimult ; //ADC����ģʽ:ADC1��ADC2�����ڻ�ϵ�ͬ������+ע��ͬ��
	  ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //ģ��ת�������ڵ���ת��ģʽ
	  ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_T4_CC4;// ��ʱ��4�¼������������ⲿ�¼���˫ADC��������ADC���ⲿ��������ADC���������
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //ADC�����Ҷ���
	  ADC_InitStructure.ADC_NbrOfChannel = 2;
	  ADC_Init(ADC1, &ADC_InitStructure);  //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ��������������6�����ø���ADC1 
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_239Cycles5); // ADC1 regular channels configuration
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_239Cycles5); // ADC1 regular channels configuration
				 
	  //---------------- ADC2 configuration ����ͨ��------------------------------------//
	  ADC_DeInit(ADC2);  //��λADC2,������ ADC2��ȫ���Ĵ�������Ϊȱʡֵ
	  ADC_InitStructure.ADC_Mode = ADC_Mode_RegInjecSimult;
	  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //�������(SWSTART)
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_NbrOfChannel = 2;
	  ADC_Init(ADC2, &ADC_InitStructure);   //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ��������������6�����ø���ADC2
	  ADC_RegularChannelConfig(ADC2, ADC_Channel_3, 1, ADC_SampleTime_239Cycles5);// ˫ADC����£���Ҫѡ��ͬһ��ͨ��
	  ADC_RegularChannelConfig(ADC2, ADC_Channel_14, 2, ADC_SampleTime_239Cycles5); // ADC2 regular channels configuration
	  
	
      //-----------------Initial for injected group ����ͨ���Ѿ����úã����ǲ�����-----------------//
	  ADC_ExternalTrigInjectedConvConfig(ADC1,ADC_ExternalTrigInjecConv_None); //
	  //ADC_ExternalTrigInjectedConvConfig(ADC2,ADC_ExternalTrigInjecConv_None);
      ADC_InjectedSequencerLengthConfig(ADC1, 1);
      //ADC_InjectedSequencerLengthConfig(ADC2, 1);
      ADC_InjectedChannelConfig(ADC1,ADC_Channel_16,1,ADC_SampleTime_239Cycles5);     //�ɼ�оƬ�ڲ��¶�
   	  //ADC_InjectedChannelConfig(ADC2,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);      //�ɼ�pt100�¶ȵ����ⲿ�¶�
	  ADC_TempSensorVrefintCmd(ENABLE);
      ADC_SetInjectedOffset(ADC1,ADC_InjectedChannel_1,0);
	  //ADC_SetInjectedOffset(ADC2,ADC_InjectedChannel_1,0);
      //ADC_ExternalTrigInjectedConvCmd(ADC2, ENABLE);

	
	//-------------------У׼��ʹ��ADC1/ADC2--------------//
    /* Enable ADC2 */
    ADC_Cmd(ADC2, ENABLE);    
    ADC_ResetCalibration(ADC2);      // Enable ADC2 reset calibaration register 
    while(ADC_GetResetCalibrationStatus(ADC2));//Check the end of ADC2 reset calibration register
    ADC_StartCalibration(ADC2);             //Start ADC2 calibaration 
    while(ADC_GetCalibrationStatus(ADC2));  //Check the end of ADC2 calibration
  
    /* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼   
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	ADC_StartCalibration(ADC1);	 //����ADC1У׼״̬
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
	
	//-------------------ʹ��DMA����----------------------//
	
	ADC_DMACmd(ADC1, ENABLE);
	
    //-------------------�ⲿ������������--��Թ���ͨ����-------------------//  
	 
    ADC_ExternalTrigConvCmd(ADC1, ENABLE);
	ADC_ExternalTrigConvCmd(ADC2, ENABLE);  
	

	
 
}				  



























