#include "find.h"

u8 FIND_DRIVER = 0;	//��־��ǰѭ������ģ��	0����ǰ��	1�����Ҳ�
u8 CURRENT_DIRATION;	//��־��ǰ�˶�����	0ͣ��	1ǰ	2��	3��	4��

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

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC,ENABLE); 						//ʹ��GPIOA GPIOCʱ��
	
	//PA
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;							//IO�˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;					//����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 					//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);								//��ʼ������GPIO�Ĵ���
	
	//PC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
																GPIO_Pin_3 | GPIO_Pin_13 | GPIO_Pin_14 |
																GPIO_Pin_15;											//IO�˿�
	GPIO_Init(GPIOC, &GPIO_InitStructure);													//��ʼ������GPIO�Ĵ���
	
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
	u8 find_arry[8], count;

	find_arry[0] = Find_Front_1;
	find_arry[1] = Find_Front_2;
	find_arry[2] = Find_Front_3;
	find_arry[3] = Find_Front_4;
	
	find_arry[4] = Find_Right_1;
	find_arry[5] = Find_Right_2;
	find_arry[6] = Find_Right_3;
	find_arry[7] = Find_Right_4;
	
	for(count=0; count<=7; count++)
		printf("%d ", find_arry[count]);
	printf("\n");
}

/*
*===================================================================
*		˵������ȡǰ�����ģ�������
*		��������
*		���أ�result	<u8>	�Ѻ������ݱ����λ������������
*===================================================================
*/
u16 Find_Get_Front(void)
{
	u8 find_arry[4];

	find_arry[0] = Find_Front_1;
	find_arry[1] = Find_Front_2;
	find_arry[2] = Find_Front_3;
	find_arry[3] = Find_Front_4;
	
	return find_arry[0]*1000 + find_arry[1]*100 + find_arry[2]*10 + find_arry[3];
}

/*
*===================================================================
*		˵������ȡ�Ҳ����ģ�������
*		��������
*		���أ�result	<u8>	�Ѻ������ݱ����λ������������
*===================================================================
*/
u16 Find_Get_Right(void)
{
	u8 find_arry[4];

	find_arry[0] = Find_Right_1;
	find_arry[1] = Find_Right_2;
	find_arry[2] = Find_Right_3;
	find_arry[3] = Find_Right_4;
	return find_arry[0]*1000 + find_arry[1]*100 + find_arry[2]*10 + find_arry[3];
}

/*
*===================================================================
*		˵��������ѭ��ģ��Ѳ�ߣ�IO��ȡ���͵�ƽ�����ں��ߴ�
*		��������
*		���أ���
*===================================================================
*/
void Find(void)
{
	u16 front_data, right_data;
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(FIND_DRIVER == 0)	//ǰ��ѭ��
	{
		switch(CURRENT_DIRATION)
		{
			case 0: break;
			case 1:
			{
				if(front_data == 0011 || front_data == 0111)	Car_Raw_Left();//printf("����");
				else if(front_data == 1100 || front_data == 1110)	Car_Raw_Right();//printf("����");
				else Car_Continue();//printf("����");
				break;
			}
			case 2:
			{
//				if(front_data == 0011 || front_data == 0111)	Car_Raw_Left(), printf("����");
//				else if(front_data == 1100 || front_data == 1110)	Car_Raw_Right(),printf("����");
//				else Car_Continue(), printf("����");
//				break;
				if(front_data == 0011 || front_data == 0111 || front_data == 0001)	Car_Back();// printf("����");
				else if(front_data == 1100 || front_data == 1110 || front_data == 1000)	Car_Go();//printf("����");
				else Car_Continue();//printf("����");
				break;
			}
			default: break;
		}
	}
	if(FIND_DRIVER == 1)	//�Ҳ�ѭ��
	{
		switch(CURRENT_DIRATION)
		{
			case 0: break;
			case 1:
			{
				if(right_data == 0011 || right_data == 0111)	Car_Raw_Left();// printf("����");
				else if(right_data == 1100 || right_data == 1110)	Car_Raw_Right();//printf("����");
				else Car_Continue();//printf("����");
				break;
			}
			case 3:
			{
				if(right_data == 0011 || right_data == 0111 || right_data == 0001)	Car_Back();//printf("����");
				else if(right_data == 1100 || right_data == 1110 || right_data == 1000)	Car_Go();//printf("����");
				else Car_Continue();//printf("����");
				break;
			}
			case 4:
			{
				if(right_data == 0011 || right_data == 0111)	Car_Raw_Left();//printf("����");
				else if(right_data == 1100 || right_data == 1110)	Car_Raw_Right();//printf("����");
				else Car_Continue();//printf("����");
				break;
			}
			default: break;
		}
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
		case 2:	Car_Back(); break;
		case 3:	Car_Go_Left(); break;
		case 4:	Car_Go_Right(); break;
		default: break;
	}
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
}
