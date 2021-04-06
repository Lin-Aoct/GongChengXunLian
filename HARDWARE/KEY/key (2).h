#ifndef __KEY_H
#define __KEY_H	 
#include "headfiles.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
 extern int a1_2,a2_2,a3,a4;

#define KEY0   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//��ȡ����0
#define KEY1   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)//��ȡ����1
#define KEY2   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13)//��ȡ����2 
#define KEY3   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)//��ȡ����0
#define KEY4   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)//��ȡ����1
#define KEY5   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)//��ȡ����2 
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





extern void KEY_Init(void);//IO��ʼ��
extern void KEY_Scan(void);  	//����ɨ�躯��			
extern void debug_arm(void);
#endif
