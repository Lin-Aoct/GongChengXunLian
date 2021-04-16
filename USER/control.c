#include "control.h"	

u8 CAR_MODE = 0;						//��־С��ģʽ
u8 step = 0, count = 10;		//��־ִ�в����Լ���ʱ����
u16 front_data, right_data, behind_data, left_data;	//ǰ �� �� �� ����ѭ��ģ���������
u8 is_stop_mode = 0;				//��־�Ƿ�Ϊͣ��ģʽ ����PIDͣ��
u8 is_car_debug_mode = 0;		//С�� debug ģʽ��־ ��Ϊ1�򵽵��ִ�л�е�۶���

/*
*===================================================================
*		˵������ʱ��6�жϷ����� 15ms ִ��һ��
*		��������
*		���أ���
*===================================================================
*/
void TIM6_DAC_IRQHandler(void)
{    
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)	//���ָ����TIM�жϷ������
	{
		switch(CAR_MODE)
		{
			case 0: break;
			case 1: Mode_Start(); break;									//����
			case 2: Mode_Go_Area1(); break;								//��ά�� 			-> 	���϶ѷ���
			case 3: Mode_Area1_To_Area2(1); break;				//���϶ѷ���	->	�ּӹ���	����ģʽ
			case 4: Mode_Area2_To_Area3_Top(); break;			//�ּӹ���		->	���Ʒ��	����ģʽ
			case 5: Mode_Area3_To_Area1(); break;					//���Ʒ��		->	ԭ����
			case 6: Mode_Go_One_Aera1(1); break;					//����1����ǰ��һ��
			case 7: Mode_Back_One_Area1(1); break;				//����1��������һ��
			case 8: Mode_Go_One_Aera1(2); break;					//����2����ǰ��һ��
			case 9: Mode_Back_One_Area1(2); break;				//����2��������һ��
			case 10: Mode_Go_One_Aera1(3); break;					//����3����ǰ��һ��
			case 11: Mode_Area1_To_Area2(2); break;				//���϶ѷ���	->	�ּӹ���	�²�ģʽ
			case 12: Mode_Area2_To_Area3_Bottom(); break;	//�ּӹ���		->	���Ʒ��	�²�ģʽ
			case 13: Mode_Area3_Back(); break;						//���Ʒ��		->	������
			
			case 20: Mode_PID_Test(1); break;
			case 21: Mode_PID_Test(2); break;
			case 22: Mode_PID_Test(3); break;
			case 23: Mode_PID_Test(4); break;
			case 24: Mode_PID_Test(5); break;
			case 25: Mode_PID_Test(6); break;
			case 26: Mode_PID_Test(7); break;
			case 27: Mode_PID_Test(8); break;
			case 28: Mode_PID_Test(9); break;
			case 29: Mode_PID_Test(10); break;

			case 41: Cross_Road_Fix(1); break;		
			case 42: Cross_Road_Fix(2); break;		

			default: break;
		}
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);			//���TIM6���жϴ�����λ
   }       	
}

