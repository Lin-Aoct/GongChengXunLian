#include "pid.h"


float Balance_Kp = 25.0, Balance_Ki = 0.00, Balance_Kd = 100.0;		//X ��λ�û� PID��ز���

float Y_side_Kp = 20.0, Y_side_Ki = 0.0, Y_side_Kd = 200.0;				//Y ��λ�û� PID��ز���


float LF_Speed_Kp = -230.5, LF_Speed_Ki = -0.37, LF_Speed_Kd = 13.0;					//PID��ز���
//float LB_Speed_Kp = -285.5, LB_Speed_Ki = -0.01, LB_Speed_Kd = 78.0;					//PID��ز���
float LB_Speed_Kp = -285.5, LB_Speed_Ki = -0.32, LB_Speed_Kd = 19.0;					//PID��ز���
float RF_Speed_Kp = -285.5, RF_Speed_Ki = -0.1, RF_Speed_Kd = 19.0;					//PID��ز���
//float RB_Speed_Kp = -230.5, RB_Speed_Ki = 0.0, RB_Speed_Kd = 0.0;					//PID��ز���
float RB_Speed_Kp = -230.5, RB_Speed_Ki = -0.26, RB_Speed_Kd = 19.0;					//PID��ز���

//float LF_Speed_Kp = -200.5, LF_Speed_Ki = 0.2, LF_Speed_Kd = -5.0;					//PID��ز���
//float LB_Speed_Kp = -125.5, LB_Speed_Ki = 0.1, LB_Speed_Kd = -6.0;					//PID��ز���
//float RF_Speed_Kp = -125.5, RF_Speed_Ki = 0.1, RF_Speed_Kd = -2.0;					//PID��ز���
//float RB_Speed_Kp = -195.5, RB_Speed_Ki = 0.1, RB_Speed_Kd = -5.0;					//PID��ز���


float LF_speed_target = 30.0, LF_PID_MAX_VALUE = 150.0;
float LB_speed_target = 30.0, LB_PID_MAX_VALUE = 150.0;
float RF_speed_target = 30.0, RF_PID_MAX_VALUE = 150.0;
float RB_speed_target = 30.0, RB_PID_MAX_VALUE = 150.0;

u8 Expect_Target_Speed_Sta;		//��־Ŀ���ٶ������ı��״̬	bit0~6	->	�ı��Ŀ��ֵ	bit7 -> �ı�״̬

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
	printf("[%0.1f %0.2f %0.1f]\t", LF_Speed_Kp, LF_Speed_Ki, LF_Speed_Kd);
	printf("[%0.1f %0.2f %0.1f]\t", LB_Speed_Kp, LB_Speed_Ki, LB_Speed_Kd);
	printf("[%0.1f %0.2f %0.1f]\t", RF_Speed_Kp, RF_Speed_Ki, RF_Speed_Kd);
	printf("[%0.1f %0.2f %0.1f]\n", RB_Speed_Kp, RB_Speed_Ki, RB_Speed_Kd);
}


/*
*===================================================================
*		˵�����ı���Ŀ���ٶ�ֵ
*		������side		<u8>		������	�Ϸ�ֵ 0 1 2 3 4		0 ����ȫ�����
*					action	<u8>		0	��	1	��
*					value		<u8>		Ҫ�ı��ֵ��С
*		���أ���
*===================================================================
*/
void Change_Speed_Target(u8 side, u8 action, u8 value)
{
	switch(side)
	{
		case 0: 	//���е��
		{
			if(action == 0)
				LF_speed_target -= value, LB_speed_target -= value, RF_speed_target -= value, RB_speed_target -= value;
			else
				LF_speed_target += value, LB_speed_target += value, RF_speed_target += value, RB_speed_target += value;
			break;
		}
		case 1: 	//���1
		{
			if(action == 0)	LF_speed_target -= value;	else	LF_speed_target += value;
			break;
		}
		case 2: 	//���2
		{
			if(action == 0)	LB_speed_target -= value;	else	LB_speed_target += value;
			break;
		}
		case 3: 	//���3
		{
			if(action == 0)	RF_speed_target -= value;	else	RF_speed_target += value;
			break;
		}
		case 4: 	//���4
		{
			if(action == 0)	RB_speed_target -= value;	else	RB_speed_target += value;
			break;
		}
		default: break;
	}
}


/*
*===================================================================
*		˵�������õ��Ŀ���ٶ�ֵ
*		������side		<u8>		������	�Ϸ�ֵ 0 1 2 3 4		0 ����ȫ�����
*					value		<u8>		Ҫ�ı��ֵ
*		���أ���
*===================================================================
*/
void Set_Speed_Target(u8 side, u8 value)
{
	switch(side)
	{
		case 0: LF_speed_target = LB_speed_target = RF_speed_target = RB_speed_target = value; break;
		case 1: LF_speed_target = value; break;
		case 2: LB_speed_target = value; break;
		case 3: RF_speed_target = value; break;
		case 4: RB_speed_target = value; break;
		default: break;
	}
}

/*
*===================================================================
*		˵����������Ŀ���ٶ�ֵ
*		��������
*		���أ���
*===================================================================
*/
void Reset_Target_Speed(void)
{
	if(Expect_Target_Speed_Sta&0x80)	//�ж�Ŀ��Ԥ��ֵ�Ƿ�ı�
	{
		LF_speed_target = Expect_Target_Speed_Sta&0x7F;
		LB_speed_target = Expect_Target_Speed_Sta&0x7F;
		RF_speed_target = Expect_Target_Speed_Sta&0x7F;
		RB_speed_target = Expect_Target_Speed_Sta&0x7F;
	}
	else
	{
		LF_speed_target = 30;
		LB_speed_target = 30;
		RF_speed_target = 30;
		RB_speed_target = 30;
	}
}

