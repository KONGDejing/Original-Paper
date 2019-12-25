#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
//#include "lcd.h"
#include "key.h"
#include "dma.h"
#include "adc.h"
#include "timer.h"
#include "exti.h"
#include "math.h"
//ALIENTEK Mini STM32开发板范例代码18
//DMA实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
#define N 2000
#define M N/2
#define pi 3.1415926535897932

typedef union {
	u16 sincos[2];
	float fsin;
} MyUnion;
MyUnion Usincosseperate1[M],Usincosseperate2[M];


u32 ADData[N];
u8 Update_flag=0;
u16 Period;
float AbsSum,SumAbs;
float temp;

void DMA1_Channel1_IRQHandler(void)      //中断判断DMA是否传输完成
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC1)==SET){
		    //ADC_Cmd(ADC1, DISABLE);	
		  Update_flag=1;
	      DMA_ClearITPendingBit(DMA1_IT_TC1);
	}
} 

void myunwrap(MyUnion *p,u16 num){
	   float temp1,temp2;
	   u16 i;
       temp1=p[0].fsin;
				for(i=1;i<num;i++)
				{
					temp2=p[i].fsin;
						if(temp2-temp1>pi)                           
						   p[i].fsin=p[i-1].fsin+temp2-temp1-2*pi; 
						else if(temp2-temp1<-pi) 
						   p[i].fsin=p[i-1].fsin+temp2-temp1+2*pi; 
						else
						   p[i].fsin=p[i-1].fsin+temp2-temp1; 
                    temp1=temp2;					
				} 
			 }		

 void GetEllFitPara(MyUnion *p,double *mid_val,u16 num)
	 {
		 double xmean,ymean, temp1,temp2,temp1s,temp2s,coeff1,coeff2;
		 u16 i,j,k;
		 double A[5][5],b[5];
		 xmean=0;ymean=0;
		 for(i=0;i<num;i++)
		 {
			xmean+=(double)(p[i].sincos[0]);
			ymean+=(double)(p[i].sincos[1]);
		 }
		 xmean/=num; ymean/=num;                 //求均值
		 //get the A matrix and b
		 for(i=0;i<5;i++)
		 {
			 b[i]=0;
			 for(j=0;j<5;j++)
			 A[i][j]=0;		 
		 }
		 
		 for(k=0;k<num;k++)
		 {
		     temp1=(double)(p[k].sincos[0])-xmean;
			 temp2=(double)(p[k].sincos[1])-ymean;
			 temp1s=temp1*temp1;temp2s=temp2*temp2;
			 A[0][0]+=temp1s*temp2s;
			 A[0][1]+=temp1*temp2s*temp2;
			 A[0][2]+=temp1s*temp2;
			 A[0][3]+=temp1*temp2s;
			 A[0][4]+=temp1*temp2;		 
			 A[1][1]+=temp2s*temp2s;
			 A[1][3]+=temp2s*temp2;
			 A[1][4]+=temp2s;	 
			 A[2][2]+=temp1s;
			 A[2][4]+=temp1;	 
			 A[3][4]+=temp2;
			 b[0]-=temp1s*temp1*temp2;  //x3y
			 b[1]-=temp1s*temp2s;   //x2y2
			 b[2]-=temp1s*temp1;   //x3
			 b[3]-=temp1s*temp2;   //x2y
			 b[4]-=temp1s;  //x2
	   }
		 A[3][3]=A[1][4];
		 A[1][2]=A[0][3];
		 A[2][3]=A[0][4];
		 A[4][4]=num;
		 for(i=1;i<5;i++)
			 for(j=0;j<i;j++)
			 {
			   A[i][j]=A[j][i];
			 }	
		//solve the eiilpse fit parameters
	   for(i=0;i<5;i++)
	   {
		 coeff1=A[i][i];
		 for(k=0;k<5;k++)
			{
				A[i][k]=A[i][k]/coeff1;
			}
		 b[i]/=coeff1;
		 for(j=0;j<5;j++)
			 {
				coeff2=A[j][i];
				if(j!=i)
				{
			       for(k=i;k<5;k++)
					 
					{
						A[j][k]-=coeff2*A[i][k];
					}
					b[j]-=coeff2*b[i];
				}
			 }
		}
		 for(i=0;i<5;i++)
		 b[i]=-b[i];
		 temp1=sqrt(-b[1]);
		 mid_val[4]=acos(b[0]/(2*temp1));
		 //offset1 offset2 are mid_val[2] mid_val[3]
		 mid_val[3]=(b[0]*b[2]+2*b[3])/(-4*b[1]-b[0]*b[0]);
		 mid_val[2]=b[2]/2+b[0]*mid_val[3]/2;
		 //amp1 amp2 are mid_val[0] mid_val[1]
		 mid_val[0]=sqrt(mid_val[2]*mid_val[2]-b[1]*mid_val[3]*mid_val[3]-b[0]*mid_val[2]*mid_val[3]+b[4])/sin(mid_val[4]);
		 mid_val[1]=mid_val[0]/temp1;
		
		 mid_val[2]+=xmean;
		 mid_val[3]+=ymean;	 
 }
 int main(void)
 { 
	 
	 u8 data2[100],error_flag;
	 u16 x1,i,counter,cur_index,k;

	 float tempcos,tempsin,temp1,temp2,tempangle,temporiginal1,temporiginal2;
	 double para1[5],para2[5];
	 u16 InterTem; 
	 Period=M;
     delay_init();
     uart_init(115200);	   //没有问题
	 Adc_Init();	       
	 EXTIX_Init();	
	 MYDMA_Config(DMA1_Channel1,(u32)&ADC1->DR,(u32)ADData,N);	//DMA初始化的时候已经启动了第一次DMA传输 
	 TIM4_Configuration(); //配置采样频率

	 do{

		 if(Update_flag==1)
		 {	            
   		//put this data to union array. after this, we can restart A/D transfer  
			 for(i=0;i<N;i++)
			 {  
				 if(i%2==0){
				 Usincosseperate1[i/2].sincos[0]=ADData[i]&0xfff;     //一象限数据               
				 Usincosseperate1[i/2].sincos[1]=(ADData[i]&0xfff0000)>>16;//二象限数据 //数据真正只有12位，其中有4位是保留位
				 }
				 if(i%2==1){
				 Usincosseperate2[i/2].sincos[0]=ADData[i]&0xfff;           //二象限数据，与一二象限的数据时钟相隔240个ADC时钟周期        
				 Usincosseperate2[i/2].sincos[1]=(ADData[i]&0xfff0000)>>16; //三象限数据
				 }
						
             }
			 for(i=0;i<N/2;i++){
				 sprintf((char *)data2,"%d  %d  %d  %d\r\n",Usincosseperate1[i].sincos[0],Usincosseperate1[i].sincos[1],
					 Usincosseperate2[i].sincos[0],Usincosseperate2[i].sincos[1]);	   
				 printf(data2);	
				 sprintf((char *)data2,"    OVER   \r\n\n\n\n\n");	   
				 printf(data2);	
			 }
		 
        //----------------------- start the next sample data ----------------------------//	
			  InterTem=0;
				for(i=0;i<10;i++)	
				{
					ADC_SoftwareStartInjectedConvCmd(ADC1,ENABLE);     //软件触发注入式  ADC_CR2
					while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_JEOC));
					ADC_ClearFlag(ADC1,ADC_FLAG_JEOC);
					InterTem+=ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_1);	  			
				}
			    InterTem=InterTem/10;
				
                Update_flag=0;				 
		        MYDMA_Enable(DMA1_Channel1);  
        //----------------get the amplification and offset and phase difference----------//
		//	 GetEllFitPara(Usincos,para1,N); 
        /*     amp1=para1[0];  //amp2=para1[1];	
             off1=para1[2];  //off2=para1[3];
             counter=0;
			 for(i=0;i<N/20;i++)
				 if((Usincos[i].sincos[0]>off1&&Usincos[i+1].sincos[0]<off1)||
					    (Usincos[i].sincos[0]<off1&&Usincos[i+1].sincos[0]>off1))
							counter++;		 
               if(counter<3000)
			   {
					GetEllFitPara(Usincos,para1,N);		*/		 
		//----------------the data is scaled and get the phase---------------------------//
				//-----------------一二象限椭圆拟合+解包裹---------------------------------//
				
				    GetEllFitPara(Usincosseperate1,para1,M);	//只需要提取其中的相位差
					tempcos=cos(para1[4]);tempsin=sin(para1[4]);
					for(i=0;i<M;i++)
					{
						 temp1=(float)Usincosseperate1[i].sincos[0];
						 temp1=(temp1-para1[2])/para1[0];
						 temp2=(float)Usincosseperate1[i].sincos[1];
						 temp2=(temp2-para1[3])/para1[1];
						 Usincosseperate1[i].fsin=atan2((temp1*tempcos-temp2)/tempsin,temp1);
				    }						   
					myunwrap(Usincosseperate1,M);      //解包裹暂时用不上
					
				//-----------------二三象限椭圆拟合+解包裹---------------------------------//
					
					GetEllFitPara(Usincosseperate2,para2,M);	
					tempcos=cos(para2[4]);tempsin=sin(para2[4]);
					for(i=0;i<M;i++)
					{
						 temp1=(float)Usincosseperate2[i].sincos[0];
						 temp1=(temp1-para2[2])/para2[0];
						 temp2=(float)Usincosseperate2[i].sincos[1];
						 temp2=(temp2-para2[3])/para2[1];
						 Usincosseperate2[i].fsin=atan2((temp1*tempcos-temp2)/tempsin,temp1);
				    }							   
					myunwrap(Usincosseperate2,M);      //解包裹暂时用不上
					
		       }		
