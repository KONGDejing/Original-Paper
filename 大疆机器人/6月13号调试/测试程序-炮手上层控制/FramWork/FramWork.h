#ifndef __FRAMWORK_H
#define __FRAMWORK_H

#include "BSP.h"

//枪管
#define RM_Kp   4
#define RM_Ki   0
#define RM_Kd   0
//拨弹
#define RM_Kp_1   70
#define RM_Ki_1   50
#define RM_Kd_1    0

//#define RM_Kp   70
//#define RM_Ki   50
//#define RM_Kd   0

//#define RM_Kp   2
//#define RM_Ki   0
//#define RM_Kd  



// //大疆电机
// #define RM_Kp1   2
// #define RM_Ki1   0
// #define RM_Kd1   0

//shaobing
// #define RM_Kp   10.1
// #define RM_Ki   3.7
// #define RM_Kd   0.2

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

