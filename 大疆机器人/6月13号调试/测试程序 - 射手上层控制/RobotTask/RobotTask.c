#include "RobotTask.h"
#include "FramWork.h"

extern MotorControlType MotorControl;

//����ʽPID�㷨
void PID_AbsoluteMode(PID_AbsoluteType* PID)
{
 if(PID->kp      < 0)    PID->kp      = -PID->kp;
 if(PID->ki      < 0)    PID->ki      = -PID->ki;
 if(PID->kd      < 0)    PID->kd      = -PID->kd;
 if(PID->errILim < 0)    PID->errILim = -PID->errILim;

 PID->errP = PID->errNow;  //��ȡ���ڵ�������kp����

 PID->errI += PID->errNow; //�����֣�����ki����

 if(PID->errILim != 0)	   //΢�����޺�����
 {
  if(     PID->errI >  PID->errILim)    PID->errI =  PID->errILim;
  else if(PID->errI < -PID->errILim)    PID->errI = -PID->errILim;
 }
 
 PID->errD = PID->errNow - PID->errOld;//���΢�֣�����kd����

 PID->errOld = PID->errNow;	//�������ڵ����
 
 PID->ctrOut = PID->kp * PID->errP + PID->ki * PID->errI + PID->kd * PID->errD;//�������ʽPID���

}

//����ʽPID�㷨
void PID_IncrementMode(PID_IncrementType* PID)
{
 float dErrP, dErrI, dErrD;
 
 if(PID->kp < 0)    PID->kp = -PID->kp;
 if(PID->ki < 0)	PID->ki = -PID->ki;
 if(PID->kd < 0)    PID->kd = -PID->kd;

 dErrP = PID->errNow - PID->errOld1;

 dErrI = PID->errNow;

 dErrD = PID->errNow - 2 * PID->errOld1 + PID->errOld2;

 PID->errOld2 = PID->errOld1; //�������΢��
 PID->errOld1 = PID->errNow;  //һ�����΢��

 /*����ʽPID����*/
 PID->dCtrOut = PID->kp * dErrP + PID->ki * dErrI + PID->kd * dErrD;
 
 if(PID->kp == 0 && PID->ki == 0 && PID->kd == 0)   PID->ctrOut = 0;

 else PID->ctrOut += PID->dCtrOut;
}

//����ٶȻ��ŷ�
s32 SpeedTagOne, SpeedNowOne, SpeedControlOne;
s32 SpeedTagTwo, SpeedNowTwo, SpeedControlTwo;
s32 SpeedTagThr, SpeedNowThr, SpeedControlThr;
s32 SpeedTagFou, SpeedNowFou, SpeedControlFou;

PID_AbsoluteType PidSpeedTypeOne,PidSpeedTypeTwo,PidSpeedTypeThr,PidSpeedTypeFou;

void PidSpeedControlOne(s32 Speed)
{
   SpeedNowOne = GetEncoder.CNT3; SpeedTagOne = Speed;   //������   //GetEncoder.V3	CNT3
   PidSpeedTypeOne.errNow = SpeedTagOne - SpeedNowOne; //���㲢д���ٶ����   	
   PidSpeedTypeOne.kp      = MotorControl.User_Kp;                       //д�����ϵ��Ϊ15
   PidSpeedTypeOne.ki      = MotorControl.User_Ki;                        //д�����ϵ��Ϊ5
   PidSpeedTypeOne.kd      = MotorControl.User_Kd;                        //д��΢��ϵ��Ϊ5
   PidSpeedTypeOne.errILim = MotorControl.Err_Lim;                     //д������������
   PID_AbsoluteMode(&PidSpeedTypeOne);                 //ִ�о���ʽPID�㷨	
   SpeedControlOne = PidSpeedTypeOne.ctrOut;           //��ȡ����ֵ
   MotorSpeedSetThr(SpeedControlOne);                 //����PWM�����������ٶȵĿ�����
}

void PidSpeedControlTwo(s32 Speed)
{
   SpeedNowTwo = GetEncoder.V5; SpeedTagTwo = Speed;   //������   GetEncoder.V5
   PidSpeedTypeTwo.errNow = SpeedTagTwo - SpeedNowTwo; //���㲢д���ٶ����   	
   PidSpeedTypeTwo.kp      = RM_Kp_1;                       //д�����ϵ��Ϊ15
   PidSpeedTypeTwo.ki      = RM_Ki_1;                        //д�����ϵ��Ϊ5
   PidSpeedTypeTwo.kd      = RM_Kd_1;                        //д��΢��ϵ��Ϊ5
   PidSpeedTypeTwo.errILim = MotorControl.Err_Lim;                     //д������������
   PID_AbsoluteMode(&PidSpeedTypeTwo);                 //ִ�о���ʽPID�㷨	
   SpeedControlTwo = PidSpeedTypeTwo.ctrOut;           //��ȡ����ֵ
   MotorSpeedSetFou(SpeedControlTwo);                 //����PWM�����������ٶȵĿ�����
}

void PidSpeedControlThr(s32 Speed)
{
   SpeedNowThr = GetEncoder.V2; SpeedTagThr = Speed;   //������
   PidSpeedTypeThr.errNow = SpeedTagThr - SpeedNowThr; //���㲢д���ٶ����   	
   PidSpeedTypeThr.kp      = MotorControl.User_Kp;                 //д�����ϵ��Ϊ15
   PidSpeedTypeThr.ki      = MotorControl.User_Ki;                  //д�����ϵ��Ϊ5
   PidSpeedTypeThr.kd      = MotorControl.User_Kd;                  //д��΢��ϵ��Ϊ5
   PidSpeedTypeThr.errILim = MotorControl.Err_Lim;               //д������������
   PID_AbsoluteMode(&PidSpeedTypeThr);           //ִ�о���ʽPID�㷨	
   SpeedControlThr = PidSpeedTypeThr.ctrOut;        //��ȡ����ֵ
   MotorSpeedSetOne(SpeedControlOne); 
	              //����PWM�����������ٶȵĿ�����
}

void PidSpeedControlFou(s32 Speed)
{
   SpeedNowFou = GetEncoder.V4; SpeedTagFou = Speed;   //������
   PidSpeedTypeFou.errNow = SpeedTagFou - SpeedNowFou; //���㲢д���ٶ����   	
   PidSpeedTypeFou.kp      = MotorControl.User_Kp;                 //д�����ϵ��Ϊ15
   PidSpeedTypeFou.ki      = MotorControl.User_Ki;                  //д�����ϵ��Ϊ5
   PidSpeedTypeFou.kd      = MotorControl.User_Kd;                  //д��΢��ϵ��Ϊ5
   PidSpeedTypeFou.errILim = MotorControl.Err_Lim;               //д������������
   PID_AbsoluteMode(&PidSpeedTypeFou);           //ִ�о���ʽPID�㷨	
   SpeedControlFou = PidSpeedTypeFou.ctrOut;        //��ȡ����ֵ
   MotorSpeedSetTwo(SpeedControlTwo); 
	               //����PWM�����������ٶȵĿ�����
}






