/*              else
			   {
					 counter=0; cur_index=0;
					 tempangle=0;
					 for(i=0;i<N-1;i++)
				     {
						 if((Usincos[i].sincos[0]>off1&&Usincos[i+1].sincos[0]<off1)||
								(Usincos[i].sincos[0]<off1&&Usincos[i+1].sincos[0]>off1))
									counter++;	
						 if(counter==6||(i==N-2&&counter>2))
						{
							 counter=0;
							 GetEllFitPara(&Usincos[cur_index],para1,i-cur_index+1);	//fit the data from cur_index to i
							//save the original sample data from last one of current segment
							 temporiginal1=Usincos[i].sincos[0];temporiginal2=Usincos[i].sincos[1]; 
							 //get the phase
							 tempcos=cos(para1[4]);tempsin=sin(para1[4]);
							   for(k=cur_index;k<i+1;k++)
							   {
										 temp1=(float)Usincos[k].sincos[0];
										 temp1=(temp1-para1[2])/para1[0];
										 temp2=(float)Usincos[k].sincos[1];
										 temp2=(temp2-para1[3])/para1[1];
										 Usincos[k].fsin=atan2((temp1*tempcos-temp2)/tempsin,temp1);
								  
							   }
						//-------get unwrap value-----------//
							 myunwrap(&Usincos[cur_index],i-cur_index+1); 								  
					    //------start piece the phase together,old phase substract new phase nad put into the tempangle
							 temp1=tempangle-Usincos[cur_index].fsin;
////								   sprintf((char *)lcd_data2,"last=%f,now=%f \r\n",tempangle,Usincos[cur_index].fsin);
////                                   printf(lcd_data2);
							 for(k=cur_index;k<i+1;k++)
									Usincos[k].fsin+=temp1;
					//save the last phase,as old phase prepare for next time
							 tempangle=Usincos[i].fsin;//save the phase of last point,prepare for next piecing together
                           	 cur_index=i; //the current last point as the start point of next fit. prepare for next fit 
									//put the original data of last one into Usincos[i],
									//because its phase has been saved to tempangle temperoarily.
							 Usincos[i].sincos[0]=temporiginal1;
							 Usincos[i].sincos[1]=temporiginal2; 	
				         }
			          }
		          }
*/
		 			
