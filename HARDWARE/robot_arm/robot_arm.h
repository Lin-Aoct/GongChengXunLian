#ifndef _ROBOT_ARM_H_
#define _ROBOT_ARM_H_
#include "headfiles.h"

/*-----------------------0.5ms��Ӧ����250
											1.5ms��Ӧ����750
									2.5ms��Ӧ����1250-------------------------------*/

//���ƻ�е�۵Ķ����Ƕ�
#define Arm0  TIM9->CCR1//PE5צ�ӿ�520 ��980
#define Arm1  TIM9->CCR2//PE6�ؽ�1�°�1250 �ϰ�650
#define Arm2  TIM10->CCR1//PF6�ؽ�2�¼���1250
#define Arm3  TIM12->CCR1//PB14�ؽ�3 ��500��900
#define Arm4  TIM12->CCR2//PB15��̨1250�� ��250



/************************** TIM ��������********************************/

/**********************************TIM9**************************************/
#define             mac_TIM_CH1_PORT                        GPIOE
#define             mac_TIM_CH1_PIN                         GPIO_Pin_5//
#define             mac_TIM_CH2_PORT                        GPIOE
#define             mac_TIM_CH2_PIN                         GPIO_Pin_6//



/**********************************TIM10**************************************/
#define             mac2_TIM_CH1_PORT                        GPIOF
#define             mac2_TIM_CH1_PIN                         GPIO_Pin_6//

/**********************************TIM12**************************************/
#define             mac3_TIM_CH1_PORT                        GPIOB
#define             mac3_TIM_CH1_PIN                         GPIO_Pin_14//
#define             mac3_TIM_CH2_PORT                        GPIOB
#define             mac3_TIM_CH2_PIN                         GPIO_Pin_15//


  

extern void RobotArm_Pwm_init(void);//��ʼ����е�۵�PWMͨ����
extern void RobotArm_Reset(void);//��е�۵ĸ�λ
extern float Arm_angle(u16 angle);//��е��ת���Ƕ�


 


#endif
