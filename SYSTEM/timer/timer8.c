#include "timer8.h"


/*
*===================================================================
*		说明：TIM8初始化配置，以便输出PWM波驱动电机
*					TIM8.1 -> PC.6 左前电机  TIM8.2 -> PC.7 左后电机
*					TIM8.3 -> PC.8 右前电机	 TIM8.4 -> PC.9 右后电机
*		参数：Period: 定时器自动重装值
*					Prescaler: 时钟频率除数的预分频值
*		返回：无
*===================================================================
*/
void MOTOR_PWM_Init(u16 Period, u16 Prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									//复用推挽输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;							//悬空
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM8);
	
	TIM_TimeBaseStructure.TIM_Period = Period; 										//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler; 							//设置用来作为TIMx时钟频率除数的预分频值 0代表不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 			//设置时钟分割 TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 								////周期计数器值 
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); 							//根据 TIM_TimeBaseInitStruct 中指定的参数初始化 TIMx 的时间基数单位
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 						//选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	//关闭互补输出
	TIM_OCInitStructure.TIM_Pulse = 0; 														//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 			//输出极性:TIM输出比较极性
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;	//
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;	//

	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  		//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  		//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
 	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  		//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);  		//根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1预装载使能	
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH2预装载使能
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH3预装载使能	
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH4预装载使能	
	
	TIM_ARRPreloadConfig(TIM8, ENABLE);									//预装载寄存器

	TIM_Cmd(TIM8, ENABLE);  	//使能TIM8
	
	TIM_CtrlPWMOutputs(TIM8, ENABLE);										//TIM8->BDTR |= 1<<15;
}