//-------------- get current temperature of innerchip ----------------------------------------//		
               //----------------------去直流----------------------//
/*				for(i=0;i<N-M/2;i++)
					Usincos[i].fsin=Usincos[i+M/2].fsin-Usincos[i].fsin;
		        for(i=0;i<N-M;i++)
				    Usincos[i].fsin=Usincos[i+M/2].fsin-Usincos[i].fsin;
				             
    		//find the first zero point position	
				temp1=0;temp2=0;				 
				for(i=0;i<N/10;i++) {
					if(temp1>Usincos[i].fsin)
						temp1=Usincos[i].fsin;
					else if(temp2<Usincos[i].fsin)
						temp2=Usincos[i].fsin;
				}
				
				error_flag=0;
				amp1=(temp2-temp1)/2;
				for(i=1;i<N-M;i++)
				  if(fabs(Usincos[i].fsin-Usincos[i-1].fsin)>0.06*pi*amp1){
					  error_flag=1;					  
					  break;
				  }

				if(error_flag==0)
				{
					 x1=0;
					 for(i=1;i<M;i++)
					 {
						 if(Usincos[i-1].fsin*Usincos[i].fsin<=0)
						 {
							  x1=i-1;
							  break;
						 }
					 }
					 
					 //get the absolute sum which starts fom zero point 				   
				     AbsSum=0; SumAbs=0; 
				     for(i=x1;i<N-2*M+x1;i++)
					 {

						 AbsSum+=fabs(Usincos[i].fsin);
						 SumAbs+=Usincos[i].fsin;
					 }
			    }		
*/								
//             sprintf((char *)lcd_data2,"%f  %f  %f  %f  %d  %d  %d\n",AbsSum/39.3838/2,SumAbs/39.3838,Usincos[x1].fsin,Usincos[x1+1].fsin,InterTem,OutsideTem ,error_flag);	   
//             printf(lcd_data2);				 			
			 delay_ms(10);
		  			 
	 }while(1);
  	 
}
