#include "timer5.h"


void Encoder_Init_TIM5(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ�� TIM5 ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//ʹ�� GPIO ��ʱ�� �򿪸������޸ĸ��ù���

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;	//�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;						//��������
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;				//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);					      	//�����趨������ʼ��GPIOB

	//TIM3��ʱ���ź���ʵ����A/B���Ƶ���������ģ��������ⲿʱ�ӣ�Ȼ���Ƶ���Ƕ��������Ƶ�ʷ�Ƶ���������Ƶ���ǰ����������Ϊһ�����塣
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;					//����Ƶ
	TIM_TimeBaseStructure.TIM_Period = 65535;					//ÿ��һ�������źŵ������أ����������ã�����ֵ���ۼӣ����ۼ�����65535��Ϊ������ֵ���������
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //��������
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	/* ����Ƚ��˲��� */
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;

	TIM_ICInit(TIM5, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);				//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

	/* ���ñ�����ģʽ */
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);

  TIM5->CNT = 0;	//��������ʼ��
 
  TIM_Cmd(TIM5, ENABLE);	  //������ʱ��4
}

void TIM5_IRQHandler(void)  
{
   if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  
   {
       TIM_ClearITPendingBit(TIM5, TIM_IT_Update); 
   }
}