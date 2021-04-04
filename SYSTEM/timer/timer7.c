#include "timer7.h"


/*
*===================================================================
*		说明：定时器7初始化配置
*		参数：period: 定时器自动重装值
*					prescaler: 时钟频率除数的预分频值
*		返回：无
*===================================================================
*/
void TIM7_Init(u16 period, u16 prescaler)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); 	//TIM7时钟使能

	TIM_TimeBaseStructure.TIM_Period = period; 						//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler; 			//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); 			//初始化TIM7
 
	TIM_ClearFlag(TIM7, TIM_FLAG_Update);
	
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE); 						//使能TIM7计数器中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; 	//TIM7中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  	//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  											//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	TIM_Cmd(TIM7, ENABLE);  															//使能TIM7外设
}

/*
*===================================================================
*		说明：定时器7中断服务函数
*		参数：无
*		返回：无
*===================================================================
*/
void TIM7_IRQHandler(void)
{    
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)	//检查指定的TIM中断发生与否
	{
		u8 count;
//		ENCODER_DATA[0] = Read_Encoder(2);
//		ENCODER_DATA[1] = Read_Encoder(3);
//		ENCODER_DATA[2] = Read_Encoder(4);
//		ENCODER_DATA[3] = Read_Encoder(5);

		printf("编码器[%d %d %d %d]\t", ENCODER_DATA[0], ENCODER_DATA[1], ENCODER_DATA[2], ENCODER_DATA[3]);// Find_Test();
		printf("PWM[");
		for(count=0; count<=3; count++)
			printf("%d ", MOTOR_PWM[count]);
		printf("] 目标[%.0f]", speed_target);
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);			//清除TIM6的中断待处理位
  }       	
}
