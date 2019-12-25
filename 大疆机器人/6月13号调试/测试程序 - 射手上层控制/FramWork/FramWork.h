#ifndef __FRAMWORK_H
#define __FRAMWORK_H

#include "BSP.h"

//枪管
#define RM_Kp   2
#define RM_Ki   0.5
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
    float User_Kp;
	float User_Ki;
    float User_Kd;
    float Err_Lim;
	s32 MotorSpeedOne;
	s32 MotorSpeedTwo;
	s32 MotorSpeedThr;
	s32 MotorSpeedFou;

}MotorControlType;

void DevelopmentFramwork(void);

#endif