/*
*===================================================================
*		˵����·�ڶ���ģʽ����
*		��������
*		���أ���
*===================================================================
*/
void Cross_Road_Fix(u8 mode)
{
	static u8 fix_counter;				//��������
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	behind_data = Find_Get_Behind();
	left_data = Find_Get_Left();
	
	Set_Expect_Target_Speed(6);	//����
	if(mode == 0)
	{
		if(front_data == 1001 && right_data == 1001 && behind_data == 1001 && left_data == 1001) printf("[ͣ��]"), Car_Stop(), Stop_Find(); //CAR_MODE = 0;	//����
		else if((front_data == 1110 || front_data == 1100) &&
						(right_data == 1110 || right_data == 1100) &&
						(behind_data == 1110 || behind_data == 1100) &&
						(left_data == 1110 || left_data == 1100)) printf("[Yaw����]"), Car_Yaw_Right();	//Yaw����
		else if((front_data == 111 || front_data == 11) &&
						(right_data == 111 || right_data == 11) &&
						(behind_data == 111 || behind_data == 11) &&
						(left_data == 111 || left_data == 11)) printf("[Yaw����]"), Car_Yaw_Right();		//Yaw����
	}

	if(mode == 1)	//�������ϲ㶨��
	{
		if(left_data == 1001 && right_data == 0)
			Car_Stop(), Stop_Find(), fix_counter = 0, CAR_MODE=0;	//λ�ú��� ͣ��
		else if(right_data == 0)
		{
			if(left_data == 111 || left_data == 1011 || left_data == 11) Car_Back();				//����
			else if(left_data == 1110 || left_data == 1101 || left_data == 1100) Car_Go();	//ǰ��
			else if(left_data == 1111 && fix_counter == 0) Car_Back(), fix_counter = 22;		//��������� ǰ��һ�� �ȴ� ((22-2)*15) 300ms ���������ٽ����۷�
			else if(left_data == 1111 && fix_counter-- == 1) Car_Go();												//ɨ������ʱ����۷�
		}
		else if(right_data == 11 || right_data == 1) Car_Yaw_Left();		//Yaw����
		else if(right_data == 1100 || right_data == 1000) Car_Yaw_Right();	//Yaw����
//		else if((right_data == 1110 || right_data == 1100) &&
//						(left_data == 1110 || left_data == 11)) Car_Yaw_Right();	//Yaw����
//		else if((right_data == 111 || right_data == 11) &&
//						(left_data == 111 || left_data == 11)) Car_Yaw_Right();		//Yaw����
	}
	
	if(mode == 2)	//�ּӹ�������
	{
		if(behind_data == 1001 && front_data == 0)
			Car_Stop(), Stop_Find(), fix_counter = 0, CAR_MODE=0;	//λ�ú��� ͣ��
		else if(front_data == 0)
		{
			if(behind_data == 111 || behind_data == 1011 || behind_data == 11) Car_Go_Right();				//����
			else if(behind_data == 1110 || behind_data == 1101 || behind_data == 1100) Car_Go_Left();	//ǰ��
			else if(behind_data == 1111 && fix_counter == 0) Car_Go_Right(), fix_counter = 22;				//��������� ǰ��һ�� �ȴ� ((22-2)*15) 300ms ���������ٽ����۷�
			else if(behind_data == 1111 && fix_counter-- == 1) Car_Go_Left();													//ɨ������ʱ����۷�
		}
		else if(front_data == 11 || front_data == 1) Car_Yaw_Left();				//Yaw����
		else if(front_data == 1100 || front_data == 1000) Car_Yaw_Right();	//Yaw����

		else if((front_data == 1110 || front_data == 1100) &&
						(behind_data == 1110 || behind_data == 11)) Car_Yaw_Right();	//Yaw����
		else if((front_data == 111 || front_data == 11) &&
						(behind_data == 111 || behind_data == 11)) Car_Yaw_Right();		//Yaw����
	}
	
	Set_PID_PWM();

}

/*
*===================================================================
*		˵����PID����ģʽ����
*		��������
*		���أ���
*===================================================================
*/
void Mode_PID_Test(u8 mode)
{
	switch(mode)
	{
		case 1: Car_Go(); FIND_DRIVER=0, CURRENT_DIRATION=1; Find(); break;
		case 2: Car_Back(); FIND_DRIVER=2, CURRENT_DIRATION=2; Find(); break;
		case 3: Car_Go_Left(); FIND_DRIVER=3, CURRENT_DIRATION=3; Find(); break;
		case 4: Car_Go_Right(); FIND_DRIVER=1, CURRENT_DIRATION=4; Find(); break;
		case 5: Set_MOTOR_Left_Front(GO); Set_MOTOR_Left_Behind(STOP); Set_MOTOR_Right_Front(STOP); Set_MOTOR_Right_Behind(STOP); break;
		case 6: Set_MOTOR_Left_Front(STOP); Set_MOTOR_Left_Behind(GO); Set_MOTOR_Right_Front(STOP); Set_MOTOR_Right_Behind(STOP); break;
		case 7: Set_MOTOR_Left_Front(STOP); Set_MOTOR_Left_Behind(STOP); Set_MOTOR_Right_Front(GO); Set_MOTOR_Right_Behind(STOP); break;
		case 8: Set_MOTOR_Left_Front(STOP); Set_MOTOR_Left_Behind(STOP); Set_MOTOR_Right_Front(STOP); Set_MOTOR_Right_Behind(GO); break;
		case 9: Car_Go(); is_stop_mode = 0; Set_Expect_Target_Speed(30); break;
		case 10: Car_Back(); is_stop_mode = 1; Set_Expect_Target_Speed(0); break;
		default: break;
	}
	Set_PID_PWM();
}

