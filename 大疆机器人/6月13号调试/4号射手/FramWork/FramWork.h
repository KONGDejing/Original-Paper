#ifndef __FRAMWORK_H
#define __FRAMWORK_H

#include "BSP.h"

#define RM_Kp   10
#define RM_Ki   13
#define RM_Kd   5
#define RM_Lim  1000

#define Pi      3.1415927
#define Beita	  Pi/4


typedef struct
{
  u16 User_Kp;
	u16 User_Ki;
  u16 User_Kd;
  u16 Err_Lim;
	s16 MotorSpeedOne;
	s16 MotorSpeedTwo;
	s16 MotorSpeedThr;
	s16 MotorSpeedFou;

}MotorControlType;

void DevelopmentFramwork(void);

#endif

