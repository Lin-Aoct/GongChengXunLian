#include "pid.h"


float Balance_Kp = 25.0, Balance_Ki = 0.00, Balance_Kd = 100.0;		//X ��λ�û� PID��ز���

float Y_side_Kp = 20.0, Y_side_Ki = 0.0, Y_side_Kd = 200.0;				//Y ��λ�û� PID��ز���


float LF_Speed_Kp = -115.5, LF_Speed_Ki = 0.1, LF_Speed_Kd = -2.0;					//PID��ز���
float LB_Speed_Kp = -135.5, LB_Speed_Ki = 0.1, LB_Speed_Kd = -2.0;					//PID��ز���
float RF_Speed_Kp = -125.5, RF_Speed_Ki = 0.1, RF_Speed_Kd = -2.0;					//PID��ز���
float RB_Speed_Kp = -125.5, RB_Speed_Ki = 0.1, RB_Speed_Kd = -2.0;					//PID��ز���

float speed_target = 30.0, PID_MAX_VALUE = 150.0;

u8 target = 0;


/*
*===================================================================
*		˵��������PID��ֵ
*		������side		<u8>		������	�Ϸ�ֵ1234
*					part		<u8>		ѡ��Ҫ�༭��PID�Ĳ���
*					action	<u8>		0	��	1	��
*					value		<float>	Ҫ�ı��ֵ��С
*		���أ���
*===================================================================
*/
void Set_PID_Value(u8 side, u8 part, u8 action, float value)
{
	switch(side)	//�жϵ��
	{
		case 1: 
		{
			if(part == 1)	{if(action) LF_Speed_Kp += value; else LF_Speed_Kp -= value;}
			if(part == 2)	{if(action) LF_Speed_Ki += value; else LF_Speed_Ki -= value;}
			if(part == 3)	{if(action) LF_Speed_Kd += value; else LF_Speed_Kd -= value;}
			break;
		}
		case 2: 
		{
			if(part == 1)	{if(action) LB_Speed_Kp += value; else LB_Speed_Kp -= value;}
			if(part == 2)	{if(action) LB_Speed_Ki += value; else LB_Speed_Ki -= value;}
			if(part == 3)	{if(action) LB_Speed_Kd += value; else LB_Speed_Kd -= value;}
			break;
		}
		case 3: 
		{
			if(part == 1)	{if(action) RF_Speed_Kp += value; else RF_Speed_Kp -= value;}
			if(part == 2)	{if(action) RF_Speed_Ki += value; else RF_Speed_Ki -= value;}
			if(part == 3)	{if(action) RF_Speed_Kd += value; else RF_Speed_Kd -= value;}
			break;
		}
		case 4: 
		{
			if(part == 1)	{if(action) RB_Speed_Kp += value; else RB_Speed_Kp -= value;}
			if(part == 2)	{if(action) RB_Speed_Ki += value; else RB_Speed_Ki -= value;}
			if(part == 3)	{if(action) RB_Speed_Kd += value; else RB_Speed_Kd -= value;}
			break;
		}
		default: break;
	}
	printf("[%.0f %.0f %.0f]\t", LF_Speed_Kp, LF_Speed_Ki, LF_Speed_Kd);
	printf("[%.0f %.0f %.0f]\t", LB_Speed_Kp, LB_Speed_Ki, LB_Speed_Kd);
	printf("[%.0f %.0f %.0f]\t", RF_Speed_Kp, RF_Speed_Ki, RF_Speed_Kd);
	printf("[%.0f %.0f %.0f]\n", RB_Speed_Kp, RB_Speed_Ki, RB_Speed_Kd);
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
	
	PID_Limit(&balance);
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
	
	balance = (LB_Speed_Kp * Bias)/10 + LB_Speed_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��

	PID_Limit(&balance);
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
	
	balance = (RF_Speed_Kp * Bias)/10 + RF_Speed_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��

	PID_Limit(&balance);
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
	
	balance = (RB_Speed_Kp * Bias)/10 + RB_Speed_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��

	PID_Limit(&balance);
	return balance;  //����ֵ
}


/**************************************************************************
�������ܣ�PID�޷�
��ڲ�����value	<int>	Ҫ�޷���ֵָ��
����  ֵ����
**************************************************************************/
void PID_Limit(int* value)
{
	if(*value > PID_MAX_VALUE)	*value = PID_MAX_VALUE;
	if(*value < -PID_MAX_VALUE)	*value = -PID_MAX_VALUE;
}



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


