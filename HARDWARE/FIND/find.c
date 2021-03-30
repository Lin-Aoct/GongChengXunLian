#include "find.h"

u8 FIND_DRIVER = 0;	//标志当前循迹红外模块	0代表前面	1代表右侧
u8 CURRENT_DIRATION;	//标志当前运动方向	0停车	1前	2后	3左	4右

/*
*===================================================================
*		说明：红外循迹模块IO引脚初始化
*		参数：无
*		返回：无
*===================================================================
*/
void Find_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC,ENABLE); 						//使能GPIOA GPIOC时钟
	
	//PA
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;							//IO端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;					//输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 					//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);								//初始化外设GPIO寄存器
	
	//PC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
																GPIO_Pin_3 | GPIO_Pin_13 | GPIO_Pin_14 |
																GPIO_Pin_15;											//IO端口
	GPIO_Init(GPIOC, &GPIO_InitStructure);													//初始化外设GPIO寄存器
	
} 

/*
*===================================================================
*		说明：红外循迹模块IO引脚测试，读取IO口数据，并通过串口打印数据
*		参数：无
*		返回：无
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
*		说明：读取前面红外模块的数据
*		参数：无
*		返回：result	<u8>	把红外数据变成四位数整数并返回
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
*		说明：读取右侧红外模块的数据
*		参数：无
*		返回：result	<u8>	把红外数据变成四位数整数并返回
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
*		说明：红外循迹模块巡线，IO读取到低电平代表处于黑线处
*		参数：无
*		返回：无
*===================================================================
*/
void Find(void)
{
	u16 front_data, right_data;
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(FIND_DRIVER == 0)	//前面循迹
	{
		switch(CURRENT_DIRATION)
		{
			case 0: break;
			case 1:
			{
				if(front_data == 0011 || front_data == 0111)	Car_Raw_Left();//printf("往左");
				else if(front_data == 1100 || front_data == 1110)	Car_Raw_Right();//printf("往右");
				else Car_Continue();//printf("继续");
				break;
			}
			case 2:
			{
//				if(front_data == 0011 || front_data == 0111)	Car_Raw_Left(), printf("往左");
//				else if(front_data == 1100 || front_data == 1110)	Car_Raw_Right(),printf("往右");
//				else Car_Continue(), printf("继续");
//				break;
				if(front_data == 0011 || front_data == 0111 || front_data == 0001)	Car_Back();// printf("往左");
				else if(front_data == 1100 || front_data == 1110 || front_data == 1000)	Car_Go();//printf("往右");
				else Car_Continue();//printf("继续");
				break;
			}
			default: break;
		}
	}
	if(FIND_DRIVER == 1)	//右侧循迹
	{
		switch(CURRENT_DIRATION)
		{
			case 0: break;
			case 1:
			{
				if(right_data == 0011 || right_data == 0111)	Car_Raw_Left();// printf("往左");
				else if(right_data == 1100 || right_data == 1110)	Car_Raw_Right();//printf("往右");
				else Car_Continue();//printf("继续");
				break;
			}
			case 3:
			{
				if(right_data == 0011 || right_data == 0111 || right_data == 0001)	Car_Back();//printf("往左");
				else if(right_data == 1100 || right_data == 1110 || right_data == 1000)	Car_Go();//printf("往右");
				else Car_Continue();//printf("继续");
				break;
			}
			case 4:
			{
				if(right_data == 0011 || right_data == 0111)	Car_Raw_Left();//printf("往左");
				else if(right_data == 1100 || right_data == 1110)	Car_Raw_Right();//printf("往右");
				else Car_Continue();//printf("继续");
				break;
			}
			default: break;
		}
	}
}

/*
*===================================================================
*		说明：循迹时若方向合适 则不作出机动动作 继续当前方向运动
*		参数：无
*		返回：无
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
*		说明：停止循迹 循迹相关参数清零
*		参数：无
*		返回：无
*===================================================================
*/
void Stop_Find(void)
{
	FIND_DRIVER = 0;
	CURRENT_DIRATION = 0;
}
