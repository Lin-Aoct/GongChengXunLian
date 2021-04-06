#ifndef __KEY_H
#define __KEY_H	 
#include "headfiles.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
 extern int a1_2,a2_2,a3,a4;

#define KEY0   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//读取按键0
#define KEY1   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)//读取按键1
#define KEY2   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13)//读取按键2 
#define KEY3   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)//读取按键0
#define KEY4   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)//读取按键1
#define KEY5   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)//读取按键2 
#define KEY6 	 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
#define KEY7 	 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define KEY2_PRES	3		//WK_UP 
#define KEY4_PRES	1		//KEY0  
#define KEY5_PRES	2		//KEY1 
#define KEY6_PRES	3		//WK_UP 

extern int k0,k1,k2,k3,k4,k5;
extern u8 key_add,key_sub;





extern void KEY_Init(void);//IO初始化
extern void KEY_Scan(void);  	//按键扫描函数			
extern void debug_arm(void);
#endif
