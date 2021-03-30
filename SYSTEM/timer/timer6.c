#include "timer6.h"


/*
*===================================================================
*		˵������ʱ��6��ʼ������
*		������period: ��ʱ���Զ���װֵ
*					prescaler: ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
*		���أ���
*===================================================================
*/
void TIM6_Init(u16 period, u16 prescaler)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); 	//TIM6ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = period; 						//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler; 			//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 			//��ʼ��TIM6
 
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
	
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE); 						//ʹ��TIM6�������ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn; 	//TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  											//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	TIM_Cmd(TIM6, ENABLE);  															//ʹ��TIM6����
}
