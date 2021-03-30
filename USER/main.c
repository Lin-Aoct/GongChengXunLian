#include "sys.h"


u8 CONTROL_MODE;				//控制模式变量
u8 IS_USART1_RX_HEAD;		//标志是否接收到数据头
u8 USART1_RX_BUF[4];		//USART1接收缓冲
u8 USART1_RX_DATA[4];		//存储USART1接收到的数据

u8 UART4_RX_DATA;				//存储UART4接收到的数据

u16 led_val = 50;
u8 up_flag = 1;
u16 count_flag;
u8 action_mode = 10;				//串口1动作指令变量
u8 u4_action_mode = 0;			//机械臂动作指令变量
u8 IS_USART1_RX_Success = 0;


int	main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//配置中断优先级分组
	delay_init(168);						//延时函数初始化
	//KEY_Init();								//按键初始化
	//LED_Init();								//LED 灯初始化
	uart_init(115200);					//USART1 初始化
	//uart4_init(9600);						//UART4 初始化
	Find_IO_Init();							//红外循迹模块初始化
	MOTO_GPIO_Config();					//电机驱动引脚初始化
	MOTOR_PWM_Init(7199, 0);	 	//TIM2 电机驱动 PWM 初始化
	//Encoder_Init_TIM3();				//TIM3 定时器初始化编码模式
	//Encoder_Init_TIM4();				//TIM3 定时器初始化编码模式
	TIM6_Init(150, 7199);				//TIM6 设置 15ms 定时中断
	
	Car_Stop();
	printf("初始化完成\n");
	//u4_printf("u4初始化完成");
	
	while(1)
	{
//		USART_SendData(UART4, '3');
//		if(count_flag==65500) 
//			count_flag = 0, printf("%d", read_cnt());
//		count_flag ++;

		/*
		//判断是否收到机械臂动作
		if(IS_UART4_RX_Success==1) 
		{
			u4_action_mode = UART4_RX_DATA;
			printf("收到机械臂指令：%c", UART4_RX_DATA);
			IS_UART4_RX_Success = 0;
		}
		//根据机械臂指令执行对应的动作
		switch(u4_action_mode)
		{
			case '1': Mode_Init(), Stop_Find(), CAR_MODE = 2; break;
			case '2': Mode_Init(), Stop_Find(), CAR_MODE = 3; break;
			case '3': Mode_Init(), Stop_Find(), CAR_MODE = 4; break;
			case '4': Mode_Init(), Stop_Find(), CAR_MODE = 5; break;
			case '5': Mode_Init(), Stop_Find(), CAR_MODE = 6; break;
			case '6': Mode_Init(), Stop_Find(), CAR_MODE = 7; break;
			default: break;
		}
		u4_action_mode = 100;
		*/
		
		//判断是否收到串口1动作
		if(IS_USART1_RX_Success==1) 
		{
			memcpy(USART1_RX_DATA, USART1_RX_BUF, 4*sizeof(u8));	//获取串口1缓冲区数据
			action_mode = USART1_RX_DATA[0];
			printf("收到u1指令：%x", action_mode);
			IS_USART1_RX_Success = 0;
		}
		
		switch(action_mode)
		{
			case 0x0: CAR_MODE = 0; Car_Go(); break;
			case 0x1: CAR_MODE = 0; Car_Back(); break;
			case 0x2: CAR_MODE = 0; Car_Go_Left(); break;
			case 0x3: CAR_MODE = 0; Car_Go_Right(); break;
			case 0x4: CAR_MODE = 0; Car_Left_Front(); break;
			case 0x5: CAR_MODE = 0; Car_Right_Front(); break;
			case 0x6: CAR_MODE = 0; Car_Raw_Left(); break;
			case 0x7: CAR_MODE = 0; Car_Raw_Right(); break;
			case 0x8: MOTOR_Speed_Up(1000); break;
			case 0x9: MOTOR_Speed_Down(1000); break;
			case 0x10: CAR_MODE = 0; Car_Stop(); break;
			case 0x11: CAR_MODE = 0; Car_Stop(); break;
			//功能部分
			case 0x12: Mode_Init(), Stop_Find(), CAR_MODE = 1; break;
			case 0x13: Mode_Init(), Stop_Find(), CAR_MODE = 2; break;
			case 0x14: Mode_Init(), Stop_Find(), CAR_MODE = 3; break;
			case 0x15: Mode_Init(), Stop_Find(), CAR_MODE = 4; break;
			case 0x16: Mode_Init(), Stop_Find(), CAR_MODE = 5; break;
			case 0x17: Mode_Init(), Stop_Find(), CAR_MODE = 6; break;
			case 0x18: break;
			case 0x19: break;
			case 0x20: break;
			case 0x21: USART_SendData(UART4, '1'); break;
			case 0x22: USART_SendData(UART4, '2'); break;
			case 0x23: USART_SendData(UART4, '3'); break;
			case 0x24: USART_SendData(UART4, '4'); break;
			case 0x25: USART_SendData(UART4, '5'); break;
			default: break;
		}
		action_mode = 100;
		MOTOR_PWM_Out(MOTOR_PWM[0], MOTOR_PWM[1], MOTOR_PWM[2], MOTOR_PWM[3]);
	}
}
