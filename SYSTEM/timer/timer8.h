#ifndef __TIMER8_H
#define __TIMER8_H
#include "stm32f4xx.h"


void MOTOR_PWM_Init(u16 Period, u16 Prescaler);											//��� PWM �����ʼ��
void MOTOR_PWM_Out(u16 left_front_pwm, u16 left_behind_pwm, u16 right_front_pwm, u16 right_behind_pwm);		//������ PWM

#endif
