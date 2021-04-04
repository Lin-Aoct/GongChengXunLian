#include "pid.h"


float Balance_Kp = 25.0, Balance_Ki = 0.00, Balance_Kd = 100.0;		//X ��λ�û� PID��ز���

float Y_side_Kp = 20.0, Y_side_Ki = 0.0, Y_side_Kd = 200.0;				//Y ��λ�û� PID��ز���


float LF_Speed_Kp = -340.5, LF_Speed_Ki = 1.3, LF_Speed_Kd = 0.0;					//PID��ز���
float LB_Speed_Kp = -240.5, LB_Speed_Ki = 0.3, LB_Speed_Kd = 1.0;					//PID��ز���
float RF_Speed_Kp = -240.5, RF_Speed_Ki = 0.3, RF_Speed_Kd = 1.0;					//PID��ز���
float RB_Speed_Kp = -240.5, RB_Speed_Ki = 0.3, RB_Speed_Kd = 1.0;					//PID��ز���

float speed_target = 40.0, speed_max = 600.0;

u8 target = 0;

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
�������ܣ���ǰ�ٶȻ�PD����
��ڲ������ٶ�
����  ֵ������PWM
**************************************************************************/
int PID_Speed_Left_Front(float speed)
{
	float Differential, Bias;		//�����ֱ�����ƫ��
	static float Last_Bias, Integration, Balance_Integration;  //��һ�ε�ƫ��ֵ
	int balance;								//ƽ��ķ���ֵ

	Bias = speed - speed_target;  		//����ٶ�ƫ��

	Differential = Bias - Last_Bias;  //���ƫ��ı仯��	 

	Balance_Integration = Integration * LF_Speed_Ki;   //���ֿ���
	
	balance = (LF_Speed_Kp * Bias)/10 + LF_Speed_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��
	//printf("%d", speed);
	return balance;  //����ֵ
}

/**************************************************************************
�������ܣ�����ٶȻ�PD����
��ڲ������ٶ�
����  ֵ������PWM
**************************************************************************/
int PID_Speed_Left_Behind(float speed)
{
	float Differential, Bias;		//�����ֱ�����ƫ��
	static float Last_Bias, Integration, Balance_Integration;  //��һ�ε�ƫ��ֵ
	int balance;								//ƽ��ķ���ֵ

	Bias = speed - speed_target;  		//����ٶ�ƫ��

	Differential = Bias - Last_Bias;  //���ƫ��ı仯��	 

	Balance_Integration = Integration * LB_Speed_Ki;   //���ֿ���
	
	balance = (LB_Speed_Kp * Bias)/100 + LB_Speed_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��

	return balance;  //����ֵ
}

/**************************************************************************
�������ܣ���ǰ�ٶȻ�PD����
��ڲ������ٶ�
����  ֵ������PWM
**************************************************************************/
int PID_Speed_Right_Front(float speed)
{
	float Differential, Bias;		//�����ֱ�����ƫ��
	static float Last_Bias, Integration, Balance_Integration;  //��һ�ε�ƫ��ֵ
	int balance;								//ƽ��ķ���ֵ

	Bias = speed - speed_target;  		//����ٶ�ƫ��

	Differential = Bias - Last_Bias;  //���ƫ��ı仯��	 

	Balance_Integration = Integration * RF_Speed_Ki;   //���ֿ���
	
	balance = (RF_Speed_Kp * Bias)/100 + RF_Speed_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��

	return balance;  //����ֵ
}

/**************************************************************************
�������ܣ��Һ��ٶȻ�PD����
��ڲ������ٶ�
����  ֵ������PWM
**************************************************************************/
int PID_Speed_Right_Behind(float speed)
{
	float Differential, Bias;		//�����ֱ�����ƫ��
	static float Last_Bias, Integration, Balance_Integration;  //��һ�ε�ƫ��ֵ
	int balance;								//ƽ��ķ���ֵ

	Bias = speed - speed_target;  		//����ٶ�ƫ��

	Differential = Bias - Last_Bias;  //���ƫ��ı仯��	 

	Balance_Integration = Integration * RB_Speed_Ki;   //���ֿ���
	
	balance = (RB_Speed_Kp * Bias)/100 + RB_Speed_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��

	return balance;  //����ֵ
}
