#include "find.h"

u8 FIND_DRIVER = 0;		//��־��ǰѭ������ģ��	0����ǰ��	1�����Ҳ� 2�������	3�������
u8 CURRENT_DIRATION;	//��־��ǰ�˶�����	0ͣ��	1ǰ	2��	3��	4��

u8 FIND_MODE = 1;			//��־ѭ��ģʽ 0����raw	1	�������

/*
*===================================================================
*		˵��������ѭ��ģ��IO���ų�ʼ��
*		��������
*		���أ���
*===================================================================
*/
void Find_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC |
													RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF |
														RCC_AHB1Periph_GPIOG, ENABLE);	//ʹ��GPIOʱ��
	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;				//����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 				//����
	
	//PC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;											//IO�˿�
	GPIO_Init(GPIOC, &GPIO_InitStructure);							//��ʼ������GPIO�Ĵ���
	
	//PD
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4 | GPIO_Pin_6;					//IO�˿�
	GPIO_Init(GPIOD, &GPIO_InitStructure);							//��ʼ������GPIO�Ĵ���
	
	//PE
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;											//IO�˿�
	GPIO_Init(GPIOE, &GPIO_InitStructure);							//��ʼ������GPIO�Ĵ���
	
	//PF
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;			//IO�˿�
	GPIO_Init(GPIOF, &GPIO_InitStructure);							//��ʼ������GPIO�Ĵ���
	
	//PG
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15 | GPIO_Pin_1;		//IO�˿�
	GPIO_Init(GPIOG, &GPIO_InitStructure);							//��ʼ������GPIO�Ĵ���
} 

/*
*===================================================================
*		˵������ȡǰ�����ģ�������
*		��������
*		���أ�result	<u16>	�Ѻ������ݱ����λ������������
*===================================================================
*/
u16 Find_Get_Front(void)
{
	return Find_Front_1*1000 + Find_Front_2*100 + Find_Front_3*10 + Find_Front_4;
}

/*
*===================================================================
*		˵������ȡ�Ҳ����ģ�������
*		��������
*		���أ�result	<u16>	�Ѻ������ݱ����λ������������
*===================================================================
*/
u16 Find_Get_Right(void)
{
	return Find_Right_1*1000 + Find_Right_2*100 + Find_Right_3*10 + Find_Right_4;
}

/*
*===================================================================
*		˵������ȡ�������ģ�������
*		��������
*		���أ�result	<u16>	�Ѻ������ݱ����λ������������
*===================================================================
*/
u16 Find_Get_Behind(void)
{
	return Find_Behind_1*1000 + Find_Behind_2*100 + Find_Behind_3*10 + Find_Behind_4;
}

/*
*===================================================================
*		˵������ȡ������ģ�������
*		��������
*		���أ�result	<u16>	�Ѻ������ݱ����λ������������
*===================================================================
*/
u16 Find_Get_Left(void)
{
	return Find_Left_1*1000 + Find_Left_2*100 + Find_Left_3*10 + Find_Left_4;
}

/*
*===================================================================
*		˵��������ѭ��ģ��IO���Ų��ԣ���ȡIO�����ݣ���ͨ�����ڴ�ӡ����
*		��������
*		���أ���
*===================================================================
*/
void Find_Test(void)
{
	printf("����[%d %d %d %d]", Find_Get_Front(), Find_Get_Right(), Find_Get_Behind(), Find_Get_Left());
}

