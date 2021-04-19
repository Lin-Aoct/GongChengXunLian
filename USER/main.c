#include "sys.h"


u8 IS_USART1_RX_HEAD;		//标志是否接收到数据头
u8 IS_USART1_RX_Success = 0;
u8 USART1_RX_BUF[4];		//USART1接收缓冲
u8 USART1_RX_DATA[4];		//存储USART1接收到的数据

u8 UART4_RX_DATA;				//存储UART4接收到的数据

u32 count_flag;								//Debug
u8 u1_action_mode = 10;				//串口1动作指令变量

u8 ARM_Action = 0;						//机械臂动作变量
u8 is_start = 0;							//标志是否已开始
int motor_current_pwm[4];

int	main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//配置中断优先级分组
	delay_init(168);						//延时函数初始化
	uart_init(115200);					//USART1 初始化
	
	OPENMV_init(9600);					//OPENMV USART2 初始化
	bluetooth_init(115200);			//蓝牙 USART3 初始化
	RobotArm_Pwm_init();				//机械臂初始化
	scan_qr_on();								//机械臂保持扫码动作

	KEY_Init();									//按键初始化
	//LED_Init();									//LED 灯初始化
	Lcd_Init();									//TFT屏幕初始化
	Find_IO_Init();							//红外循迹模块初始化
	MOTO_GPIO_Config();					//电机驱动引脚初始化
	MOTOR_PWM_Init(499, 83);	 	//TIM8 电机驱动 PWM 初始化 7199 16799
	Encoder_Init_TIM2();				//TIM2 定时器初始化编码模式
	Encoder_Init_TIM3();				//TIM3 定时器初始化编码模式
	Encoder_Init_TIM4();				//TIM4 定时器初始化编码模式
	Encoder_Init_TIM5();				//TIM5 定时器初始化编码模式
	TIM6_Init(150, 8399);				//TIM6 设置 15ms 定时中断
	//TIM7_Init(150, 8399);			//TIM7 定时 15ms 中断

	Car_Stop();
	Lcd_Clear(BLACK);
	//GUI_Draw_Long_Font(1, 1, WHITE, BLACK, (u8*)qr_mes);
	printf("初始化完成\n");
	
	while(1)
	{
		//vcan_sendware((uint8_t *)ENCODER_DATA, sizeof(ENCODER_DATA));		//编码器波形发送

//		if(count_flag == 65535) 
//			count_flag = 0,Find_Test();
//		count_flag ++;

		//判断按键是否按下 一键启动
		if(KEY_Scan(0) == 1 && is_start==0)
			Mode_Init(), Stop_Find(), CAR_MODE = 1, is_start=1;

		
		//判断是否收到串口1动作
		if(IS_USART1_RX_Success==1) 
		{
			memcpy(USART1_RX_DATA, USART1_RX_BUF, 4*sizeof(u8));	//获取串口1缓冲区数据
			u1_action_mode = USART1_RX_DATA[0];
			printf("收到u1指令：%x\n", u1_action_mode);
			IS_USART1_RX_Success = 0;
		}
		switch(u1_action_mode)
		{
			case 0x0: CAR_MODE = 0; MOTOR_PWM_Out(MOTOR_PWM[0], MOTOR_PWM[1], MOTOR_PWM[2], MOTOR_PWM[3]); Car_Go(); break;
			case 0x1: CAR_MODE = 0; MOTOR_PWM_Out(MOTOR_PWM[0], MOTOR_PWM[1], MOTOR_PWM[2], MOTOR_PWM[3]); Car_Back(); break;
			case 0x2: CAR_MODE = 0; MOTOR_PWM_Out(MOTOR_PWM[0], MOTOR_PWM[1], MOTOR_PWM[2], MOTOR_PWM[3]); Car_Go_Left(); break;
			case 0x3: CAR_MODE = 0; MOTOR_PWM_Out(MOTOR_PWM[0], MOTOR_PWM[1], MOTOR_PWM[2], MOTOR_PWM[3]); Car_Go_Right(); break;
			case 0x4: CAR_MODE = 0; MOTOR_PWM_Out(MOTOR_PWM[0], MOTOR_PWM[1], MOTOR_PWM[2], MOTOR_PWM[3]); Car_Left_Front(); break;
			case 0x5: CAR_MODE = 0; MOTOR_PWM_Out(MOTOR_PWM[0], MOTOR_PWM[1], MOTOR_PWM[2], MOTOR_PWM[3]); Car_Right_Front(); break;
			case 0x6: CAR_MODE = 0; MOTOR_PWM_Out(MOTOR_PWM[0], MOTOR_PWM[1], MOTOR_PWM[2], MOTOR_PWM[3]); Car_Yaw_Left(); break;
			case 0x7: CAR_MODE = 0; MOTOR_PWM_Out(MOTOR_PWM[0], MOTOR_PWM[1], MOTOR_PWM[2], MOTOR_PWM[3]); Car_Yaw_Right(); break;
			case 0x8: LED0=1; break;//MOTOR_Speed_Up(10); break;
			case 0x9: LED0=0; break;//MOTOR_Speed_Down(10); break;
			case 0x10: CAR_MODE = 0; Car_Stop(); break;
			case 0x11: CAR_MODE = 0; Car_Stop(); break;
			//功能部分
			case 0x12: Mode_Init(), Stop_Find(), CAR_MODE = 1; break;
			case 0x13: Mode_Init(), Stop_Find(), CAR_MODE = 2; break;
			case 0x14: Mode_Init(), Stop_Find(), CAR_MODE = 3; break;
			case 0x15: Mode_Init(), Stop_Find(), CAR_MODE = 4; break;
			case 0x16: Mode_Init(), Stop_Find(), CAR_MODE = 5; break;
			case 0x17: Mode_Init(), Stop_Find(), CAR_MODE = 6; break;
			case 0x18: Mode_Init(), Stop_Find(), CAR_MODE = 7; break;
			case 0x19: Mode_Init(), Stop_Find(), CAR_MODE = 8; break;
			case 0x20: Mode_Init(), Stop_Find(), CAR_MODE = 9; break;
			case 0x66: Mode_Init(), Stop_Find(), CAR_MODE = 10; break;
			case 0x67: Mode_Init(), Stop_Find(), CAR_MODE = 11; break;
			case 0x68: Mode_Init(), Stop_Find(), CAR_MODE = 12; break;
			case 0x69: Mode_Init(), Stop_Find(), CAR_MODE = 13; break;
			case 0x70: Mode_Init(), Stop_Find(), CAR_MODE = 14; break;
			//杂项
			case 0x21: Change_Speed_Target(0, 1, 5); ENCODER_DATA[4]+=5; break;
			case 0x22: Change_Speed_Target(0, 0, 5); ENCODER_DATA[4]-=5; break;
			case 0x23: uart2_sendStr("1"); break;
			case 0x24: uart2_sendStr("2"); break;
			case 0x25: uart2_sendStr("3"); break;
			case 0x26: Mode_Init(), Stop_Find(), CAR_MODE = 20; break;
			case 0x27: Mode_Init(), Stop_Find(), CAR_MODE = 21; break;
			case 0x28: Mode_Init(), Stop_Find(), CAR_MODE = 22; break;
			case 0x29: Mode_Init(), Stop_Find(), CAR_MODE = 23; break;
			case 0x30: IS_MOTOR_ALL_STOP = 1; break;
			case 0x31: IS_MOTOR_ALL_STOP = 0; break;
			case 0x32: break;
			case 0x33: Mode_Init(), Stop_Find(), CAR_MODE = 24; break;
			case 0x34: Mode_Init(), Stop_Find(), CAR_MODE = 25; break;
			case 0x35: Mode_Init(), Stop_Find(), CAR_MODE = 26; break;
			case 0x36: Mode_Init(), Stop_Find(), CAR_MODE = 27; break;
			case 0x37: Mode_Init(), Stop_Find(), CAR_MODE = 28; break;
			case 0x38: Mode_Init(), Stop_Find(), CAR_MODE = 29; break;
			//PID调参
			case 0x40: Set_PID_Value(1, 1, 1, 1.0); break;
			case 0x41: Set_PID_Value(1, 1, 0, 1.0); break;
			case 0x42: Set_PID_Value(1, 2, 1, 0.01); break;
			case 0x43: Set_PID_Value(1, 2, 0, 0.01); break;
			case 0x44: Set_PID_Value(1, 3, 1, 1); break;
			case 0x45: Set_PID_Value(1, 3, 0, 1); break;

			case 0x46: Set_PID_Value(2, 1, 1, 1.0); break;
			case 0x47: Set_PID_Value(2, 1, 0, 1.0); break;
			case 0x48: Set_PID_Value(2, 2, 1, 0.01); break;
			case 0x49: Set_PID_Value(2, 2, 0, 0.01); break;
			case 0x50: Set_PID_Value(2, 3, 1, 1); break;
			case 0x51: Set_PID_Value(2, 3, 0, 1); break;

			case 0x52: Set_PID_Value(3, 1, 1, 1.0); break;
			case 0x53: Set_PID_Value(3, 1, 0, 1.0); break;
			case 0x54: Set_PID_Value(3, 2, 1, 0.01); break;
			case 0x55: Set_PID_Value(3, 2, 0, 0.01); break;
			case 0x56: Set_PID_Value(3, 3, 1, 0.1); break;
			case 0x57: Set_PID_Value(3, 3, 0, 0.1); break;

			case 0x58: Set_PID_Value(4, 1, 1, 1.0); break;
			case 0x59: Set_PID_Value(4, 1, 0, 1.0); break;
			case 0x60: Set_PID_Value(4, 2, 1, 0.01); break;
			case 0x61: Set_PID_Value(4, 2, 0, 0.01); break;
			case 0x62: Set_PID_Value(4, 3, 1, 0.1); break;
			case 0x63: Set_PID_Value(4, 3, 0, 0.1); break;
			
			case 0x71: is_car_debug_mode=1; break;
			case 0x72: is_car_debug_mode=0; break;
			default: break;
		}
		u1_action_mode = 100;

		
		//机械臂动作判断
		switch(ARM_Action)
		{
			case 0: break;
			case 1: OPENMV_Cmd("1");while(qr_mes[6]=='0'){Arm4-=17;delay_ms(200);Arm4 +=17;delay_ms(200);};printf("机械臂模式[扫码]\n");ARM_Action=0; break;		//扫码姿势 告诉OV扫码  Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"扫码"); 
			case 2: printf("OV发2\n"),OPENMV_Cmd("2"); printf("机械臂模式[OV扫描上层]\n"); ARM_Action=0; break;	//颜色识别	告诉OV识别上层颜色 Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"OV扫描上层"); 
			case 3: Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"抓取上层"); top_grasp_choose1(way1); top_grasp_choose2(way1); top_grasp_choose3(way1); Mode_Init(); CAR_MODE = 3; finish_top_grasp_status(); ARM_Action=0; break; 	//机械臂抓取物料
			case 4: 
			{
				printf("机械臂模式[粗加工区放置 上层模式]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//部分清屏
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"粗加工区上层放置");
				//第一次放置物料
				First_choose_place1(qr_mes, 1);
				First_choose_place2(qr_mes, 1);
				First_choose_place3(qr_mes, 1);
				//重新抓取物料
				printf("机械臂模式[粗加工区重新抓取物料 上层模式]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//部分清屏
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"粗加工区重新抓取");
				cujiagong_choose_grasp1(qr_mes, 1);
				cujiagong_choose_grasp2(qr_mes, 1);
				cujiagong_choose_grasp3(qr_mes, 1);
				Mode_Init();
				CAR_MODE = 4;		//粗加工 -> 半成品	顶层模式
				finish_rough_status();
				ARM_Action=0;
				break;
			}
			case 5: //半成品区上层放置
			{
				printf("机械臂模式[半成品区上层放置]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//部分清屏
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"半成品区上层放置");
				place_top_product1(qr_mes);
				place_top_product2(qr_mes);
				place_top_product3(qr_mes);
				Mode_Init();
				CAR_MODE = 5;					//半成品	-> 	原料区
				finish_top_product_status();		//机械臂识别颜色动作
				ARM_Action=0;
				break;
			}
			case 6:
			{
				//扫描下层物料
				printf("机械臂模式[扫描下层物料]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//部分清屏
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"扫描下层物料");
				delay_ms(100);
				LED0=1;
				OPENMV_Cmd("3");			//OV扫描颜色
				ARM_Action=0;
				break;
			}
			case 7:	
			{
				//准备第一次抓取下层
				printf("机械臂模式[准备第一次抓取下层]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//部分清屏
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"第一次抓取下层");
				under_grasp_choose1(way2);	//第一次机械臂伸出
				Mode_Init();
				CAR_MODE = 6;								//车第一次前进一格
				ARM_Action=0;
				break;
			}
			case 8:
			{
				//第一次爪子闭合
				printf("机械臂模式[第一次爪子闭合]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//部分清屏
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"爪子闭合1");
				Arm0 = 740;					//机械臂抓取动作
				Mode_Init();
				CAR_MODE = 7;				//车第一次后退一格
				ARM_Action=0;
				break;
			}
			case 9:
			{
				printf("机械臂模式[机械臂第一次收回]\n");
				Arm4 -= 8;delay_ms(50); 
				under_Arm_back();
				//Arm_back1();									//机械臂第一次收回
				place_playload1();						//放置物料到车上
				under_grasp_choose2(way2);		//机械臂伸出
				Mode_Init();
				CAR_MODE = 8;									//车第二次向前一格
				ARM_Action=0;
				break;
			}
			case 10:
			{
				//第二次爪子闭合
				printf("机械臂模式[第二次爪子闭合]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//部分清屏
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"爪子闭合2");
				Arm0 = 740;				//机械臂抓取动作
				Mode_Init();
				CAR_MODE = 9;			//车第二次后退一格
				ARM_Action=0;
				break;
			}
			case 11:					//准备第三次抓取
			{
				printf("机械臂模式[准备第三次抓取]\n");
				under_Arm_back();
				//Arm_back1();				//机械臂第二次收回
				place_playload2();	//放置物料到车上2
				under_grasp_choose3(way2);		//机械臂第三次伸出
				Mode_Init();
				CAR_MODE = 10;		//车第三次向前一格
				ARM_Action=0;
				break;
			}
			case 12:
			{
				//第三次爪子闭合
				printf("机械臂模式[第三次爪子闭合]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//部分清屏
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"爪子闭合3");
				Arm0 = 740;				//机械臂抓取动作
				
				Mode_Init();
				CAR_MODE = 11;		//车后退一格
				
				ARM_Action=0;
				break;
			}
			case 13:
			{
				printf("机械臂模式[下层抓取第三次存放]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//部分清屏
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"下层放置3");
				under_Arm_back();
				//Arm_back1();				//机械臂第三次收回
				place_playload3();	//放置物料到车上3
				Mode_Init();
				CAR_MODE = 12;			//车前往粗加工区 
				finish_under_grasp_status();
				ARM_Action=0;
				break;
			}
			case 14: 
			{
				//加工区放置物料 底层模式
				printf("机械臂模式[粗加工区放置物料 下层模式]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//部分清屏
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"加工区下层放置");
				First_choose_place1(qr_mes, 2);
				First_choose_place2(qr_mes, 2);
				First_choose_place3(qr_mes, 2);
				//加工区重新抓取物料 底层模式
				printf("机械臂模式[粗加工区重新抓取物料 下层模式]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//部分清屏
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"加工区下层抓取");
				cujiagong_choose_grasp1(qr_mes, 2);
				cujiagong_choose_grasp2(qr_mes, 2);
				cujiagong_choose_grasp3(qr_mes, 2);
				Mode_Init();
				CAR_MODE = 13;		//粗加工 -> 半成品	下层模式
				finish_rough_status();
				ARM_Action=0;
				break;
			}
			case 15: 
			{
				//半成品区放置 下层模式
				printf("机械臂模式[半成品区放置物料 下层模式]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//部分清屏
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"半成品区下层放置");
				if(is_plus_mode == 0)
				{
					place_under_product1(qr_mes);
					place_under_product2(qr_mes);
					place_under_product3(qr_mes);
				}
				else
				{
					Place_Plus1_choose(qr_mes);
					Place_Plus2_choose(qr_mes);
					Place_Plus3_choose(qr_mes);
				}

				Mode_Init();
				CAR_MODE = 14;		//去返回区
				ARM_Action=0;
				is_start = 0;			//标志已停机
				break;
			}
			default: break;
		}
	}
}
