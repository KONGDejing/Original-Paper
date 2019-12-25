#include "RobotTask.h"
#include "FramWork.h"

extern MotorControlType MotorControl;

//绝对式PID算法
void PID_AbsoluteMode(PID_AbsoluteType* PID)
{
 if(PID->kp      < 0)    PID->kp      = -PID->kp;
 if(PID->ki      < 0)    PID->ki      = -PID->ki;
 if(PID->kd      < 0)    PID->kd      = -PID->kd;
 if(PID->errILim < 0)    PID->errILim = -PID->errILim;

 PID->errP = PID->errNow;  //读取现在的误差，用于kp控制

 PID->errI += PID->errNow; //误差积分，用于ki控制

 if(PID->errILim != 0)	   //微分上限和下限
 {
  if(     PID->errI >  PID->errILim)    PID->errI =  PID->errILim;
  else if(PID->errI < -PID->errILim)    PID->errI = -PID->errILim;
 }
 
 PID->errD = PID->errNow - PID->errOld;//误差微分，用于kd控制

 PID->errOld = PID->errNow;	//保存现在的误差
 
 PID->ctrOut = PID->kp * PID->errP + PID->ki * PID->errI + PID->kd * PID->errD;//计算绝对式PID输出

}

//增量式PID算法
void PID_IncrementMode(PID_IncrementType* PID)
{
 float dErrP, dErrI, dErrD;
 
 if(PID->kp < 0)    PID->kp = -PID->kp;
 if(PID->ki < 0)	PID->ki = -PID->ki;
 if(PID->kd < 0)    PID->kd = -PID->kd;

 dErrP = PID->errNow - PID->errOld1;

 dErrI = PID->errNow;

 dErrD = PID->errNow - 2 * PID->errOld1 + PID->errOld2;

 PID->errOld2 = PID->errOld1; //二阶误差微分
 PID->errOld1 = PID->errNow;  //一阶误差微分

 /*增量式PID计算*/
 PID->dCtrOut = PID->kp * dErrP + PID->ki * dErrI + PID->kd * dErrD;
 
 if(PID->kp == 0 && PID->ki == 0 && PID->kd == 0)   PID->ctrOut = 0;

 else PID->ctrOut += PID->dCtrOut;
}

//电机速度环伺服
s32 SpeedTagOne, SpeedNowOne, SpeedControlOne;
s32 SpeedTagTwo, SpeedNowTwo, SpeedControlTwo;
s32 SpeedTagThr, SpeedNowThr, SpeedControlThr;
s32 SpeedTagFou, SpeedNowFou, SpeedControlFou;

PID_AbsoluteType PidSpeedTypeOne,PidSpeedTypeTwo,PidSpeedTypeThr,PidSpeedTypeFou;

void PidSpeedControlOne(s32 Speed)
{
   SpeedNowOne = GetEncoder.CNT3; SpeedTagOne = Speed;   //无量纲   //GetEncoder.V3	CNT3
   PidSpeedTypeOne.errNow = SpeedTagOne - SpeedNowOne; //计算并写入速度误差   	
   PidSpeedTypeOne.kp      = MotorControl.User_Kp;                       //写入比例系数为15
   PidSpeedTypeOne.ki      = MotorControl.User_Ki;                        //写入积分系数为5
   PidSpeedTypeOne.kd      = MotorControl.User_Kd;                        //写入微分系数为5
   PidSpeedTypeOne.errILim = MotorControl.Err_Lim;                     //写入误差积分上限
   PID_AbsoluteMode(&PidSpeedTypeOne);                 //执行绝对式PID算法	
   SpeedControlOne = PidSpeedTypeOne.ctrOut;           //读取控制值
   MotorSpeedSetThr(SpeedControlOne);                 //放入PWM，用于收敛速度的控制中
}

void PidSpeedControlTwo(s32 Speed)
{
   SpeedNowTwo = GetEncoder.V5; SpeedTagTwo = Speed;   //无量纲   GetEncoder.V5
   PidSpeedTypeTwo.errNow = SpeedTagTwo - SpeedNowTwo; //计算并写入速度误差   	
   PidSpeedTypeTwo.kp      = RM_Kp_1;                       //写入比例系数为15
   PidSpeedTypeTwo.ki      = RM_Ki_1;                        //写入积分系数为5
   PidSpeedTypeTwo.kd      = RM_Kd_1;                        //写入微分系数为5
   PidSpeedTypeTwo.errILim = MotorControl.Err_Lim;                     //写入误差积分上限
   PID_AbsoluteMode(&PidSpeedTypeTwo);                 //执行绝对式PID算法	
   SpeedControlTwo = PidSpeedTypeTwo.ctrOut;           //读取控制值
   MotorSpeedSetFou(SpeedControlTwo);                 //放入PWM，用于收敛速度的控制中
}

void PidSpeedControlThr(s32 Speed)
{
   SpeedNowThr = GetEncoder.V2; SpeedTagThr = Speed;   //无量纲
   PidSpeedTypeThr.errNow = SpeedTagThr - SpeedNowThr; //计算并写入速度误差   	
   PidSpeedTypeThr.kp      = MotorControl.User_Kp;                 //写入比例系数为15
   PidSpeedTypeThr.ki      = MotorControl.User_Ki;                  //写入积分系数为5
   PidSpeedTypeThr.kd      = MotorControl.User_Kd;                  //写入微分系数为5
   PidSpeedTypeThr.errILim = MotorControl.Err_Lim;               //写入误差积分上限
   PID_AbsoluteMode(&PidSpeedTypeThr);           //执行绝对式PID算法	
   SpeedControlThr = PidSpeedTypeThr.ctrOut;        //读取控制值
   MotorSpeedSetOne(SpeedControlOne); 
	              //放入PWM，用于收敛速度的控制中
}

void PidSpeedControlFou(s32 Speed)
{
   SpeedNowFou = GetEncoder.V4; SpeedTagFou = Speed;   //无量纲
   PidSpeedTypeFou.errNow = SpeedTagFou - SpeedNowFou; //计算并写入速度误差   	
   PidSpeedTypeFou.kp      = MotorControl.User_Kp;                 //写入比例系数为15
   PidSpeedTypeFou.ki      = MotorControl.User_Ki;                  //写入积分系数为5
   PidSpeedTypeFou.kd      = MotorControl.User_Kd;                  //写入微分系数为5
   PidSpeedTypeFou.errILim = MotorControl.Err_Lim;               //写入误差积分上限
   PID_AbsoluteMode(&PidSpeedTypeFou);           //执行绝对式PID算法	
   SpeedControlFou = PidSpeedTypeFou.ctrOut;        //读取控制值
   MotorSpeedSetTwo(SpeedControlTwo); 
	               //放入PWM，用于收敛速度的控制中
}






