/*
*===================================================================
*		˵����PID���Ƶ�����PWM ��ʱ���ñ�����
*		��������
*		���أ���
*===================================================================
*/
void Set_PID_PWM(void)
{
	ENCODER_DATA[0] = abs(Read_Encoder(2));
	ENCODER_DATA[1] = abs(Read_Encoder(3));
	ENCODER_DATA[2] = abs(Read_Encoder(4));
	ENCODER_DATA[3] = abs(Read_Encoder(5));
	
	if(IS_MOTOR_ALL_STOP == 0)	//�ж��Ƿ�����
	{
		if(is_stop_mode == 1)//�ж��Ƿ�Ϊͣ��ģʽ
		{
			printf("ͣ��ģʽ");
			TIM8->CCR1 = -PID_Speed_Left_Front(ENCODER_DATA[0]);
			TIM8->CCR2 = -PID_Speed_Left_Behind(ENCODER_DATA[1]);
			TIM8->CCR4 = -PID_Speed_Right_Front(ENCODER_DATA[2]);
			TIM8->CCR3 = -PID_Speed_Right_Behind(ENCODER_DATA[3]);
		}
		else
		{
			TIM8->CCR1 = MOTOR_PWM[0] + PID_Speed_Left_Front(ENCODER_DATA[0]);
			TIM8->CCR2 = MOTOR_PWM[1]	+ PID_Speed_Left_Behind(ENCODER_DATA[1]);
			TIM8->CCR4 = MOTOR_PWM[2] + PID_Speed_Right_Front(ENCODER_DATA[2]);
			TIM8->CCR3 = MOTOR_PWM[3] + PID_Speed_Right_Behind(ENCODER_DATA[3]);
		}
		ENCODER_DATA[5] = TIM8->CCR3 -100;
	}
	
//	printf("%x%x%x%d%x", 0xFF, 0XF0, 0X0F, ENCODER_DATA[0], 0x00);
//	printf("%x%x%x%d%x", 0xFF, 0XF1, 0X0E, ENCODER_DATA[1], 0x00);
//	printf("%x%x%x%d%x", 0xFF, 0XF2, 0X0D, ENCODER_DATA[2], 0x00);
//	printf("%x%x%x%d%x", 0xFF, 0XF3, 0X0C, ENCODER_DATA[3], 0x00);
	
	if(is_car_debug_mode)
	{
		printf("������[%d %d %d %d]\t", ENCODER_DATA[0], ENCODER_DATA[1], ENCODER_DATA[2], ENCODER_DATA[3]);
		printf("PWM[%d %d %d %d]\t", TIM8->CCR1, TIM8->CCR2, TIM8->CCR4, TIM8->CCR3);
		printf("TS[%.0f %.0f %.0f %.0f]\t", LF_speed_target, LB_speed_target, RF_speed_target, RB_speed_target);	//��ӡĿ���ٶ�
		printf("H[%d | %d]\tstep[%d]\n", front_data, right_data, step);	//��ӡ������Ϣ
	}
}

