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

//	 Vx = (1024-RC_Ctl.rc.ch0)*2.5;
//	 Vy = (RC_Ctl.rc.ch3-1024 )*2.5;
//	 Vo = (RC_Ctl.rc.ch2 - 1024)*2.5;

if(RC_Ctl.rc.s2==1)
{
if(RC_Ctl.mouse.x==0)
{
Vx=0;
Vy=0;
Vo=0;
}

 if(RC_Ctl.key.v==0)
{
Vx=0;
Vy=0;
Vo=0;
}

if(RC_Ctl.key.v==1)
{
Vy=3000;
}
if(RC_Ctl.key.v==2)
{
Vy=-3000;
}

if(RC_Ctl.key.v==4)
{
Vo=-3000;
}
if(RC_Ctl.key.v==8)
{
Vo=3000;
}

if(RC_Ctl.key.v==5)
{
Vy=3000;
Vo=-3000;
}


if(RC_Ctl.key.v==6)
{
Vy=-3000;
Vo=-3000;
}

if(RC_Ctl.key.v==9)
{
Vy=3000;
Vo=3000;
}

if(RC_Ctl.key.v==10)
{
Vy=-3000;
Vo=3000;
}





if(RC_Ctl.mouse.x<0)
{
Vx=(-RC_Ctl.mouse.x)*30;
}

if(RC_Ctl.mouse.x>0)
{
Vx=(-RC_Ctl.mouse.x)*30;

}
	 MotorControl.MotorSpeedOne = (Vx+Vy-Vo);
	 MotorControl.MotorSpeedTwo = (Vx-Vy-Vo);
	 MotorControl.MotorSpeedThr = -(-Vx+Vy-Vo);
	 MotorControl.MotorSpeedFou = -(-Vx-Vy-Vo);	
	 }

if(RC_Ctl.rc.s2==2||RC_Ctl.rc.s2==3)
{
	 Vx = (1024-RC_Ctl.rc.ch0)*2.5;
	 Vy = (RC_Ctl.rc.ch3-1024 )*2.5;
	 Vo = (RC_Ctl.rc.ch2 - 1024)*2.5;

	 MotorControl.MotorSpeedOne = (Vx+Vy-Vo);
	 MotorControl.MotorSpeedTwo = (Vx-Vy-Vo);
	 MotorControl.MotorSpeedThr = -(-Vx+Vy-Vo);
	 MotorControl.MotorSpeedFou = -(-Vx-Vy-Vo);

}

// 	 MotorControl.MotorSpeedOne = 0;	
	
// 	 MotorControl.MotorSpeedOne = -Vx+Vy-Vo;
// 	 MotorControl.MotorSpeedTwo = -Vx-Vy-Vo;
// 	 MotorControl.MotorSpeedThr =  Vx-Vy-Vo;
// 	 MotorControl.MotorSpeedFou =  Vx+Vy-Vo;
	 
		if(mode==0)
		{
	 MotorControl.MotorSpeedOne =0;
	 MotorControl.MotorSpeedTwo =0;
	 MotorControl.MotorSpeedThr =0;
	 MotorControl.MotorSpeedFou =0;				
		}	 
	 
	
}









