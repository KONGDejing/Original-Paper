#include "FramWork.h"
#include "math.h"
#include "BSP.h"

 MotorControlType MotorControl;
extern char mode=0;
extern RC_Ctl_t RC_Ctl; 
 
s32 Vx,Vy,Vo,VxNow,VyNow,VoNow,VxOld,VyOld,VoOld;
s16	VxNew=0,VyNew=0,VoNew=0;

extern int yuntai_value;
extern int mouse_press_r,mouse_press_l;

void DevelopmentFramwork(void)
{
   MotorControl.User_Kp = RM_Kp;	
   MotorControl.User_Ki = RM_Ki;
   MotorControl.User_Kd = RM_Kd;
   MotorControl.Err_Lim = RM_Lim;

//   MotorControl.User_Kp_1 = RM_Kp_1;	
//   MotorControl.User_Ki_1 = RM_Ki_1;
//   MotorControl.User_Kd_1 = RM_Kd_1;
//
//     Vx = (-RC_Ctl.rc.ch1 )*20;
// 	 Vy = (RC_Ctl.rc.ch0 - 1024)*4;
// 	 Vo = (RC_Ctl.rc.ch0 - 1024)*0.4;

//
//      MotorControl.MotorSpeedOne = Vx;
 //     MotorControl.MotorSpeedTwo = 0;

// 	 MotorControl.MotorSpeedTwo = -Vx;
// 	 MotorControl.MotorSpeedThr = 0;
// 	 MotorControl.MotorSpeedFou = 0;
// 	 
if(RC_Ctl.rc.s2==2||RC_Ctl.rc.s2==3)
{

      Vx = (1024-RC_Ctl.rc.ch1 )*60;
      MotorControl.MotorSpeedOne = Vx;
  }

		if(mode==0)
		{
	 MotorControl.MotorSpeedOne =0;

//	 MotorControl.MotorSpeedTwo =0;
//	 MotorControl.MotorSpeedThr =0;
//	 MotorControl.MotorSpeedFou =0;				
		}	 
	 
	
}









