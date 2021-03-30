#include "control.h"	

u8 CAR_MODE = 0;						//��־С��ģʽ
u8 step=0, count = 10;			//��־ִ�в����Լ���ʱ����
u16 front_data, right_data;	//ǰ���Һ���ѭ��ģ���������
	
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
			case 1: Mode_Start(); break;						//����
			case 2: Mode_Go_Area1(); break;					//��ά�� 			-> 	���϶ѷ���
			case 3: Mode_Area1_To_Area2(); break;		//���϶ѷ���	->	�ּӹ���
			case 4: Mode_Area2_To_Area1(); break;		//�ּӹ���		->	���϶ѷ���
			case 5: Mode_Area2_To_Area3(); break;		//�ּӹ���		->	���Ʒ��
			case 6: Mode_Area3_To_Area2(); break;		//���Ʒ��		->	�ּӹ���
			default: break;
		}
		//printf("\nH1��%d, H2��%d, step��%d\n", front_data, right_data, step);	//��ӡ������Ϣ
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);			//���TIM6���жϴ�����λ
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
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Go_Left();		//��ƽ��
	
	if(front_data == 1001 && step == 0)	Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, step = 1;	//ǰ�洦������
	Find();
	if(right_data == 1001 && step == 1)	step = 2;	//��1�м�
	
	if(right_data == 1110 && step == 2)	step = 3;	//����1
	
	if(right_data == 1001 && step == 3)	step = 4;	//��2�м�
	
	if(right_data == 1110 && step == 4)	step = 5;	//����2
		
	if(count > 0 && step == 5)	count--;						//6*15ms = 150ms

	if(count <= 0 && step == 5)	Car_Go_Left(), Stop_Find(), step = 6;	//����

	if(right_data == 0000 && step == 6)	
	{
		Car_Stop();										//�˳�����ģʽ
		CAR_MODE = 0;
		USART_SendData(UART4, '1');		//��е��ɨ��
	}
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
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Go_Left();		//��ƽ��
	
	if(front_data == 1001 && step == 0)	Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, step = 1;	//ǰ�洦������
	Find();
	
	if(right_data == 1001 && step == 1)	step = 2;	//��1�м�
	if(right_data == 1110 && step == 2)	step = 3;	//����1
	
	if(right_data == 1001 && step == 3)	step = 4;	//��2�м�
	if(right_data == 1110 && step == 4)	step = 5;	//����2
	
	if(right_data == 1001 && step == 5)	step = 6;	//��3�м�
	if(right_data == 1110 && step == 6)	step = 7;	//����3
	
	if((right_data == 1001 || right_data == 0011) && step == 7)	step = 8, MOTOR_Speed_Down(3000), Car_Go_Right(), FIND_DRIVER=1, CURRENT_DIRATION=4;	//������4 ��ƽ��

	if(right_data == 0000 && step == 8)	
	{
		step = 9;
		Car_Stop();
		Stop_Find();
		MOTOR_Speed_Up(3000);
		USART_SendData(UART4, '2');	//��е��ץȡ����
		CAR_MODE = 0;	//��������ץȡλ�� �˳�ģʽ
	}
}