/*
*===================================================================
*		˵�������õ��Ŀ���ٶ�����ֵ
*		��������
*		���أ���
*===================================================================
*/
void Set_Expect_Target_Speed(u8 speed)
{
	Expect_Target_Speed_Sta |= 0x80;	//��־����ֵ�ı�
	Expect_Target_Speed_Sta |= speed;	//��־�ٶ�ֵ
	Reset_Target_Speed();
}


/**************************************************************************
�������ܣ���ǰ�ٶȻ�PD����
��ڲ������ٶ�
����  ֵ������PWM
**************************************************************************/
int PID_Speed_Left_Front(float speed)
{
	float Differential, Bias;		//�����ֱ�����ƫ��
	static float Last_Bias, Integration, Balance_Integration, Flag_Target;  //��һ�ε�ƫ��ֵ
	int balance;								//ƽ��ķ���ֵ

	Bias = speed - LF_speed_target;  		//����ٶ�ƫ��

	Differential = Bias - Last_Bias;  //���ƫ��ı仯��	 

//	if(++Flag_Target > 10) 						//��Ƶ������ֿ���
//	{
		Flag_Target = 0;
		Integration += Bias;  // ����
		if(Integration<-50) Integration = -50;	//�����޷�
		if(Integration>50)  Integration = 50;	
		Balance_Integration = Integration * LF_Speed_Ki;   //���ֿ���
//	}
	
	balance = (LF_Speed_Kp * Bias)/10 + LF_Speed_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��
	
	PID_Limit(1, &balance);
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
	static float Last_Bias, Integration, Balance_Integration, Flag_Target;  //��һ�ε�ƫ��ֵ
	int balance;								//ƽ��ķ���ֵ

	Bias = speed - LB_speed_target;  		//����ٶ�ƫ��

	Differential = Bias - Last_Bias;  //���ƫ��ı仯��	 

//	if(++Flag_Target > 10) 						//��Ƶ������ֿ���
//	{
		Flag_Target = 0;
		Integration += Bias;  // ����
		if(Integration<-50) Integration = -50;	//�����޷�
		if(Integration>50)  Integration = 50;	
		Balance_Integration = Integration * LB_Speed_Ki;   //���ֿ���
	//}
	
	balance = (LB_Speed_Kp * Bias)/10 + LB_Speed_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��

	PID_Limit(2, &balance);
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
	static float Last_Bias, Integration, Balance_Integration, Flag_Target;  //��һ�ε�ƫ��ֵ
	int balance;								//ƽ��ķ���ֵ

	Bias = speed - RF_speed_target;  		//����ٶ�ƫ��

	Differential = Bias - Last_Bias;  //���ƫ��ı仯��	 

//	if(++Flag_Target > 10) 						//��Ƶ������ֿ���
//	{
		Flag_Target = 0;
		Integration += Bias;  // ����
		if(Integration<-50) Integration = -50;	//�����޷�
		if(Integration>50)  Integration = 50;	
		Balance_Integration = Integration * RF_Speed_Ki;   //���ֿ���
	//}
	
	balance = (RF_Speed_Kp * Bias)/10 + RF_Speed_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��

	PID_Limit(3, &balance);
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
	static float Last_Bias, Integration, Balance_Integration, Flag_Target;  //��һ�ε�ƫ��ֵ
	int balance;								//ƽ��ķ���ֵ

	Bias = speed - RB_speed_target;  		//����ٶ�ƫ��

	Differential = Bias - Last_Bias;  //���ƫ��ı仯��	 

//	if(++Flag_Target > 10) 						//��Ƶ������ֿ���
//	{
		Flag_Target = 0;
		Integration += Bias;  // ����
		if(Integration<-50) Integration = -50;	//�����޷�
		if(Integration>50)  Integration = 50;	
		Balance_Integration = Integration * RB_Speed_Ki;   //���ֿ���
//	}
	
	balance = (RB_Speed_Kp * Bias)/10 + RB_Speed_Kd*Differential/10 + Balance_Integration;   //�������PWM  PD����
	Last_Bias = Bias;  //������һ�ε�ƫ��

	PID_Limit(4, &balance);
	return balance;  //����ֵ
}


/**************************************************************************
�������ܣ�PID�޷�
��ڲ�����side	<u8>	�޷��ĵ�����
					value	<int>	Ҫ�޷���ֵָ��
����  ֵ����
**************************************************************************/
void PID_Limit(u8 side, int* value)
{
	switch(side)
	{
		case 1:
		{
			if(*value > LF_PID_MAX_VALUE)	*value = LF_PID_MAX_VALUE;
			if(*value < -LF_PID_MAX_VALUE)	*value = -LF_PID_MAX_VALUE;
			break;
		}
		case 2:
		{
			if(*value > LB_PID_MAX_VALUE)	*value = LB_PID_MAX_VALUE;
			if(*value < -LB_PID_MAX_VALUE)	*value = -LB_PID_MAX_VALUE;
			break;
		}
		case 3:
		{
			if(*value > RF_PID_MAX_VALUE)	*value = RF_PID_MAX_VALUE;
			if(*value < -RF_PID_MAX_VALUE)	*value = -RF_PID_MAX_VALUE;
			break;
		}
		case 4:
		{
			if(*value > RB_PID_MAX_VALUE)	*value = RB_PID_MAX_VALUE;
			if(*value < -RB_PID_MAX_VALUE)	*value = -RB_PID_MAX_VALUE;
			break;
		}
		default: break;
	}

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


