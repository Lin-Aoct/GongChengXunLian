#include "timer7.h"


/*
*===================================================================
*		˵������ʱ��7��ʼ������
*		������period: ��ʱ���Զ���װֵ
*					prescaler: ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
*		���أ���
*===================================================================
*/
void TIM7_Init(u16 period, u16 prescaler)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); 	//TIM7ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = period; 						//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler; 			//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); 			//��ʼ��TIM7
 
	TIM_ClearFlag(TIM7, TIM_FLAG_Update);
	
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE); 						//ʹ��TIM7�������ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; 	//TIM7�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  											//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	TIM_Cmd(TIM7, ENABLE);  															//ʹ��TIM7����
}

/*
*===================================================================
*		˵������ʱ��7�жϷ�����
*		��������
*		���أ���
*===================================================================
*/
void TIM7_IRQHandler(void)
{    
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)	//���ָ����TIM�жϷ������
	{
		u8 count;
//		ENCODER_DATA[0] = Read_Encoder(2);
//		ENCODER_DATA[1] = Read_Encoder(3);
//		ENCODER_DATA[2] = Read_Encoder(4);
//		ENCODER_DATA[3] = Read_Encoder(5);

		printf("������[%d %d %d %d]\t", ENCODER_DATA[0], ENCODER_DATA[1], ENCODER_DATA[2], ENCODER_DATA[3]);// Find_Test();
		printf("PWM[");
		for(count=0; count<=3; count++)
			printf("%d ", MOTOR_PWM[count]);
		printf("] Ŀ��[%.0f]", speed_target);
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);			//���TIM6���жϴ�����λ
  }       	
}