/*
*===================================================================
*		˵��������ģʽ��ǰ����ά��ɨ������
*		��������
*		���أ���
*===================================================================
*/
void Mode_Start(void)
{
	static u8 y_line_step;		//����ģʽ��y�߲������  ����б��ʱ����
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	
		Set_Expect_Target_Speed(35), Car_Left_Front(), step++, count = 35;		//����ƽ��	���� 
	
	if(count > 0 && step == 1)	count--;	//��ʱ510ms
	
	if(front_data == 1001 && step == 1 && count == 0)
		Car_Go(), Set_Expect_Target_Speed(30), FIND_MODE=0, FIND_DRIVER = 0, CURRENT_DIRATION = 1, step++;	//ǰ�洦������
	Find();
	
	if(right_data == 1001 && y_line_step == 0)	y_line_step++;	//Y��1 �м�
	
	if(right_data == 1110 && y_line_step == 1)	y_line_step++;	//����1
	
	if(right_data == 1001 && y_line_step == 2)	y_line_step++;	//��2�м�
	
	if(right_data == 1110 && y_line_step == 3)	count = 3, y_line_step++, step++;	//����2
		
	if(count > 0 && step == 3)	count--;						//3*15ms = 45ms

	if(count == 0 && step == 3)	
	{
		Car_Stop();				//�˳�����ģʽ
		Stop_Find();			//ֹͣѲ��
		CAR_MODE = 0;
		y_line_step = 0;
		if(!is_car_debug_mode)
			ARM_Action = 1;		//��е��ɨ��
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		˵������ά��ɨ����Ϻ� ǰ�����϶ѷ�����
*		��������
*		���أ���
*===================================================================
*/
void Mode_Go_Area1(void)
{
	static u8 y_line_step;		//����ģʽ��y�߲������  ����б��ʱ����
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	left_data = Find_Get_Left();

	
//	if(step == 0)	Set_Expect_Target_Speed(30), Car_Left_Front(), step++;	//�����Ͻ�

//	if((left_data == 1001 || left_data == 0) && step == 1) y_line_step=1, step++;	//�������
//	
//	if(front_data == 1001 && step == 2)
//		Car_Go(), Set_Expect_Target_Speed(40), FIND_MODE=0, FIND_DRIVER = 0, CURRENT_DIRATION = 1, step++;	//ǰ�洦������

//	Find();
//	if(right_data == 1001 && step == 3)	step++;	//Y��2 �м�
//	if(right_data == 1110 && step == 4)	step++;	//�� Y��2
//	
//	if(right_data == 1001 && step == 5)	step++;	//Y��3 �м�
//	if(right_data == 1110 && step == 6)	
//		step++, Set_Expect_Target_Speed(15);			//��Y��3 ���� ׼��ת��
//	
//	if((right_data == 1001 || right_data == 11) && step == 7)
//		Set_Expect_Target_Speed(7), Car_Go_Right(), FIND_DRIVER = 3, CURRENT_DIRATION = 3, step++;	//������4 ��ƽ��

//	Set_PID_PWM();

//	if(right_data == 0 && step == 8)	
//	{
//		step++;
//		Car_Stop();
//		Stop_Find();
//		y_line_step = 0;
//		Expect_Target_Speed_Sta = 0;
//		Reset_Target_Speed();					//�ָ��ٶ�
//		//CAR_MODE = 0;								//��������ץȡλ��
//		CAR_MODE = 41;								//��������ץȡλ�� ��ʼ����
//		if(!is_car_debug_mode)
//			ARM_Action = 2;							//��е��ɨ���ϲ�
//	}
//	
	
	
	
	
	
	
	
	
	
	
	if(step == 0)	Set_Expect_Target_Speed(40), Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, step = 1;	//ǰ�洦������
	
	Find();
	
	if(right_data == 1001 && step == 1)	step++;	//��1�м�
	if(right_data == 1110 && step == 2)	step++;	//����1
	
	if(right_data == 1001 && step == 3)	step++;	//��2�м�
	if(right_data == 1110 && step == 4)	step++;	//����2
	
	if(right_data == 1001 && step == 5)	step++;	//��3�м�
	if(right_data == 1110 && step == 6)	
		step++, Set_Expect_Target_Speed(15);			//����3 ���� ׼��ת��
	
	if((right_data == 1001 || right_data == 11) && step == 7)
		Set_Expect_Target_Speed(7), Car_Go_Left(), FIND_DRIVER = 3, CURRENT_DIRATION = 3, step++;	//������4 ��ƽ��

	Set_PID_PWM();

	if(right_data == 0 && step == 8)	
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();					//�ָ��ٶ�
		//CAR_MODE = 0;								//��������ץȡλ��
		CAR_MODE = 41;								//��������ץȡλ�� ��ʼ����
		if(!is_car_debug_mode)
			ARM_Action = 2;							//��е��ɨ���ϲ�
	}
}

/*
*===================================================================
*		˵�������϶ѷ�����ǰ���ּӹ���
*		������mode	<u8>	
*		���أ���
*===================================================================
*/
void Mode_Area1_To_Area2(u8 mode)
{
	static u8 down_temp, dis_temp;
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)
		Set_Expect_Target_Speed(25), Find_Target_Speed = 25, Car_Go_Left(), FIND_DRIVER = 3, CURRENT_DIRATION = 3, step++;	//��ƽ��	Y��ѭ��
	Find();
	
	if(front_data == 1001 && step == 1)
		step++, Expect_Target_Speed_Sta = 0, Reset_Target_Speed();	//X��1 �м� �ָ��ٶ�
	if(front_data == 1110 && step == 2)	step++;	//����1
	
	if(front_data == 1001 && step == 3)	step++;	//X��2 �м�
	if(front_data == 1110 && step == 4) step++;	//�� X��2 ����Ѳ���ٶ� 
	
//	if(front_data == 1001 && step == 5)						//X��3 �м�
//		down_temp = 20, dis_temp=2, Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, FIND_MODE = 1, step++;	//������3 ���� ��ǰ�˶� X��Ѳ��

//	if(step == 6)	{dis_temp--;if(dis_temp==0){Set_Expect_Target_Speed(down_temp--);dis_temp=2; if(down_temp == 6) step++;}}

	if(front_data == 1001 && step == 5)						//X��3 �м�
		Set_Expect_Target_Speed(10), Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, FIND_MODE = 0, step++;	//������3 ���� ��ǰ�˶� X��Ѳ��
	
	if(front_data == 0000 && step == 6)
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();					//�ָ��ٶ�
		Find_Target_Speed = 35;	//Ѳ���ٶȻָ�
		down_temp = 0;
		dis_temp = 0;
		CAR_MODE = 42;									//�ּӹ�������
		//CAR_MODE = 0;									//��������ץȡλ�� ��ʼ����
		if(!is_car_debug_mode)
		{
			if(mode)
				ARM_Action = 4;
			else
				ARM_Action = 14;
		}
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		˵�����ּӹ���ǰ�����Ʒ����	����ģʽ
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area2_To_Area3_Top(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	left_data = Find_Get_Left();
	
	if(step == 0)	Set_Expect_Target_Speed(35), Car_Back(), FIND_DRIVER = 2, CURRENT_DIRATION = 2, FIND_MODE = 1, step++;	//����	X�Ḻ����ѭ��
	
	Find();
	
	if(right_data == 1001 && step == 1)	step++;		//Y��1 �м�
	if(right_data == 1110 && step == 2)	step++;		//��Y��1
	
	if(right_data == 1001 && step == 3)	step++;		//Y��2 �м�
	if(right_data == 1110 && step == 4)	step++;		//��Y��2
	
	if((right_data == 1110 || right_data == 1001)&& step == 5)
		Set_Expect_Target_Speed(25), Car_Go_Left(), FIND_MODE = 1, FIND_DRIVER = 3, CURRENT_DIRATION = 3, count = 35, step++;	//Y��3 �м�	���� Y��������Ѳ��

	if(count > 0 && step == 6)	count--;					//��ʱ 34*15ms = 510ms
	if(count == 0 && step == 6) step++;
	
	if(front_data == 1001 && step == 7)	step++;		//X��1 �м�
	if(front_data == 1110 && step == 8)	step++;		//��X��1
	
	if(front_data == 1001 && step == 9)	step++;		//X��2 �м�
	if(front_data == 1110 && step == 10) step++, Set_Expect_Target_Speed(15);	//��X��2
	
	if(left_data == 0 && step == 11)					//X��3 �м� ͣ��
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();					//�ָ��ٶ�
		CAR_MODE = 0;
		if(!is_car_debug_mode)
			ARM_Action = 5;		//��е�۶���ڶ��η���
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		˵�������Ʒ��ǰ��ԭ����
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area3_To_Area1(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)
		Car_Go_Right(), FIND_DRIVER = 1, CURRENT_DIRATION = 4, step = 1;	//���� Y��ѭ��
	Find();
	
	if(front_data == 1001 && step == 1)	step++;		//X��1 �м�
	if(front_data == 1110 && step == 2)	step++;		//�� X��1
	
	if(front_data == 1001 && step == 3)	step++;		//X��2 �м�
	if(front_data == 1110 && step == 4)	step++;		//�� X��2
	
	if(front_data == 1001 && step == 5)	step++;		//X��3 �м�
	if(front_data == 1110 && step == 6)	step++;		//�� X��3
	
	if(front_data == 1001 && step == 7)	step++;		//X��4 �м�
	if(front_data == 1110 && step == 8)	Set_Expect_Target_Speed(25), step++;		//�� X��4

	if(front_data == 1001 && step == 9)	
		Car_Go(), FIND_MODE=0, FIND_DRIVER = 0, CURRENT_DIRATION = 1, Expect_Target_Speed_Sta=0, Reset_Target_Speed(), step++, count+=11;	//X��5�м�	ǰ��	X��Ѳ��

	if(count > 0 && step == 10)	count--;					//��ʱ 10*15ms = 150ms
	if(count == 0 && step == 10) step++;
	
	if(right_data == 1001 && step == 11)	step++;	//Y��1 �м�
	if(right_data == 1110 && step == 12)	step++, Set_Expect_Target_Speed(12);	//�� Y��1
	
	if(right_data == 1001 && step == 13)
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta=0;
		Reset_Target_Speed();
		CAR_MODE = 0;
		if(!is_car_debug_mode)
			ARM_Action = 6;		//Y��2 �м�	ԭ���� ��е��ʶ����ɫ ׼��ץȡ����
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		˵����ԭ��������ǰһ�� ץȡ�м�����
*		������step	<u8>	�ڼ�����ǰ��
*		���أ���
*===================================================================
*/
void Mode_Go_One_Aera1(u8 current_step)
{
	if(way2[current_step-1] == '2')							//�ж��Ƿ�ץȡ�м�
	{
		left_data = Find_Get_Left();
		if(step == 0)
			Set_Expect_Target_Speed(15), Car_Go_Right(), FIND_DRIVER = 1, CURRENT_DIRATION = 4, step++;	//��ƽ�� Y�Ḻ����ѭ��
		Find();
		if(left_data == 0 && step == 1) count=16, step++;
		if(count > 0 && step == 2) count--;
		if(count == 0 && step == 2) step++;
		
		if(step == 3)	
		{
			step++;
			Car_Stop();
			Stop_Find();
			Mode_Init();
			Expect_Target_Speed_Sta = 0;
			Reset_Target_Speed();						//�ָ��ٶ�
			CAR_MODE = 0;										//��������ץȡλ�� �˳�ģʽ
			if(!is_car_debug_mode)
			{
				if(current_step==1)
					ARM_Action = 8;							//��е���²��һ��ץȡ����
				else if(current_step==2)
					ARM_Action = 10;						//��е���²�ڶ���ץȡ����
				else if(current_step==3)
					ARM_Action = 12;						//��е���²������ץȡ����
			}
		}
	}
	else
	{
		right_data = Find_Get_Right();
		if(step == 0)
			Set_Expect_Target_Speed(15), Car_Go_Right(), FIND_DRIVER = 1, CURRENT_DIRATION = 4, step++;	//��ƽ�� Y�Ḻ����ѭ��
		Find();
		
		//if(right_data == 0 && step == 1)	
		
		if(right_data == 0 && step == 1) count=3, step++;
		
		if(count > 0 && step == 2) count--;
		if(count == 0 && step == 2) step++;		//3*15 30ms
		
		if(step == 3)
		{
			step++;
			Car_Stop();
			Stop_Find();
			Mode_Init();
			Expect_Target_Speed_Sta = 0;
			Reset_Target_Speed();						//�ָ��ٶ�
			CAR_MODE = 0;										//��������ץȡλ�� �˳�ģʽ
			if(!is_car_debug_mode)					//�ж��Ƿ�Ϊ�� DEBUG ģʽ
			{
				if(current_step==1)
					ARM_Action = 8;							//��е���²��һ��ץȡ����
				else if(current_step==2)
					ARM_Action = 10;						//��е���²�ڶ���ץȡ����
				else if(current_step==3)
					ARM_Action = 12;						//��е���²������ץȡ����
			}
		}
	}

	Set_PID_PWM();
}


/*
*===================================================================
*		˵����ԭ����������һ��
*		������step	<u8>	�ڼ��κ���
*		���أ���
*===================================================================
*/
void Mode_Back_One_Area1(u8 current_step)
{
	front_data = Find_Get_Front();
	
	if(step == 0)
		Set_Expect_Target_Speed(15), Car_Go_Left(), FIND_DRIVER = 3, CURRENT_DIRATION = 3, step++;	//��ƽ�� Y��������ѭ��

	Find();
	
	if((front_data == 1001 || front_data == 11) && step == 1)	
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();						//�ָ��ٶ�
		CAR_MODE = 0;										//��������ץȡλ�� �˳�ģʽ
		if(!is_car_debug_mode)
		{
			if(current_step==1)
				ARM_Action = 9;							//��е�۴�� �²��һ��ץȡ����
			else if(current_step==2)
				ARM_Action = 11;						//��е�۴�� �²�ڶ���ץȡ����
//			else if(step==3)
//				ARM_Action = 13;						//��е�۴�� �²������ץȡ����
		}
	}
	
	Set_PID_PWM();
}



/*
*===================================================================
*		˵����ԭ��������ǰһ��
*		��������
*		���أ���
*===================================================================
*/
void Mode_Go_One_Step(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)
		Set_Expect_Target_Speed(15), Car_Go_Right(), FIND_DRIVER = 1, CURRENT_DIRATION = 4, step++;	//��ƽ�� Y�Ḻ����ѭ��

	Find();
	
	if(right_data == 0 && step == 1)	
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();						//�ָ��ٶ�
		CAR_MODE = 0;										//��������ץȡλ�� �˳�ģʽ
		if(!is_car_debug_mode)
			ARM_Action = 8;								//��е��ץȡ����
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		˵����ԭ����������һ��
*		��������
*		���أ���
*===================================================================
*/
void Mode_Back_One_Step(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)
		Set_Expect_Target_Speed(15), Car_Go_Left(), FIND_DRIVER = 3, CURRENT_DIRATION = 3, step++;	//��ƽ�� Y��������ѭ��

	Find();
	
	if((front_data == 1001 || front_data == 11) && step == 1)	
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();						//�ָ��ٶ�
		CAR_MODE = 0;			//��������ץȡλ�� �˳�ģʽ
		if(!is_car_debug_mode)
			ARM_Action = 9;		//��е��ץȡ����
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		˵�����ּӹ���ǰ�����Ʒ����	�ײ�ģʽ
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area2_To_Area3_Bottom(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	left_data = Find_Get_Left();
	
	if(step == 0)	Set_Expect_Target_Speed(35), Car_Back(), FIND_DRIVER = 2, CURRENT_DIRATION = 2, FIND_MODE = 1, step++;	//����	X�Ḻ����ѭ��
	
	Find();
	
	if(right_data == 1001 && step == 1)	step++;		//Y��1 �м�
	if(right_data == 1110 && step == 2)	step++;		//��Y��1
	
	if(right_data == 1001 && step == 3)	step++;		//Y��2 �м�
	if(right_data == 1110 && step == 4)	step++;		//��Y��2
	
	if((right_data == 1110 || right_data == 1001)&& step == 5)
		Set_Expect_Target_Speed(25), Car_Go_Left(), FIND_MODE = 1, FIND_DRIVER = 3, CURRENT_DIRATION = 3, count = 35, step++;	//Y��3 �м�	���� Y��������Ѳ��

	if(count > 0 && step == 6)	count--;					//��ʱ 34*15ms = 510ms
	if(count == 0 && step == 6) step++;
	
	if(front_data == 1001 && step == 7)	step++;		//X��1 �м�
	if(front_data == 1110 && step == 8)	step++, Set_Expect_Target_Speed(15);		//��X��1
	
	if((front_data == 1001 || front_data == 111) && step == 9)	step++, Set_Expect_Target_Speed(7);		//X��2 �м�

	if(front_data == 1110 && step == 10)					//X��2 �ϲ� ͣ��
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();					//�ָ��ٶ�
		CAR_MODE = 0;
		if(!is_car_debug_mode)
			ARM_Action = 15;						//��е�۵ײ���Ʒ������
	}
	
	Set_PID_PWM();
}


