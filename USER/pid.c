#include "pid.h"


float Balance_Kp = 25.0, Balance_Ki = 0.00, Balance_Kd = 100.0;		//X ��λ�û� PID��ز���

float Y_side_Kp = 20.0, Y_side_Ki = 0.0, Y_side_Kd = 200.0;				//Y ��λ�û� PID��ز���

float speed_Kp = -10.0, speed_Ki = 0.0, speed_Kd = 50.0;					//PID��ز���

float Y_speed_Kp = 8.0, Y_speed_Ki = 0.0, Y_speed_Kd = -65.0;					//PID��ز���

u8 target = 0, speed_max = 100;

/**************************************************************************
�������ܣ�X����ƽ��PD����
��ڲ������Ƕ�,
����  ֵ��ֱ������PWM
**************************************************************************/
int balanceX(float Angle)
{
	float Differential, Bias;//�����ֱ�����ƫ��
	static float Last_Bias, Integration, Balance_Integration, Flag_Target;  //��һ�ε�ƫ��ֵ
	int balance;											//����ֵ����

	Bias = Angle - target;  					//���ƽ�����ֵ
	Differential = Bias - Last_Bias;  //���ƫ��ı仯��	 
	if(++Flag_Target > 30) 						//��Ƶ������ֿ���
	{
		Flag_Target = 0;
		Integration += Bias;  // ��⵽С���Ҷ��ʹ�������
		if(Integration<-500) Integration = -500;	//�����޷�
		if(Integration>500)  Integration = 500;	
		Balance_Integration = Integration * Balance_Ki;  //���ֿ���
	}		
	balance = (Balance_Kp * Bias)/100 + Balance_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  	//������һ�ε�ƫ��
	//printf("%0.1f,%0.1f", (Balance_Kp * Bias)/100, Bias);
	return balance;  		//����ֵ
}
/**************************************************************************
�������ܣ�Y����ƽ��PD����
��ڲ������Ƕ�
����  ֵ��ֱ������PWM
**************************************************************************/
int balanceY(float Angle)
{  
	float Differential,Bias;		//�����ֱ�����ƫ��
	static float Last_Bias,Integration,Balance_Integration,Flag_Target;  //��һ�ε�ƫ��ֵ
	int balance;								//����ֵ����

	Bias = Angle - target;  					//���ƽ�����ֵ 
	Differential = Bias - Last_Bias;  //���ƫ��ı仯��	 
	if(++Flag_Target > 30) 						//��Ƶ������ֿ���
	{
		Flag_Target = 0;
		Integration += Bias;  // ����
		if(Integration<-500) Integration = -500;	//�����޷�
		if(Integration>500)  Integration = 500;	
		Balance_Integration = Integration * Y_side_Ki;   //���ֿ���
	}		
	balance = (Y_side_Kp * Bias)/100 + Y_side_Kd*Differential/10 + Balance_Integration;   //������Ƶ�PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��
	return balance;  //����ֵ
}


/**************************************************************************
�������ܣ�X�����ٶȻ�PD����
��ڲ������ٶ�
����  ֵ��ֱ������PWM
**************************************************************************/
int Speed_X(float side)
{
	float Differential, Bias;		//�����ֱ�����ƫ��
	static float Last_Bias, Integration, Balance_Integration, last_side;  //��һ�ε�ƫ��ֵ
	int balance;								//ƽ��ķ���ֵ
	u8 speed_now;
	
	speed_now = side - last_side;
	Bias = speed_now - speed_max;  		//����ٶ�ƫ��

	Differential = Bias - Last_Bias;  //���ƫ��ı仯��	 

	Balance_Integration = Integration * speed_Ki;   //���ֿ���
	
	balance = (speed_Kp * Bias)/100 + speed_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��
	last_side = side;
	//printf("%0.1f,%0.1f", (Balance_Kp * Bias)/100, Bias);
	return balance;  //����ֵ
}

/**************************************************************************
�������ܣ�Y�����ٶȻ�PD����
��ڲ������ٶ�
����  ֵ��ֱ������PWM
**************************************************************************/
int Speed_Y(float side)
{  
	float Differential, Bias;		//�����ֱ�����ƫ��
	static float Last_Bias, Integration, Balance_Integration, last_side;  //��һ�ε�ƫ��ֵ
	int balance;								//ƽ��ķ���ֵ
	u8 speed_now;
	
	speed_now = side - last_side;
	Bias = speed_now - speed_max;  		//���ƽ��ĽǶ���ֵ

	Differential = Bias - Last_Bias;  //���ƫ��ı仯��	 
	
	Balance_Integration = Integration * Y_speed_Ki;   //���ֿ���

	balance = (Y_speed_Kp * Bias)/100 + Y_speed_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��
	last_side = side;
	return balance;  //����ֵ
}