/*
*===================================================================
*		˵�������϶ѷ�����ǰ���ּӹ���
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area1_To_Area2(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Go_Left(), FIND_DRIVER=1, CURRENT_DIRATION=3, step = 1;	//��ƽ��	Y��ѭ��
	Find();
	
	if(front_data == 1001 && step == 1)	step = 2;	//��1�м�
	if(front_data == 1110 && step == 2)	step = 3;	//����1
	
	if(front_data == 1001 && step == 3)	step = 4;	//��2�м�
	if(front_data == 1110 && step == 4)	step = 5;	//����2
	
	if(front_data == 1001 && step == 5)						//��3�м�
	{
		step = 6;
		MOTOR_Speed_Down(3000), Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1;	//������3 ���� ��ǰ�˶� X��Ѳ��
	}

	if(front_data == 0000 && step == 6)
	{
		step = 7;
		Car_Stop();
		Stop_Find();
		USART_SendData(UART4, '3');		//��е�۷�������
		MOTOR_Speed_Up(3000);
		CAR_MODE = 0;									//�ּӹ���
	}
}

/*
*===================================================================
*		˵�����ּӹ���ǰ�����϶ѷ�����
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area2_To_Area1(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Back(), FIND_DRIVER=0, CURRENT_DIRATION=2, step = 1;	//����	X��ѭ��
	Find();
	
	if(right_data == 1001 && step == 1) Car_Go_Right(),	FIND_DRIVER=1, CURRENT_DIRATION=4, step = 2;	//Y�����м� ��ƽ�� Y��ѭ��
	
	if(front_data == 1001 && step == 2)	step = 3;	//��1�м�
	if(front_data == 1110 && step == 3)	step = 4;	//����1
	
	if(front_data == 1001 && step == 4)	step = 5;	//��2�м�
	if(front_data == 1110 && step == 5)	step = 6;	//����2

	if(right_data == 0000 && step == 6)	
	{
		step = 7;
		Car_Stop();
		Stop_Find();
		USART_SendData(UART4, '4');
		CAR_MODE = 0;	//ԭ����
	}
}

/*
*===================================================================
*		˵�����ּӹ���ǰ�����Ʒ����1
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area2_To_Area3(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Back(), FIND_DRIVER=0, CURRENT_DIRATION=2, step = 1;	//����	X��ѭ��
	Find();
	
	if(right_data == 1001 && step == 1)	Car_Go_Left(), FIND_DRIVER=1, CURRENT_DIRATION=3, step = 2;	//Y�����м� ��ƽ�� Y��ѭ��
	
	if(front_data == 1001 && step == 2)	step = 3;	//��1�м�
	if(front_data == 1110 && step == 3)	step = 4;	//����1
	
	if(front_data == 1001 && step == 4)	step = 5;	//��2�м�
	if(front_data == 1110 && step == 5)	step = 6;	//����2

	if(front_data == 1001 && step == 6)	Car_Back(), FIND_DRIVER=0, CURRENT_DIRATION=2, step = 7;	//X��3�м�	����	X��Ѳ��
	
	if(right_data == 1001 && step == 7)	step = 8;	//Y��1�м�
	if(right_data == 1110 && step == 8)	step = 9;	//��Y��1
	
	if(right_data == 1001 && step == 9)	step = 10;		//Y��2�м�
	if(right_data == 1110 && step == 10)	step = 11;	//��Y��2
	
	if(right_data == 1001 && step == 11)	Car_Stop(), Stop_Find(), CAR_MODE = 0, step = 12;		//Y��3�м�	���Ʒ��
}

/*
*===================================================================
*		˵�������Ʒ����1ǰ���ּӹ���
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area3_To_Area2(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, step = 1;	//ǰ��	X��ѭ��
	Find();
	
	if(right_data == 1001 && step == 1)	step = 2;	//Y��1�м�
	if(right_data == 1110 && step == 2)	step = 3;	//��Y��1
	
	if(right_data == 1001 && step == 3)	step = 4;	//Y��2�м�
	if(right_data == 1110 && step == 4)	step = 5;	//��Y��2

	if(right_data == 1001 && step == 5)	Car_Go_Right(), FIND_DRIVER=1, CURRENT_DIRATION=4, step = 6;	//Y��3�м�	����	Y��Ѳ��
	
	if(front_data == 1001 && step == 6)	step = 7;	//X��1�м�
	if(front_data == 1110 && step == 7)	step = 8;	//��X��1
	
	if(front_data == 1001 && step == 8)	step = 9;		//X��2�м�
	if(front_data == 1110 && step == 9)	step = 10;	//��X��2
	
	if(front_data == 1001 && step == 10)	Car_Stop(), Stop_Find(), CAR_MODE = 0, step = 11;		//Y��3�м�	���Ʒ��
}

/*
*===================================================================
*		˵�������Ʒ����2����
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area3_2_Back(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Back(), FIND_DRIVER=0, CURRENT_DIRATION=2, step = 1;	//����	X��ѭ��
	Find();
	
	if(right_data == 1001 && step == 1)	step = 2;	//Y��1�м�
	if(right_data == 1110 && step == 2)	step = 3;	//��Y��1
	
	if(right_data == 1001 && step == 3)	step = 4;	//Y��2�м�
	if(right_data == 1110 && step == 4)	step = 5;	//��Y��2

	if(right_data == 1001 && step == 5)	Car_Go_Right(), FIND_DRIVER=1, CURRENT_DIRATION=4, step = 6;	//Y��3�м�	����	Y��Ѳ��
	
	if(front_data == 1001 && step == 7)	step = 8;	//X��1�м�
	if(front_data == 1110 && step == 8)	step = 9;	//��X��1
	
	if(front_data == 1001 && step == 9)	step = 10;		//X��2�м�
	if(front_data == 1110 && step == 10)	step = 11;	//��X��2
	
	if(front_data == 1001 && step == 11)	Car_Stop(), Stop_Find(), CAR_MODE = 0, step = 12;		//Y��3�м�	���Ʒ��
}

void Mode_Init(void)
{
	step = 0;
	count = 10;
}