/*
*===================================================================
*		˵�������Ʒ������
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area3_Back(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Set_Expect_Target_Speed(35), Car_Back(), FIND_DRIVER=2, CURRENT_DIRATION=2, FIND_MODE=0, count=31, step++;	//���� X�Ḻ����ѭ��
	Find();
	
	if(count>0 && step == 1) count--;
	if(count == 0 && step == 1)step++;						//��ʱ 30*15 450ms
	
	if(right_data == 1001 && step == 2)	step++;		//Y��1 �м�
	if(right_data == 1110 && step == 3)	step++;		//�� Y��1
	
	if(right_data == 1001 && step == 4)	step++;		//Y��2 �м�
	if(right_data == 1110 && step == 5)	step++;		//�� Y��2

	if(right_data == 1001 && step == 6)	Car_Go_Left(), FIND_DRIVER=3, CURRENT_DIRATION=3, count=31, step++;	//Y��3�м� ���� Y��������Ѳ��

	if(count>0 && step == 7) count--;
	if(count == 0 && step == 7)step++;						//��ʱ 30*15 450ms
	
	if(front_data == 1001 && step == 8)	step++;		//X��1 �м�
	if(front_data == 1110 && step == 9)	step++;		//�� X��1
	
	if(right_data == 0 && step == 10)	Stop_Find(), Car_Back(), Set_Expect_Target_Speed(10), step++;	//��X��2
	
	if(front_data == 0 && step == 11)	Car_Stop(), Stop_Find(), CAR_MODE = 0, step++;	//ǰ��������غ� ͣ�� ���ﷵ����
	
	Set_PID_PWM();
}

void Mode_Init(void)
{
	step = 0;
	count = 10;
}




/********************��е�۲��ֿ���************************/


