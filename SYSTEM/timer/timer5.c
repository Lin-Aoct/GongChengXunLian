#include "timer5.h"


void Encoder_Init_TIM5(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能 TIM5 时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//使能 GPIO 口时钟 打开复用再修改复用功能

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;	//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;						//复用
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;					//推挽
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;				//浮空
	GPIO_Init(GPIOA, &GPIO_InitStructure);					      	//根据设定参数初始化GPIOB

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
	
	//TIM3的时钟信号其实是由A/B相的频率来决定的，类似于外部时钟，然后分频就是对这个脉冲频率分频，比如二分频就是把两个脉冲记为一个脉冲。
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;					//不分频
	TIM_TimeBaseStructure.TIM_Period = 65535;					//每来一个脉冲信号的上升沿（下面有设置）计数值就累加（或累减），65535则为最大计数值，就溢出了
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数方向
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	/* 输入比较滤波器 */
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;

	TIM_ICInit(TIM5, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);				//清除TIM的更新标志位
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

	/* 设置编码器模式 */
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);

  TIM5->CNT = 0;	//计数器初始化
 
  TIM_Cmd(TIM5, ENABLE);	  //开启定时器4
}

void TIM5_IRQHandler(void)  
{
   if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  
   {
       TIM_ClearITPendingBit(TIM5, TIM_IT_Update); 
   }
}
