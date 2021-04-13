#include "motor.h"

//u16 MOTOR_PWM[4] = {20000, 20000, 20000, 20000,};						//��ǰ���CCRֵ
//u16 MAX_MOTOR_PWM = 32000;	//������CCRֵ

u8 IS_MOTOR_ALL_STOP = 0;	//��־�Ƿ�ǿ�����е��ͣת	0��ͣת		1ͣת

u8 MOTOR_PWM[4] = {160, 160, 160, 160};						//��ǰ���CCRֵ
u8 MAX_MOTOR_PWM = 200;	//������CCRֵ

/*
*===================================================================
*		˵�������õ������ IN ��
*		��������
*		���أ���
*===================================================================
*/
void MOTO_GPIO_Config(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;																							//���� GPIO_InitTypeDef ���͵Ľṹ��

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF, ENABLE);  		//����GPIO������ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;	//���ÿ��Ƶ�GPIO����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                    //ͨ�ø���������� 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;									//����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 //������������Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);                            //��ʼ��GPIO

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7;	//���ÿ��Ƶ�GPIO����
	GPIO_Init(GPIOF, &GPIO_InitStructure);				//��ʼ��GPIO
}


/*
*===================================================================
*		˵����������ǰ��� IN ��״̬
*		������state	����˶�״̬
*		���أ���
*===================================================================
*/
void Set_MOTOR_Left_Front(char state)
{
	if(state == GO)		//��ǰ���ǰ��
	{
		IN1(0);
		IN2(1);
	}
	if(state == BACK)	//��ǰ�������
	{
		IN1(1);
		IN2(0);
	}
	if(state == STOP)	//��ǰ���ͣת
	{
	  IN1(0);
		IN2(0);
	}
}

/*
*===================================================================
*		˵������������� IN ��״̬
*		������state	����˶�״̬
*		���أ���
*===================================================================
*/
void Set_MOTOR_Left_Behind(char state)
{
	if(state == GO)		//�����ǰ��
	{
		IN3(0);
		IN4(1);
	}
	if(state == BACK)	//���������
	{
		IN3(1);
		IN4(0);
	}
	if(state == STOP)//�����ͣת
	{
	  IN3(0);
		IN4(0);
	}
}

/*
*===================================================================
*		˵����������ǰ��� IN ��״̬
*		������state	����˶�״̬
*		���أ���
*===================================================================
*/
void Set_MOTOR_Right_Front(char state)
{
	if(state == GO)		//��ǰ���ǰ��
	{
		IN5(0);
		IN6(1);
	}
	if(state == BACK)	//��ǰ�������
	{
		IN5(1);
		IN6(0);
	}
	if(state == STOP)	//��ǰ���ͣת
	{
	  IN5(0);
		IN6(0);
	}
}

/*
*===================================================================
*		˵���������Һ��� IN ��״̬
*		������state	����˶�״̬
*		���أ���
*===================================================================
*/
void Set_MOTOR_Right_Behind(char state)
{
	if(state == GO)		//�����ǰ��
	{
		IN7(0);
		IN8(1);
	}
	if(state == BACK)	//���������
	{
		IN7(1);
		IN8(0);
	}
	if(state == STOP)//�����ͣת
	{
	  IN7(0);
		IN8(0);
	}
}


/*
*===================================================================
*		˵����С����ǰ��
*		��������
*		���أ���
*===================================================================
*/
void Car_Go(void)
{
	Set_MOTOR_Left_Front(GO);
	Set_MOTOR_Left_Behind(GO);
	Set_MOTOR_Right_Front(GO);
	Set_MOTOR_Right_Behind(GO);
}


//***************************С������***************************//
void Car_Back(void)
{
	Set_MOTOR_Left_Front(BACK);
	Set_MOTOR_Left_Behind(BACK);
	Set_MOTOR_Right_Front(BACK);
	Set_MOTOR_Right_Behind(BACK);
}

////***************************С������ֱ��***************************//
void Car_Go_Right(void)
{
	Set_MOTOR_Left_Front(GO);
	Set_MOTOR_Left_Behind(BACK);
	Set_MOTOR_Right_Front(BACK);
	Set_MOTOR_Right_Behind(GO);
}

//***************************С������ֱ��***************************//
void Car_Go_Left(void)
{
	Set_MOTOR_Left_Front(BACK);
	Set_MOTOR_Left_Behind(GO);
	Set_MOTOR_Right_Front(GO);
	Set_MOTOR_Right_Behind(BACK);
}

//***************************С��ͣ��***************************//
void Car_Stop(void)
{
	Set_MOTOR_Left_Front(STOP);
	Set_MOTOR_Left_Behind(STOP);
	Set_MOTOR_Right_Front(STOP);
	Set_MOTOR_Right_Behind(STOP);
}

//***************************��ǰ45��***************************//
void Car_Right_Front(void)
{
	Set_MOTOR_Left_Front(GO);
	Set_MOTOR_Left_Behind(STOP);
	Set_MOTOR_Right_Front(STOP);
	Set_MOTOR_Right_Behind(GO);
}

