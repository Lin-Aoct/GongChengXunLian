#include "timer2.h"


/*
*===================================================================
*		˵����TIM2 ��ʼ������ ��ǰ���������
*					TIM2.1 -> PA.5 ��ǰ���A  TIM2.2 -> PB.3 ��ǰ���B
*		������Period: ��ʱ���Զ���װֵ
*					Prescaler: ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
*		���أ���
*===================================================================
*/
void Encoder_Init_TIM2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);													//ʹ�� TIM2 ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);	//ʹ�� GPIO ��ʱ�� �򿪸������޸ĸ��ù���

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;								//PA.5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;						//��������
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;				//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;								//PB.3
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);
	
	//TIM2��ʱ���ź���ʵ����A/B���Ƶ���������ģ��������ⲿʱ�ӣ�Ȼ���Ƶ���Ƕ��������Ƶ�ʷ�Ƶ���������Ƶ���ǰ����������Ϊһ�����塣
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);		//TB�ṹ�帳ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 0;					//����Ƶ
	TIM_TimeBaseStructure.TIM_Period = 65535;					//ÿ��һ�������źŵ������أ����������ã�����ֵ���ۼӣ����ۼ�����65535��Ϊ������ֵ���������
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //��������
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* ����Ƚ��˲��� */
	TIM_ICStructInit(&TIM_ICInitStructure);			//IC�ṹ�帳ֵ
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);				//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	/* ���ñ�����ģʽ */
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);

  TIM2->CNT = 0;	//��������ʼ��
 
  TIM_Cmd(TIM2, ENABLE);	  //����TIM2
}

void TIM2_IRQHandler(void)  
{
   if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  
   {
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
   }
}
