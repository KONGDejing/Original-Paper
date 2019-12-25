#include "BSP.h"
#include "RobotTask.h"
/*********************************************
Author     :JasonLin
Version	   :V2.0		   Ownership-Reserved
Date       :2015/3/15
Description:MCIO Motor Control Support Package  
**********************************************/

int main(void)
{	
  SystemInit();

  BSP_Configuration();

	while(1)
	{
		SysDelay_ms(20);LED2=!LED2;SysDelay_ms(20);//LED2提示系统正常运行
	}
	
}

