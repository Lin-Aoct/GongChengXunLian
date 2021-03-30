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

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;											//PA.5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;						//��������
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;				//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;											//PB.3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;						//��������
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;				//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//TIM2��ʱ���ź���ʵ����A/B���Ƶ���������ģ��������ⲿʱ�ӣ�Ȼ���Ƶ���Ƕ��������Ƶ�ʷ�Ƶ���������Ƶ���ǰ����������Ϊһ�����塣
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0;					//����Ƶ
	TIM_TimeBaseStructure.TIM_Period = 65535;					//ÿ��һ�������źŵ������أ����������ã�����ֵ���ۼӣ����ۼ�����65535��Ϊ������ֵ���������
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //��������
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* ����Ƚ��˲��� */
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;

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
/*
*===================================================================
*		˵����TIM2 TIM4 ռ�ձȵ��� ռ�ձ� = TIMx_CCRx / TIMx_ARR
*		������left_front_pwm��	��ǰ�ֵ��  ��ֵ 0-100
*					left_behind_pwm��	����ֵ��	��ֵ 0-100
*					right_front_pwm��	��ǰ�ֵ��	��ֵ 0-100
*					right_behind_pwm���Һ��ֵ��	��ֵ 0-100
*		���أ���
*===================================================================
*/
//void MOTOR_PWM_Out(u16 left_front_pwm, u16 left_behind_pwm, u16 right_front_pwm, u16 right_behind_pwm)
//{
//	if(IS_MOTOR_ALL_STOP == 1)	left_front_pwm = left_behind_pwm = right_front_pwm = right_behind_pwm = 0;	//���е��ͣת
//	TIM2->CCR1 = left_front_pwm;
//	TIM2->CCR2 = left_behind_pwm;
//	TIM2->CCR3 = right_front_pwm;
//	TIM2->CCR4 = right_behind_pwm;
//}
