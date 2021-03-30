#include "timer8.h"

u8 IS_MOTOR_ALL_STOP;	//��־�Ƿ�ǿ�����е��ͣת	0��ͣת		1ͣת

/*
*===================================================================
*		˵����TIM8��ʼ�����ã��Ա����PWM���������
*					TIM8.1 -> PC.6 ��ǰ���  TIM8.2 -> PC.7 �����
*					TIM8.3 -> PC.8 ��ǰ���	 TIM8.4 -> PC.9 �Һ���
*		������Period: ��ʱ���Զ���װֵ
*					Prescaler: ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
*		���أ���
*===================================================================
*/
void MOTOR_PWM_Init(u16 Period, u16 Prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;									//�������
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = Period; 										//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler; 							//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 0������Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 			//����ʱ�ӷָ� TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); 							//���� TIM_TimeBaseInitStruct ��ָ���Ĳ�����ʼ�� TIMx ��ʱ�������λ
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 						//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; 														//���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//�������:TIM����Ƚϼ���

	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  		//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  		//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
 	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  		//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);  		//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH2Ԥװ��ʹ��
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH3Ԥװ��ʹ��	
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��	
	
	TIM_ARRPreloadConfig(TIM8, ENABLE);									//Ԥװ�ؼĴ���

	TIM_Cmd(TIM8, ENABLE);  	//ʹ��TIM8
	
}

/*
*===================================================================
*		˵����TIM8 ռ�ձȵ��� ռ�ձ� = TIMx_CCRx / TIMx_ARR
*		������left_front_pwm��	��ǰ�ֵ��  ��ֵ 0-100
*					left_behind_pwm��	����ֵ��	��ֵ 0-100
*					right_front_pwm��	��ǰ�ֵ��	��ֵ 0-100
*					right_behind_pwm���Һ��ֵ��	��ֵ 0-100
*		���أ���
*===================================================================
*/
void MOTOR_PWM_Out(u16 left_front_pwm, u16 left_behind_pwm, u16 right_front_pwm, u16 right_behind_pwm)
{
	if(IS_MOTOR_ALL_STOP == 1)	left_front_pwm = left_behind_pwm = right_front_pwm = right_behind_pwm = 0;	//���е��ͣת
	TIM8->CCR1 = left_front_pwm;
	TIM8->CCR2 = left_behind_pwm;
	TIM8->CCR3 = right_front_pwm;
	TIM8->CCR4 = right_behind_pwm;
}
