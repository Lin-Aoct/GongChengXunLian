#include "sys.h"


u8 IS_USART1_RX_HEAD;		//��־�Ƿ���յ�����ͷ
u8 IS_USART1_RX_Success = 0;
u8 USART1_RX_BUF[4];		//USART1���ջ���
u8 USART1_RX_DATA[4];		//�洢USART1���յ�������

u8 UART4_RX_DATA;				//�洢UART4���յ�������

u32 count_flag;					//Debug
u8 u1_action_mode = 10;				//����1����ָ�����
u8 car_u1_action_mode = 0;			//��е�۶���ָ�����


u8 TFT_String[2];

u8 ARM_Action = 0;			//��е�۶�������

int motor_current_pwm[4];

int	main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//�����ж����ȼ�����
	delay_init(168);						//��ʱ������ʼ��
	//KEY_Init();								//������ʼ��
	//LED_Init();								//LED �Ƴ�ʼ��
	uart_init(115200);					//USART1 ��ʼ��
	
	OPENMV_init(9600);					//OPENMV USART2 ��ʼ��
	bluetooth_init(115200);			//���� USART3 ��ʼ��
	RobotArm_Pwm_init();				//��е�۳�ʼ��
	scan_qr_on();								//��е�۱���ɨ�붯��

	Lcd_Init();									//TFT��Ļ��ʼ��
	Find_IO_Init();							//����ѭ��ģ���ʼ��
	MOTO_GPIO_Config();					//����������ų�ʼ��
	MOTOR_PWM_Init(499, 83);	 	//TIM8 ������� PWM ��ʼ�� 7199 16799
	Encoder_Init_TIM2();				//TIM2 ��ʱ����ʼ������ģʽ
	Encoder_Init_TIM3();				//TIM3 ��ʱ����ʼ������ģʽ
	Encoder_Init_TIM4();				//TIM4 ��ʱ����ʼ������ģʽ
	Encoder_Init_TIM5();				//TIM5 ��ʱ����ʼ������ģʽ
	TIM6_Init(150, 8399);				//TIM6 ���� 15ms ��ʱ�ж�
	//TIM7_Init(150, 8399);			//TIM7 ��ʱ 15ms �ж�

	Car_Stop();
	Lcd_Clear(BLACK);
	GUI_Draw_Long_Font(1, 1, WHITE, BLACK, (u8*)qr_mes);
	printf("��ʼ�����\n");
	
	while(1)
	{
		vcan_sendware((uint8_t *)ENCODER_DATA, sizeof(ENCODER_DATA));
		//vcan_sendware((uint8_t *)motor_current_pwm[3], sizeof(int));

		//Lcd_Clear(GRAY0);

		//delay_ms(1000);
		//Gui_DrawFont_GBK16(0,80,RED,GRAY0, qr_mes);	

//		if(count_flag == 65535) 
//			count_flag = 0,Find_Test();
//		count_flag ++;

		
		//�ж��Ƿ��յ�����1����
		if(IS_USART1_RX_Success==1) 
		{
			memcpy(USART1_RX_DATA, USART1_RX_BUF, 4*sizeof(u8));	//��ȡ����1����������
			u1_action_mode = USART1_RX_DATA[0];
			printf("�յ�u1ָ�%x\n", u1_action_mode);
			//Lcd_Clear(GRAY0);
			//sprintf((u8*)TFT_String, "%d", u1_action_mode);
			//Gui_DrawFont_GBK16(60,80,RED,GRAY0, TFT_String);	
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
			case 0x8: MOTOR_Speed_Up(10); break;
			case 0x9: MOTOR_Speed_Down(10); break;
			case 0x10: CAR_MODE = 0; Car_Stop(); break;
			case 0x11: CAR_MODE = 0; Car_Stop(); break;
			//���ܲ���
			case 0x12: Mode_Init(), Stop_Find(), CAR_MODE = 1; break;
			case 0x13: Mode_Init(), Stop_Find(), CAR_MODE = 2; break;
			case 0x14: Mode_Init(), Stop_Find(), CAR_MODE = 3; break;
			case 0x15: Mode_Init(), Stop_Find(), CAR_MODE = 4; break;
			case 0x16: Mode_Init(), Stop_Find(), CAR_MODE = 5; break;
			case 0x17: Mode_Init(), Stop_Find(), CAR_MODE = 6; break;
			case 0x18: Mode_Init(), Stop_Find(), CAR_MODE = 7; break;
			case 0x19: ARM_Action = 9; break;
			case 0x20: Mode_Init(), Stop_Find(), CAR_MODE = 9; break;
			case 0x21: Change_Speed_Target(0, 1, 5); ENCODER_DATA[4]+=5; break;
			case 0x22: Change_Speed_Target(0, 0, 5); ENCODER_DATA[4]-=5; break;
			case 0x23: uart2_sendStr("1"); break;
			case 0x24: uart2_sendStr("2"); break;
			case 0x25: uart2_sendStr("3"); break;
			case 0x26: Mode_Init(), Stop_Find(), CAR_MODE = 10; break;
			case 0x27: Mode_Init(), Stop_Find(), CAR_MODE = 11; break;
			case 0x28: Mode_Init(), Stop_Find(), CAR_MODE = 12; break;
			case 0x29: Mode_Init(), Stop_Find(), CAR_MODE = 13; break;
			case 0x30: IS_MOTOR_ALL_STOP = 1; break;
			case 0x31: IS_MOTOR_ALL_STOP = 0; break;
			
			case 0x33: Mode_Init(), Stop_Find(), CAR_MODE = 14; break;
			case 0x34: Mode_Init(), Stop_Find(), CAR_MODE = 15; break;
			case 0x35: Mode_Init(), Stop_Find(), CAR_MODE = 16; break;
			case 0x36: Mode_Init(), Stop_Find(), CAR_MODE = 17; break;
			
			case 0x37: Mode_Init(), Stop_Find(), CAR_MODE = 20; break;
			case 0x38: Mode_Init(), Stop_Find(), CAR_MODE = 21; break;
			
			//PID����
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
			
			default: break;
		}
		u1_action_mode = 100;
		//MOTOR_PWM_Out(MOTOR_PWM[0], MOTOR_PWM[1], MOTOR_PWM[2], MOTOR_PWM[3]);
	
	
		//��е�۶����ж�
		switch(ARM_Action)
		{
			case 0: break;
			case 1: scan_qr_on(); uart2_sendStr("1"); ARM_Action=0; break;		//ɨ������ ����OVɨ��
			case 2: scan_block_top(); uart2_sendStr("2"); ARM_Action=0;	break;	//��ɫʶ��	����OVʶ���ϲ���ɫ
			case 3: top_grasp_choose1(way1); top_grasp_choose2(way1); top_grasp_choose3(way1); Mode_Init(); CAR_MODE = 3; ARM_Action=0; break; 	//��е��ץȡɫ��
			case 4: 
			{
				printf("��е��ģʽ[��һ�η���]");
				//��һ�η�������
				First_choose_place1(qr_mes, 1);
				First_choose_place2(qr_mes, 1);
				First_choose_place3(qr_mes, 1);
				//����ץȡ����
				printf("��е��ģʽ[����ץȡ����]");
				cujiagong_choose_grasp1(qr_mes, 1);
				cujiagong_choose_grasp2(qr_mes, 1);
				cujiagong_choose_grasp3(qr_mes, 1);
				Mode_Init();
				CAR_MODE = 4;		//�ּӹ� -> ���Ʒ	����ģʽ
				ARM_Action=0;
				break;
			}
			case 5: //���Ʒ���ϲ����
			{
				printf("��е��ģʽ[���Ʒ���²����]");
				place_top_product1(qr_mes);
				place_top_product2(qr_mes);
				place_top_product3(qr_mes);
				Mode_Init();
				CAR_MODE = 5;		//���Ʒ	-> 	ԭ����
				ARM_Action=0;
				break;
			}
			case 6:
			{
				//ɨ���²�����
				printf("��е��ģʽ[ɨ���²�����]");
				scan_block_under();		//��е��ʶ����ɫ����
				delay_ms(100);
				uart2_sendStr("3");		//OVɨ����ɫ
				ARM_Action=0;
				break;
			}
			case 7:	
			{
				//׼����һ��ץȡ�²�
				printf("��е��ģʽ[׼����һ��ץȡ�²�]");
				under_grasp_choose1(way2);		//��е�����
				Mode_Init();
				CAR_MODE = 6;					//����ǰһ��
				ARM_Action=0;
				break;
			}
			case 8:
			{
				//צ�ӱպ�
				printf("��е��ģʽ[צ�ӱպ�]");
				Arm0 = 740;		//��е��ץȡ����
				Mode_Init();
				CAR_MODE = 7;
				ARM_Action=0;
				break;
			}
			case 9:
			{
				printf("��е��ģʽ[��е���ջ�]");
				Arm_back1();									//��е���ջ�
				place_playload1();						//�������ϵ�����
				under_grasp_choose2(way2);		//��е�����
				Mode_Init();
				CAR_MODE = 8;		//����ǰһ��
				ARM_Action=0;
				break;
			}
			case 10:					//׼���ڶ���ץȡ
			{
				printf("��е��ģʽ[׼���ڶ���ץȡ]");
				Arm_back1();		//��е���ջ�
				place_playload2();	//�������ϵ�����2
				under_grasp_choose3(way2);		//��е�����
				Mode_Init();
				CAR_MODE = 8;		//����ǰһ��
				ARM_Action=0;
				break;
			}
			case 11:
			{
				
				Arm_back1();		//��е���ջ�
				place_playload3();	//�������ϵ�����3
				Mode_Init();
				CAR_MODE = 10;
				ARM_Action=0;
				break;
			}
			case 12: 
			{
				//�ڶ��η�������
				First_choose_place1(qr_mes, 2);
				First_choose_place2(qr_mes, 2);
				First_choose_place3(qr_mes, 2);
				//����ץȡ����
				cujiagong_choose_grasp1(qr_mes, 2);
				cujiagong_choose_grasp2(qr_mes, 2);
				cujiagong_choose_grasp3(qr_mes, 2);
				Mode_Init();
				CAR_MODE = 11;		//�ڶ��� �ּӹ� -> ���Ʒ
				ARM_Action=0;
				break;
			}
			case 13: 
			{
				//���Ʒ���²����
				place_under_product1(qr_mes);
				place_under_product2(qr_mes);
				place_under_product3(qr_mes);
				Mode_Init();
				CAR_MODE = 12;									//ȥ������
				ARM_Action=0;
				break;
			}
			default: break;
		}
	
	}
}
