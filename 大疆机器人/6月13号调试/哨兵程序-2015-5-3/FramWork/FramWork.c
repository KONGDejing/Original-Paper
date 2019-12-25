#include "FramWork.h"
#include "math.h"
#include "BSP.h"

 MotorControlType MotorControl;
extern char mode=0;
extern RC_Ctl_t RC_Ctl; 

s16 Vx,Vy,Vo,VxNow,VyNow,VoNow,VxOld,VyOld,VoOld;
s16	VxNew=0,VyNew=0,VoNew=0;

void DevelopmentFramwork(void)
{
   MotorControl.User_Kp = RM_Kp;	
   MotorControl.User_Ki = RM_Ki;
   MotorControl.User_Kd = RM_Kd;
   MotorControl.Err_Lim = RM_Lim;
//
     Vx = (RC_Ctl.rc.ch1 - 1024)*10.5;
 	 Vy = (1024-RC_Ctl.rc.ch3 )*10.5;
// 	 Vo = (RC_Ctl.rc.ch0 - 1024)*0.4;



// MotorControl.MotorSpeedTwo = 20;
     MotorControl.MotorSpeedOne = Vx;
 	 MotorControl.MotorSpeedTwo = -Vx;
 	 MotorControl.MotorSpeedThr = Vy;
// 	 MotorControl.MotorSpeedFou = 0;
// 	 
		if(mode==0)
		{
	 MotorControl.MotorSpeedOne =0;
	 MotorControl.MotorSpeedTwo =0;
	 MotorControl.MotorSpeedThr =0;
	 MotorControl.MotorSpeedFou =0;				
		}	 
	 
	
}