//ץ����
void top_grasp_choose(u8* ptr)
{
	int i;
	for( i= 0;i<3;i++)
	{
		switch(ptr[i])
		{
			case '1':{top_grasp1();place_playload1(); break;}
			case '2':{top_grasp2();place_playload2(); break;}
			case '3':{top_grasp3();place_playload3();break;}	  
			default: break;		
	  }
}
}

//�ϲ�ץȡ
void top_grasp_choose1(u8*ptr)
{
  if(ptr[0]=='1')
		top_grasp1();
	else if(ptr[0]=='2')
     top_grasp2();
	else if(ptr[0]=='3')
			top_grasp3();
	place_playload1();
}
	

void top_grasp_choose2(u8*ptr)
{
	if(ptr[1]=='1')
		top_grasp1();
	else if(ptr[1]=='2')
     top_grasp2();
	else if(ptr[1]=='3')
			top_grasp3();
	place_playload2();

}

void top_grasp_choose3(u8*ptr)
{
	if(ptr[2]=='1')
		top_grasp1();
	else if(ptr[2]=='2')
     top_grasp2();
	else if(ptr[2]=='3')
			top_grasp3();
	place_playload3();

}

//�²�ץȡ
void  under_grasp_choose1(u8 *ptr)
{
	//printf("1%c\n", ptr[0]);
	if(ptr[0]=='1')
		under_grasp1();
	else if(ptr[0]=='2')
     under_grasp2();
	else if(ptr[0]=='3')
			under_grasp3(), printf("ץ��ɫ");
//	place_playload1();

}

