#ifndef _ROBOT_ARM_H_
#define _ROBOT_ARM_H_
#include "headfiles.h"

/*-----------------------0.5ms对应的是250
											1.5ms对应的是750
									2.5ms对应的是1250-------------------------------*/

//控制机械臂的动作角度
#define Arm0  TIM9->CCR1//PE5爪子开520 合980
#define Arm1  TIM9->CCR2//PE6关节1下摆1250 上摆650
#define Arm2  TIM10->CCR1//PF6关节2下极限1250
#define Arm3  TIM12->CCR1//PB14关节3 下500下900
#define Arm4  TIM12->CCR2//PB15云台1250左 右250



/************************** TIM 函数声明********************************/

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


  

extern void RobotArm_Pwm_init(void);//初始化机械臂的PWM通道。
extern void RobotArm_Reset(void);//机械臂的复位
extern float Arm_angle(u16 angle);//机械手转动角度


 


#endif
