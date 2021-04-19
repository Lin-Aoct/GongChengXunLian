#include "sys.h"


u8 IS_USART1_RX_HEAD;		//��־�Ƿ���յ�����ͷ
u8 IS_USART1_RX_Success = 0;
u8 USART1_RX_BUF[4];		//USART1���ջ���
u8 USART1_RX_DATA[4];		//�洢USART1���յ�������

u8 UART4_RX_DATA;				//�洢UART4���յ�������

u32 count_flag;								//Debug
u8 u1_action_mode = 10;				//����1����ָ�����

u8 ARM_Action = 0;						//��е�۶�������
u8 is_start = 0;							//��־�Ƿ��ѿ�ʼ
int motor_current_pwm[4];

int	main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//�����ж����ȼ�����
	delay_init(168);						//��ʱ������ʼ��
	uart_init(115200);					//USART1 ��ʼ��
	
	OPENMV_init(9600);					//OPENMV USART2 ��ʼ��
	bluetooth_init(115200);			//���� USART3 ��ʼ��
	RobotArm_Pwm_init();				//��е�۳�ʼ��
	scan_qr_on();								//��е�۱���ɨ�붯��

	KEY_Init();									//������ʼ��
	//LED_Init();									//LED �Ƴ�ʼ��
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
	//GUI_Draw_Long_Font(1, 1, WHITE, BLACK, (u8*)qr_mes);
	printf("��ʼ�����\n");
	
	while(1)
	{
		//vcan_sendware((uint8_t *)ENCODER_DATA, sizeof(ENCODER_DATA));		//���������η���

//		if(count_flag == 65535) 
//			count_flag = 0,Find_Test();
//		count_flag ++;

		//�жϰ����Ƿ��� һ������
		if(KEY_Scan(0) == 1 && is_start==0)
			Mode_Init(), Stop_Find(), CAR_MODE = 1, is_start=1;

		
		//�ж��Ƿ��յ�����1����
		if(IS_USART1_RX_Success==1) 
		{
			memcpy(USART1_RX_DATA, USART1_RX_BUF, 4*sizeof(u8));	//��ȡ����1����������
			u1_action_mode = USART1_RX_DATA[0];
			printf("�յ�u1ָ�%x\n", u1_action_mode);
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
			//���ܲ���
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
			//����
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
			
			case 0x71: is_car_debug_mode=1; break;
			case 0x72: is_car_debug_mode=0; break;
			default: break;
		}
		u1_action_mode = 100;

		
		//��е�۶����ж�
		switch(ARM_Action)
		{
			case 0: break;
			case 1: OPENMV_Cmd("1");while(qr_mes[6]=='0'){Arm4-=17;delay_ms(200);Arm4 +=17;delay_ms(200);};printf("��е��ģʽ[ɨ��]\n");ARM_Action=0; break;		//ɨ������ ����OVɨ��  Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"ɨ��"); 
			case 2: printf("OV��2\n"),OPENMV_Cmd("2"); printf("��е��ģʽ[OVɨ���ϲ�]\n"); ARM_Action=0; break;	//��ɫʶ��	����OVʶ���ϲ���ɫ Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"OVɨ���ϲ�"); 
			case 3: Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"ץȡ�ϲ�"); top_grasp_choose1(way1); top_grasp_choose2(way1); top_grasp_choose3(way1); Mode_Init(); CAR_MODE = 3; finish_top_grasp_status(); ARM_Action=0; break; 	//��е��ץȡ����
			case 4: 
			{
				printf("��е��ģʽ[�ּӹ������� �ϲ�ģʽ]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//��������
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"�ּӹ����ϲ����");
				//��һ�η�������
				First_choose_place1(qr_mes, 1);
				First_choose_place2(qr_mes, 1);
				First_choose_place3(qr_mes, 1);
				//����ץȡ����
				printf("��е��ģʽ[�ּӹ�������ץȡ���� �ϲ�ģʽ]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//��������
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"�ּӹ�������ץȡ");
				cujiagong_choose_grasp1(qr_mes, 1);
				cujiagong_choose_grasp2(qr_mes, 1);
				cujiagong_choose_grasp3(qr_mes, 1);
				Mode_Init();
				CAR_MODE = 4;		//�ּӹ� -> ���Ʒ	����ģʽ
				finish_rough_status();
				ARM_Action=0;
				break;
			}
			case 5: //���Ʒ���ϲ����
			{
				printf("��е��ģʽ[���Ʒ���ϲ����]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//��������
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"���Ʒ���ϲ����");
				place_top_product1(qr_mes);
				place_top_product2(qr_mes);
				place_top_product3(qr_mes);
				Mode_Init();
				CAR_MODE = 5;					//���Ʒ	-> 	ԭ����
				finish_top_product_status();		//��е��ʶ����ɫ����
				ARM_Action=0;
				break;
			}
			case 6:
			{
				//ɨ���²�����
				printf("��е��ģʽ[ɨ���²�����]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//��������
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"ɨ���²�����");
				delay_ms(100);
				LED0=1;
				OPENMV_Cmd("3");			//OVɨ����ɫ
				ARM_Action=0;
				break;
			}
			case 7:	
			{
				//׼����һ��ץȡ�²�
				printf("��е��ģʽ[׼����һ��ץȡ�²�]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//��������
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"��һ��ץȡ�²�");
				under_grasp_choose1(way2);	//��һ�λ�е�����
				Mode_Init();
				CAR_MODE = 6;								//����һ��ǰ��һ��
				ARM_Action=0;
				break;
			}
			case 8:
			{
				//��һ��צ�ӱպ�
				printf("��е��ģʽ[��һ��צ�ӱպ�]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//��������
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"צ�ӱպ�1");
				Arm0 = 740;					//��е��ץȡ����
				Mode_Init();
				CAR_MODE = 7;				//����һ�κ���һ��
				ARM_Action=0;
				break;
			}
			case 9:
			{
				printf("��е��ģʽ[��е�۵�һ���ջ�]\n");
				Arm4 -= 8;delay_ms(50); 
				under_Arm_back();
				//Arm_back1();									//��е�۵�һ���ջ�
				place_playload1();						//�������ϵ�����
				under_grasp_choose2(way2);		//��е�����
				Mode_Init();
				CAR_MODE = 8;									//���ڶ�����ǰһ��
				ARM_Action=0;
				break;
			}
			case 10:
			{
				//�ڶ���צ�ӱպ�
				printf("��е��ģʽ[�ڶ���צ�ӱպ�]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//��������
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"צ�ӱպ�2");
				Arm0 = 740;				//��е��ץȡ����
				Mode_Init();
				CAR_MODE = 9;			//���ڶ��κ���һ��
				ARM_Action=0;
				break;
			}
			case 11:					//׼��������ץȡ
			{
				printf("��е��ģʽ[׼��������ץȡ]\n");
				under_Arm_back();
				//Arm_back1();				//��е�۵ڶ����ջ�
				place_playload2();	//�������ϵ�����2
				under_grasp_choose3(way2);		//��е�۵��������
				Mode_Init();
				CAR_MODE = 10;		//����������ǰһ��
				ARM_Action=0;
				break;
			}
			case 12:
			{
				//������צ�ӱպ�
				printf("��е��ģʽ[������צ�ӱպ�]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//��������
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"צ�ӱպ�3");
				Arm0 = 740;				//��е��ץȡ����
				
				Mode_Init();
				CAR_MODE = 11;		//������һ��
				
				ARM_Action=0;
				break;
			}
			case 13:
			{
				printf("��е��ģʽ[�²�ץȡ�����δ��]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//��������
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"�²����3");
				under_Arm_back();
				//Arm_back1();				//��е�۵������ջ�
				place_playload3();	//�������ϵ�����3
				Mode_Init();
				CAR_MODE = 12;			//��ǰ���ּӹ��� 
				finish_under_grasp_status();
				ARM_Action=0;
				break;
			}
			case 14: 
			{
				//�ӹ����������� �ײ�ģʽ
				printf("��е��ģʽ[�ּӹ����������� �²�ģʽ]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//��������
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"�ӹ����²����");
				First_choose_place1(qr_mes, 2);
				First_choose_place2(qr_mes, 2);
				First_choose_place3(qr_mes, 2);
				//�ӹ�������ץȡ���� �ײ�ģʽ
				printf("��е��ģʽ[�ּӹ�������ץȡ���� �²�ģʽ]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//��������
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"�ӹ����²�ץȡ");
				cujiagong_choose_grasp1(qr_mes, 2);
				cujiagong_choose_grasp2(qr_mes, 2);
				cujiagong_choose_grasp3(qr_mes, 2);
				Mode_Init();
				CAR_MODE = 13;		//�ּӹ� -> ���Ʒ	�²�ģʽ
				finish_rough_status();
				ARM_Action=0;
				break;
			}
			case 15: 
			{
				//���Ʒ������ �²�ģʽ
				printf("��е��ģʽ[���Ʒ���������� �²�ģʽ]\n");
				Lcd_Clear_Part(2,100,180,32, BLACK);					//��������
				Gui_DrawFont_GBK16(2,100,WHITE,BLACK, (u8*)"���Ʒ���²����");
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
				CAR_MODE = 14;		//ȥ������
				ARM_Action=0;
				is_start = 0;			//��־��ͣ��
				break;
			}
			default: break;
		}
	}
}