/*
*===================================================================
*		˵��������ѭ��ģ��Ѳ�� IO��ȡ���͵�ƽ�����ں��ߴ� ��ʱ����
*		��������
*		���أ���
*===================================================================
*/
void Find(void)
{
	u16 front_data, right_data, behind_data, left_data;
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	behind_data = Find_Get_Behind();
	left_data = Find_Get_Left();
	
	if(FIND_DRIVER == 0 && CURRENT_DIRATION == 1)				//ǰ��ѭ��
	{
		if(FIND_MODE)
		{
			if(front_data == 11 || front_data == 111 || front_data == 1011)
				Set_Speed_Target(1, 15), Set_Speed_Target(2, 15), Set_Speed_Target(3, 30), Set_Speed_Target(4, 30);
				//Car_Yaw_Left();
			else if(front_data == 1100 || front_data == 1110 || front_data == 1101)
				Set_Speed_Target(3, 15), Set_Speed_Target(4, 15), Set_Speed_Target(1, 30), Set_Speed_Target(2, 30);
				//Car_Yaw_Right();
			else if(front_data == 1001) Car_Continue();
		}
		else
		{
			if(front_data == 11 || front_data == 111 || front_data == 1011)
				Car_Yaw_Left();
			else if(front_data == 1100 || front_data == 1110 || front_data == 1101)
				Car_Yaw_Right();
			else Car_Continue();
		}
	}
	else if(FIND_DRIVER == 1 && CURRENT_DIRATION == 4)	//�Ҳ�ѭ��
	{
		if(right_data == 11 || right_data == 111 || right_data == 1011)
			Set_Speed_Target(3, 10), Set_Speed_Target(4, 30);
			//Car_Yaw_Left();
		else if(right_data == 1100 || right_data == 1110 || right_data == 1101)
			Set_Speed_Target(4, 10), Set_Speed_Target(3, 30);
			//Car_Yaw_Right();
		else if(right_data == 1001) Car_Continue();
	}
	else if(FIND_DRIVER == 2 && CURRENT_DIRATION == 2)	//����ѭ��
	{
		if(FIND_MODE)
		{
			if(behind_data == 11 || behind_data == 111 || behind_data == 1011)
				Set_Speed_Target(3, 15), Set_Speed_Target(4, 15), Set_Speed_Target(1, 30),Set_Speed_Target(2, 30);
				//Car_Yaw_Left();
			else if(behind_data == 1100 || behind_data == 1110 || behind_data == 1101)
				Set_Speed_Target(1, 15),Set_Speed_Target(2, 15), Set_Speed_Target(3, 30),Set_Speed_Target(4, 30);
				//Car_Yaw_Right();
			else if(behind_data == 1001) Car_Continue();
		}
		else
		{
			if(behind_data == 11 || behind_data == 111 || behind_data == 1011)
				Car_Yaw_Left();
			else if(behind_data == 1100 || behind_data == 1110 || behind_data == 1101)
				Car_Yaw_Right();
			else Car_Continue();
		}
	}
	else if(FIND_DRIVER == 3 && CURRENT_DIRATION == 3)	//���ѭ��
	{
		if(left_data == 11 || left_data == 111 || left_data == 1011)
			Set_Speed_Target(2, 5), Set_Speed_Target(1, 30);
			//Car_Yaw_Left();
		else if(left_data == 1100 || left_data == 1110 || left_data == 1101)
			Set_Speed_Target(1, 5), Set_Speed_Target(2, 30);
			//Car_Yaw_Right();
		else if(left_data == 1001) Car_Continue();
	}
}

/*
*===================================================================
*		˵����ѭ��ʱ��������� �������������� ������ǰ�����˶�
*		��������
*		���أ���
*===================================================================
*/
void Car_Continue(void)
{
	switch(CURRENT_DIRATION)
	{
		case 0:	break;
		case 1:	Car_Go(); break;
		case 2:	Car_Back();break;
		case 3:	Car_Go_Left(); break;
		case 4:	Car_Go_Right(); break;
		default: break;
	}
	Reset_Target_Speed();
}

/*
*===================================================================
*		˵����ֹͣѭ�� ѭ����ز�������
*		��������
*		���أ���
*===================================================================
*/
void Stop_Find(void)
{
	FIND_DRIVER = 0;
	CURRENT_DIRATION = 0;
	FIND_MODE = 1;
}