void  under_grasp_choose2(u8 *ptr)
{
		//printf("2%c\n", ptr[1]);

	
	if(ptr[1]=='1')
		under_grasp1();
	else if(ptr[1]=='2')
     under_grasp2(), printf("ץ��ɫ");
	else if(ptr[1]=='3')
			under_grasp3();
//	place_playload2();

}

void  under_grasp_choose3(u8 *ptr)
{
		//printf("3%c\n", ptr[2]);

	if(ptr[2]=='1')
		under_grasp1(), printf("ץ��ɫ");
	else if(ptr[2]=='2')
     under_grasp2();
	else if(ptr[2]=='3')
			under_grasp3();
//	place_playload3();

}

void under_grasp_all(u8 * ptr)
{
	int i = 5;
	for(;i<8;i++)
	{
		switch(ptr[i])
		{
			case '1':{under_grasp1();place_playload1();break;}
			case '2':{under_grasp2();place_playload2();break;}
			case '3':{under_grasp3();place_playload3();break;}
			default : break;

		}
	}
}



//�ּӹ�����
void  First_choose_place1(u8* ptr,u8 mode)
{
	if(mode==1)
	{
	grasp_playload1();
	if(ptr[0]=='1')
		First_place2();
	else if(ptr[0]=='2')
     First_place3();
	else if(ptr[0]=='3')
			First_place1();
}
	else if(mode==2)
	{
		grasp_playload1();
	if(ptr[4]=='1')
		First_place2();
	else if(ptr[4]=='2')
     First_place3();
	else if(ptr[4]=='3')
			First_place1();
		
	}
}

