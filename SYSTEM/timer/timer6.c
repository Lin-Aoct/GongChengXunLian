#include "timer6.h"


/*
*===================================================================
*		说明：定时器6初始化配置
*		参数：period: 定时器自动重装值
*					prescaler: 时钟频率除数的预分频值
*		返回：无
*===================================================================
*/
void TIM6_Init(u16 period, u16 prescaler)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); 	//TIM6时钟使能

	TIM_TimeBaseStructure.TIM_Period = period; 						//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler; 			//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 			//初始化TIM6
 
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
	
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE); 						//使能TIM6计数器中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn; 	//TIM6中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  	//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  											//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	TIM_Cmd(TIM6, ENABLE);  															//使能TIM6外设
}
