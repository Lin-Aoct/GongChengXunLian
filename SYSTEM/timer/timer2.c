#include "timer2.h"


/*
*===================================================================
*		说明：TIM2 初始化配置 左前电机编码器
*					TIM2.1 -> PA.5 左前电机A  TIM2.2 -> PB.3 左前电机B
*		参数：Period: 定时器自动重装值
*					Prescaler: 时钟频率除数的预分频值
*		返回：无
*===================================================================
*/
void Encoder_Init_TIM2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);													//使能 TIM2 时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);	//使能 GPIO 口时钟 打开复用再修改复用功能

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;								//PA.5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;						//浮空输入
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;				//浮空
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;								//PB.3
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);
	
	//TIM2的时钟信号其实是由A/B相的频率来决定的，类似于外部时钟，然后分频就是对这个脉冲频率分频，比如二分频就是把两个脉冲记为一个脉冲。
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);		//TB结构体赋值
	TIM_TimeBaseStructure.TIM_Prescaler = 0;					//不分频
	TIM_TimeBaseStructure.TIM_Period = 65535;					//每来一个脉冲信号的上升沿（下面有设置）计数值就累加（或累减），65535则为最大计数值，就溢出了
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数方向
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* 输入比较滤波器 */
	TIM_ICStructInit(&TIM_ICInitStructure);			//IC结构体赋值
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);				//清除TIM的更新标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	/* 设置编码器模式 */
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);

  TIM2->CNT = 0;	//计数器初始化
 
  TIM_Cmd(TIM2, ENABLE);	  //开启TIM2
}

void TIM2_IRQHandler(void)  
{
   if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  
   {
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
   }
}