void  First_choose_place2(u8* ptr,u8 mode)
{
	if(mode==1)
	{
	grasp_playload2();
	if(ptr[1]=='1')
		First_place2();
	else if(ptr[1]=='2')
     First_place3();
	else if(ptr[1]=='3')
			First_place1();
}
	else if(mode==2)
	{
		grasp_playload2();
	if(ptr[5]=='1')
		First_place2();
	else if(ptr[5]=='2')
     First_place3();
	else if(ptr[5]=='3')
			First_place1();
	}
	
}
void  First_choose_place3(u8* ptr,u8 mode)
{
	if(mode==1)
	{
	grasp_playload3();
	if(ptr[2]=='1')
		First_place2();
	else if(ptr[2]=='2')
     First_place3();
	else if(ptr[2]=='3')
			First_place1();
}
	else if(mode==2)
	{
			grasp_playload3();
	if(ptr[6]=='1')
		First_place2();
	else if(ptr[6]=='2')
     First_place3();
	else if(ptr[6]=='3')
			First_place1();
	}
}

void  First_place_all(u8* ptr,u8 mode)
{
	int i = 0;
		if(mode==1)
	{
	for(i=0;i<3;i++)
	{
			switch(ptr[i])
		{
			case '1':{grasp_playload1(); First_place2();break;}
			case '2':{grasp_playload2(); First_place3(); break;}
			case '3':{grasp_playload3(); First_place1();break;}
		  default:  break;
			    
		}
	}
}
	else if(mode==2)
	{
	for(i=4;i<7;i++)
	{
			switch(ptr[i])
		{
			case '1':{grasp_playload1(); First_place2();break;}
			case '2':{grasp_playload2();First_place3(); break;}
			case '3':{grasp_playload3(); First_place1();break;}
		  default:  break;
			    
		}
	}
}
}



//�ּӹ�����ȡ����Ϊqe_mes
void  cujiagong_choose_grasp1(u8 *ptr,u8 mode)
{
	if(mode==1)
	{
	if(ptr[0]=='1')
		cujiagongclip2();
	else if(ptr[0]=='2')
     cujiagongclip3();
	else if(ptr[0]=='3')
			cujiagongclip1();
	place_playload3();
		
		
	}
	else if(mode==2)
	{
			if(ptr[4]=='1')
		cujiagongclip2();
	else if(ptr[4]=='2')
     cujiagongclip3();
	else if(ptr[4]=='3')
			cujiagongclip1();
		place_playload3();

	}
	
}
void  cujiagong_choose_grasp2(u8 *ptr,u8 mode)
{
	if(mode==1)
	{
	if(ptr[1]=='1')
		cujiagongclip2();
	else if(ptr[1]=='2')
     cujiagongclip3();
	else if(ptr[1]=='3')
			cujiagongclip1();
	place_playload2();
		
		
	}
	else if(mode==2)
	{
			if(ptr[5]=='1')
		cujiagongclip2();
	else if(ptr[5]=='2')
     cujiagongclip3();
	else if(ptr[5]=='3')
			cujiagongclip1();
		place_playload2();

	}
}
void  cujiagong_choose_grasp3(u8 *ptr,u8 mode)
{
	if(mode==1)
	{
	if(ptr[2]=='1')
		cujiagongclip2();
	else if(ptr[2]=='2')
     cujiagongclip3();
	else if(ptr[2]=='3')
			cujiagongclip1();
	place_playload1();
	}
	else if(mode==2)
	{
			if(ptr[6]=='1')
		cujiagongclip2();
	else if(ptr[6]=='2')
     cujiagongclip3();
	else if(ptr[6]=='3')
			cujiagongclip1();
		place_playload1();

	}
}

//���Ʒ�ϲ����
void place_top_product1(u8* ptr)
{
	
	
	grasp_playload3();
	if(ptr[0]=='1')
		Second_place2();
	else if(ptr[0]=='2')
     Second_place3();
	else if(ptr[0]=='3')
			Second_place1();
   
	
	
}

void place_top_product2(u8* ptr)
{

	grasp_playload2();
	if(ptr[1]=='1')
		Second_place2();
	else if(ptr[1]=='2')
     Second_place3();
	else if(ptr[1]=='3')
			Second_place1();
   
	
}

void place_top_product3(u8* ptr)
{

	grasp_playload1();
	if(ptr[2]=='1')
		Second_place2();
	else if(ptr[2]=='2')
     Second_place3();
	else if(ptr[2]=='3')
			Second_place1();
 
	
}


//���Ʒ���²����
void place_under_product1(u8* ptr)
{
	
	grasp_playload3();
	if(ptr[4]=='1')
		Third_place2();
	else if(ptr[4]=='2')
     Third_place3();
	else if(ptr[4]=='3')
			Third_place1();
  
	
}

void place_under_product2(u8* ptr)
{
	
	grasp_playload2();
	if(ptr[5]=='1')
		Third_place2();
	else if(ptr[5]=='2')
     Third_place3();
	else if(ptr[5]=='3')
			Third_place1();

	
}

void place_under_product3(u8* ptr )
{

	grasp_playload1();
	if(ptr[6]=='1')
		Third_place2();
	else if(ptr[6]=='2')
     Third_place3();
	else if(ptr[6]=='3')
			Third_place1();
  
}
