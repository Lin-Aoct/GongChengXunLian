#ifndef __FIND_H
#define __FIND_H

#include "sys.h"

//红外循迹模块输入接口
#define Find_Front_1 GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_13)
#define Find_Front_2 GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_15)
#define Find_Front_3 GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11)
#define Find_Front_4 GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9)

#define Find_Right_1 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4)
#define Find_Right_2 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6)
#define Find_Right_3 GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0)
#define Find_Right_4 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11)


void Find_IO_Init(void);
void Find_Test(void);
void Find(void);
u16 Find_Get_Front(void);
u16 Find_Get_Right(void);
void Car_Continue(void);
void Stop_Find(void);

#endif