//***************************��ǰ45��***************************//
void Car_Left_Front(void)
{
	Set_MOTOR_Left_Front(STOP);
	Set_MOTOR_Left_Behind(GO);
	Set_MOTOR_Right_Front(GO);
	Set_MOTOR_Right_Behind(STOP);
}

//***************************ԭ����ת***************************//
void Car_Yaw_Left(void)
{
	Set_MOTOR_Left_Front(BACK);
	Set_MOTOR_Left_Behind(BACK);
	Set_MOTOR_Right_Front(GO);
	Set_MOTOR_Right_Behind(GO);
}

//***************************ԭ����ת***************************//
void Car_Yaw_Right(void)
{
	Set_MOTOR_Left_Front(GO);
	Set_MOTOR_Left_Behind(GO);
	Set_MOTOR_Right_Front(BACK);
	Set_MOTOR_Right_Behind(BACK);
}

//***************************ԭ��180�ȵ�ͷ***************************//
void Car_Turn(void)
{
	Set_MOTOR_Left_Front(GO);
	Set_MOTOR_Left_Behind(STOP);
	Set_MOTOR_Right_Front(BACK);
	Set_MOTOR_Right_Behind(STOP);
}

/*
*===================================================================
*		˵����С������
*		������motor_pwm	<u16>	С�����ٵ�CCRֵ
*		���أ���
*===================================================================
*/
void MOTOR_Speed_Up(u16 motor_pwm)
{
	MOTOR_PWM[0]+=motor_pwm;
	MOTOR_PWM[1]+=motor_pwm;
	MOTOR_PWM[2]+=motor_pwm;
	MOTOR_PWM[3]+=motor_pwm;
	printf("\t%d, %d", MOTOR_PWM[0], MOTOR_PWM[1]);
}

/*
*===================================================================
*		˵����С������
*		������motor_pwm	<u16>	С�����ٵ�CCRֵ
*		���أ���
*===================================================================
*/
void MOTOR_Speed_Down(u16 motor_pwm)
{
	MOTOR_PWM[0]-=motor_pwm;
	MOTOR_PWM[1]-=motor_pwm;
	MOTOR_PWM[2]-=motor_pwm;
	MOTOR_PWM[3]-=motor_pwm;
	printf("\t%d, %d", MOTOR_PWM[0], MOTOR_PWM[1]);
}

/*
*===================================================================
*		˵�������� X Y W ������������������˶��ٶ�
*		������xSpeed��X �����ٶ�
*					ySpeed��Y �����ٶ�
*					wSpeed��W �����ٶ�
*		���أ���
*===================================================================
*/
void Calc_Motor_PWM(float xSpeed, float ySpeed, float wSpeed)
{
    float m1_speed = ySpeed - xSpeed + wSpeed; 
    float m2_speed = ySpeed + xSpeed - wSpeed;
    float m3_speed = ySpeed - xSpeed - wSpeed;
    float m4_speed = ySpeed + xSpeed + wSpeed;
    
    float max = m1_speed;
    if (max < m2_speed)   max = m2_speed;
    if (max < m3_speed)   max = m3_speed;
    if (max < m4_speed)   max = m4_speed;
    
    if (max > MAX_MOTOR_PWM)
    {
        m1_speed = m1_speed / max * MAX_MOTOR_PWM;
        m2_speed = m2_speed / max * MAX_MOTOR_PWM;
        m3_speed = m3_speed / max * MAX_MOTOR_PWM;
        m4_speed = m4_speed / max * MAX_MOTOR_PWM;
    }
    
    MOTOR_PWM_Out(m2_speed, m3_speed, m1_speed, m4_speed);
}



/*
*===================================================================
*		˵����TIM8 ռ�ձȵ��� ռ�ձ� = TIMx_CCRx / TIMx_ARR
*		������left_front_pwm��	��ǰ�ֵ��  ��ֵ 0-500
*					left_behind_pwm��	����ֵ��	��ֵ 0-500
*					right_front_pwm��	��ǰ�ֵ��	��ֵ 0-500
*					right_behind_pwm���Һ��ֵ��	��ֵ 0-500
*		���أ���
*===================================================================
*/
void MOTOR_PWM_Out(u16 left_front_pwm, u16 left_behind_pwm, u16 right_front_pwm, u16 right_behind_pwm)
{
	if(left_front_pwm > MAX_MOTOR_PWM)	left_front_pwm = MOTOR_PWM[0] = MAX_MOTOR_PWM;
	if(left_behind_pwm > MAX_MOTOR_PWM)	left_behind_pwm = MOTOR_PWM[1] = MAX_MOTOR_PWM;
	if(right_front_pwm > MAX_MOTOR_PWM)	right_front_pwm = MOTOR_PWM[2] = MAX_MOTOR_PWM;
	if(right_behind_pwm > MAX_MOTOR_PWM)	right_behind_pwm = MOTOR_PWM[3] = MAX_MOTOR_PWM;
	
	
	if(IS_MOTOR_ALL_STOP == 1)	left_front_pwm = left_behind_pwm = right_front_pwm = right_behind_pwm = 0;	//���е��ͣת
	
	TIM8->CCR1 = left_front_pwm;
	TIM8->CCR2 = left_behind_pwm;
	TIM8->CCR4 = right_front_pwm;
	TIM8->CCR3 = right_behind_pwm;
}
