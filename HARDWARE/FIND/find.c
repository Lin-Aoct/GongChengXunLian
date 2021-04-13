#include "find.h"

u8 FIND_DRIVER = 0;		//标志当前循迹红外模块	0代表前面	1代表右侧 2代表后面	3代表左侧
u8 CURRENT_DIRATION;	//标志当前运动方向	0停车	1前	2后	3左	4右

u8 FIND_MODE = 1;			//标志循迹模式 0代表raw	1	代表差速

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

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC |
													RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF |
														RCC_AHB1Periph_GPIOG, ENABLE);	//使能GPIO时钟
	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;				//输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 				//上拉
	
	//PC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;											//IO端口
	GPIO_Init(GPIOC, &GPIO_InitStructure);							//初始化外设GPIO寄存器
	
	//PD
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4 | GPIO_Pin_6;					//IO端口
	GPIO_Init(GPIOD, &GPIO_InitStructure);							//初始化外设GPIO寄存器
	
	//PE
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;											//IO端口
	GPIO_Init(GPIOE, &GPIO_InitStructure);							//初始化外设GPIO寄存器
	
	//PF
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;			//IO端口
	GPIO_Init(GPIOF, &GPIO_InitStructure);							//初始化外设GPIO寄存器
	
	//PG
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15 | GPIO_Pin_1;		//IO端口
	GPIO_Init(GPIOG, &GPIO_InitStructure);							//初始化外设GPIO寄存器
} 

/*
*===================================================================
*		说明：读取前面红外模块的数据
*		参数：无
*		返回：result	<u16>	把红外数据变成四位数整数并返回
*===================================================================
*/
u16 Find_Get_Front(void)
{
	return Find_Front_1*1000 + Find_Front_2*100 + Find_Front_3*10 + Find_Front_4;
}

/*
*===================================================================
*		说明：读取右侧红外模块的数据
*		参数：无
*		返回：result	<u16>	把红外数据变成四位数整数并返回
*===================================================================
*/
u16 Find_Get_Right(void)
{
	return Find_Right_1*1000 + Find_Right_2*100 + Find_Right_3*10 + Find_Right_4;
}

/*
*===================================================================
*		说明：读取后面红外模块的数据
*		参数：无
*		返回：result	<u16>	把红外数据变成四位数整数并返回
*===================================================================
*/
u16 Find_Get_Behind(void)
{
	return Find_Behind_1*1000 + Find_Behind_2*100 + Find_Behind_3*10 + Find_Behind_4;
}

/*
*===================================================================
*		说明：读取左侧红外模块的数据
*		参数：无
*		返回：result	<u16>	把红外数据变成四位数整数并返回
*===================================================================
*/
u16 Find_Get_Left(void)
{
	return Find_Left_1*1000 + Find_Left_2*100 + Find_Left_3*10 + Find_Left_4;
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
	printf("红外[%d %d %d %d]", Find_Get_Front(), Find_Get_Right(), Find_Get_Behind(), Find_Get_Left());
}

/*
*===================================================================
*		说明：红外循迹模块巡线 IO读取到低电平代表处于黑线处 定时调用
*		参数：无
*		返回：无
*===================================================================
*/
void Find(void)
{
	u16 front_data, right_data, behind_data, left_data;
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	behind_data = Find_Get_Behind();
	left_data = Find_Get_Left();
	
	if(FIND_DRIVER == 0 && CURRENT_DIRATION == 1)				//前面循迹
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
	else if(FIND_DRIVER == 1 && CURRENT_DIRATION == 4)	//右侧循迹
	{
		if(right_data == 11 || right_data == 111 || right_data == 1011)
			Set_Speed_Target(3, 10), Set_Speed_Target(4, 30);
			//Car_Yaw_Left();
		else if(right_data == 1100 || right_data == 1110 || right_data == 1101)
			Set_Speed_Target(4, 10), Set_Speed_Target(3, 30);
			//Car_Yaw_Right();
		else if(right_data == 1001) Car_Continue();
	}
	else if(FIND_DRIVER == 2 && CURRENT_DIRATION == 2)	//后面循迹
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
	else if(FIND_DRIVER == 3 && CURRENT_DIRATION == 3)	//左侧循迹
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
		case 2:	Car_Back();break;
		case 3:	Car_Go_Left(); break;
		case 4:	Car_Go_Right(); break;
		default: break;
	}
	Reset_Target_Speed();
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
	FIND_MODE = 1;
}
