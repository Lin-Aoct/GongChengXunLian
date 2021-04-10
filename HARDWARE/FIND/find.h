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

#define Find_Left_1 GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_1)
#define Find_Left_2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)
#define Find_Left_3 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_15)
#define Find_Left_4 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_13)

#define Find_Behind_1 GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_0)
#define Find_Behind_2 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_14)
#define Find_Behind_3 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)
#define Find_Behind_4 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)

void Find_IO_Init(void);
void Find_Test(void);
void Find(void);
u16 Find_Get_Front(void);
u16 Find_Get_Right(void);
u16 Find_Get_Behind(void);
u16 Find_Get_Left(void);
void Car_Continue(void);
void Stop_Find(void);

#endif
