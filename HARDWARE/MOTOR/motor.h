#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"


#define GO    0		//正转
#define BACK  1 	//反转
#define STOP  2 	//停车

#define MOTO_PIN1_PORT GPIOF
#define MOTO_PIN2_PORT GPIOF
#define MOTO_PIN3_PORT GPIOF
#define MOTO_PIN4_PORT GPIOF

#define MOTO_PIN5_PORT GPIOE
#define MOTO_PIN6_PORT GPIOE
#define MOTO_PIN7_PORT GPIOE
#define MOTO_PIN8_PORT GPIOE


#define MOTO_PIN1  GPIO_Pin_1
#define MOTO_PIN2  GPIO_Pin_3
#define MOTO_PIN3  GPIO_Pin_5
#define MOTO_PIN4  GPIO_Pin_7

#define MOTO_PIN5  GPIO_Pin_4
#define MOTO_PIN6  GPIO_Pin_2
#define MOTO_PIN7  GPIO_Pin_1
#define MOTO_PIN8  GPIO_Pin_3

//#define MOTO_PIN_STBY  GPIO_Pin_5

/* 带参宏，可以像内联函数一样使用 */
#define IN1(a)	if (a)	\
					GPIO_SetBits(MOTO_PIN1_PORT, MOTO_PIN1);\
					else		\
					GPIO_ResetBits(MOTO_PIN1_PORT, MOTO_PIN1)
					
#define IN2(a)	if (a)	\
					GPIO_SetBits(MOTO_PIN2_PORT, MOTO_PIN2);\
					else		\
					GPIO_ResetBits(MOTO_PIN2_PORT, MOTO_PIN2)
					
#define IN3(a)	if (a)	\
					GPIO_SetBits(MOTO_PIN3_PORT, MOTO_PIN3);\
					else		\
					GPIO_ResetBits(MOTO_PIN3_PORT, MOTO_PIN3)
					
#define IN4(a)	if (a)	\
					GPIO_SetBits(MOTO_PIN4_PORT, MOTO_PIN4);\
					else		\
					GPIO_ResetBits(MOTO_PIN4_PORT, MOTO_PIN4)

#define IN5(a)	if (a)	\
					GPIO_SetBits(MOTO_PIN5_PORT, MOTO_PIN5);\
					else		\
					GPIO_ResetBits(MOTO_PIN5_PORT, MOTO_PIN5)
				
#define IN6(a)	if (a)	\
					GPIO_SetBits(MOTO_PIN6_PORT, MOTO_PIN6);\
					else		\
					GPIO_ResetBits(MOTO_PIN6_PORT, MOTO_PIN6)
					
#define IN7(a)	if (a)	\
					GPIO_SetBits(MOTO_PIN7_PORT, MOTO_PIN7);\
					else		\
					GPIO_ResetBits(MOTO_PIN7_PORT, MOTO_PIN7)
					
#define IN8(a)	if (a)	\
					GPIO_SetBits(MOTO_PIN8_PORT, MOTO_PIN8);\
					else		\
					GPIO_ResetBits(MOTO_PIN8_PORT, MOTO_PIN8)


void MOTO_GPIO_Config(void);
void Set_MOTOR_Left_Front(char state);
void Set_MOTOR_Left_Behind(char state);
void Set_MOTOR_Right_Front(char state);
void Set_MOTOR_Right_Behind(char state);
void Car_Go(void);
void Car_Back(void);
void Car_Go_Left(void);
void Car_Go_Right(void);
void Car_Stop(void);
void Car_Right_Front(void);
void Car_Left_Front(void);
void Car_Turn(void);
void Car_Raw_Left(void);
void Car_Raw_Right(void);
					
void MOTOR_Speed_Up(u16 motor_pwm);
void MOTOR_Speed_Down(u16 motor_pwm);
void MOTOR_PWM_Out(u16 left_front_pwm, u16 left_behind_pwm, u16 right_front_pwm, u16 right_behind_pwm);		//输出电机 PWM

#endif
