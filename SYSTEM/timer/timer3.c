#include "timer3.h"

/*
*===================================================================
*		˵����TIM3�ж����ȼ�����
*		��������
*		���أ���
*===================================================================
*/
//void TIM3_NVIC_Configuration(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure; 

//	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  													
//	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//}


void Encoder_Init_TIM3(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);		//ʹ�� TIM3 ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		//ʹ�� GPIO ��ʱ�� �򿪸������޸ĸ��ù���

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;						//����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;					//����
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;				//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);

	//TIM3��ʱ���ź���ʵ����A/B���Ƶ���������ģ��������ⲿʱ�ӣ�Ȼ���Ƶ���Ƕ��������Ƶ�ʷ�Ƶ���������Ƶ���ǰ����������Ϊһ�����塣
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;					//����Ƶ
	TIM_TimeBaseStructure.TIM_Period = 65535;					//ÿ��һ�������źŵ������أ����������ã�����ֵ���ۼӣ����ۼ�����65535��Ϊ������ֵ���������
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //��������
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* ����Ƚ��˲��� */
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);				//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	/* ���ñ�����ģʽ */
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);

//	TIM3->CCMR1 |= 2 << 0;
//	TIM3->CCMR1 |= 2 << 8;
//	TIM3->CCER |= 1<<1; //IC1����
//	TIM3->CCER |= 1<<5; //IC2����

  TIM3->CNT = 0;	//��������ʼ��
 
  TIM_Cmd(TIM3, ENABLE);	  //������ʱ��3
}

void TIM3_IRQHandler(void)  
{
   if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  
   {
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
   }
}
