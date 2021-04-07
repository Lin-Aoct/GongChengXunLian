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

int	main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//�����ж����ȼ�����
	delay_init(168);						//��ʱ������ʼ��
	//KEY_Init();								//������ʼ��
	//LED_Init();								//LED �Ƴ�ʼ��
	uart_init(115200);					//USART1 ��ʼ��
	
	//OPENMV_init(9600);					//OPENMV USART2 ��ʼ��
	//bluetooth_init(115200);			//���� USART3 ��ʼ��
	//RobotArm_Pwm_init();				//��е�۳�ʼ��
	//scan_qr_on();								//��е�۱���ɨ�붯��

	Lcd_Init();									//TFT��Ļ��ʼ��
	Find_IO_Init();							//����ѭ��ģ���ʼ��
	MOTO_GPIO_Config();					//����������ų�ʼ��
	MOTOR_PWM_Init(499, 83);	 	//TIM8 ������� PWM ��ʼ�� 7199 16799
	Encoder_Init_TIM2();				//TIM2 ��ʱ����ʼ������ģʽ
	Encoder_Init_TIM3();				//TIM3 ��ʱ����ʼ������ģʽ
	Encoder_Init_TIM4();				//TIM4 ��ʱ����ʼ������ģʽ
	Encoder_Init_TIM5();				//TIM5 ��ʱ����ʼ������ģʽ
	TIM6_Init(150, 8399);				//TIM6 ���� 15ms ��ʱ�ж�
	//TIM7_Init(2000, 8399);			//TIM7 ��ʱ 200ms �ж�

	Car_Stop();
	printf("��ʼ�����\n");
	GUI_Draw_Long_Font(1, 1, RED, GRAY0, (u8*)"123+321");
	
	while(1)
	{
		//Lcd_Clear(GRAY0);

		//delay_ms(1000);
		//Gui_DrawFont_GBK16(0,80,RED,GRAY0, qr_mes);	

//		if(count_flag == 265535) 
//			count_flag = 0;
//		count_flag ++;

		
		//�ж��Ƿ��յ�����1����
		if(IS_USART1_RX_Success==1) 
		{
			memcpy(USART1_RX_DATA, USART1_RX_BUF, 4*sizeof(u8));	//��ȡ����1����������
			u1_action_mode = USART1_RX_DATA[0];
			printf("�յ�u1ָ�%x", u1_action_mode);
			//Lcd_Clear(GRAY0);
			//sprintf((u8*)TFT_String, "%d", u1_action_mode);
			//Gui_DrawFont_GBK16(60,80,RED,GRAY0, TFT_String);	
			IS_USART1_RX_Success = 0;
		}
		switch(u1_action_mode)
		{
			case 0x0: CAR_MODE = 0; Car_Go(); break;
			case 0x1: CAR_MODE = 0; Car_Back(); break;
			case 0x2: CAR_MODE = 0; Car_Go_Left(); break;
			case 0x3: CAR_MODE = 0; Car_Go_Right(); break;
			case 0x4: CAR_MODE = 0; Car_Left_Front(); break;
			case 0x5: CAR_MODE = 0; Car_Right_Front(); break;
			case 0x6: CAR_MODE = 0; Car_Raw_Left(); break;
			case 0x7: CAR_MODE = 0; Car_Raw_Right(); break;
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
			case 0x18: break;
			case 0x19: break;
			case 0x20: break;
			case 0x21: speed_target+=10; break;
			case 0x22: speed_target-=10; break;
			case 0x23: USART_SendData(USART2, '1'); break;
			case 0x24: USART_SendData(USART2, '2'); break;
			case 0x25: USART_SendData(USART2, '3'); break;
			default: break;
		}
		u1_action_mode = 100;
		MOTOR_PWM_Out(MOTOR_PWM[0], MOTOR_PWM[1], MOTOR_PWM[2], MOTOR_PWM[3]);
	
	
		//��е�۶����ж�
		switch(ARM_Action)
		{
			case 0: break;
			case 1: scan_qr_on(); uart2_sendStr("1"); break;		//ɨ������ ����OVɨ��
			case 2: scan_block_top(); uart2_sendStr("2");break;	//��ɫʶ��	����OVʶ���ϲ���ɫ
			case 3: top_grasp_choose1(way1); top_grasp_choose2(way1); top_grasp_choose3(way1); CAR_MODE = 3; break; 	//��е��ץȡɫ��
			case 4: 
			{
				//��һ�η�������
				First_choose_place1(qr_mes, 1);
				First_choose_place2(qr_mes, 1);
				First_choose_place3(qr_mes, 1);
				//����ץȡ����
				cujiagong_choose_grasp1(qr_mes, 1);
				cujiagong_choose_grasp2(qr_mes, 1);
				cujiagong_choose_grasp3(qr_mes, 1);
				CAR_MODE = 5;		//�ּӹ� -> ���Ʒ
				break;
			}
			case 5: //���Ʒ���ϲ����
			{
				place_top_product1(qr_mes);
				place_top_product2(qr_mes);
				place_top_product3(qr_mes);
				CAR_MODE = 7;
				break;
			}
			case 6:
			{
				//ɨ���²�����
				scan_block_under();		//��е��ʶ����ɫ����
				delay_ms(100);
				uart2_sendStr("3");		//OVɨ����ɫ
				break;
			}
			case 7:	//׼����һ��ץȡ�²�
			{
				under_grasp_choose1(way2);		//��е�����
				CAR_MODE = 8;
				break;
			}
			case 8:	//צ�ӱպ�
			{
				Arm0 = 740;		//��е��ץȡ����
				CAR_MODE = 9;
				break;
			}
			case 9:
			{
				Arm_back1();		//��е���ջ�
				place_playload1();	//�������ϵ�����
				under_grasp_choose2(way2);		//��е�����
				CAR_MODE = 8;		//����ǰһ��
				break;
			}
			case 10:					//׼���ڶ���ץȡ
			{
				Arm_back1();		//��е���ջ�
				place_playload2();	//�������ϵ�����2
				under_grasp_choose3(way2);		//��е�����
				CAR_MODE = 8;		//����ǰһ��
				break;
			}
			case 11:
			{
				Arm_back1();		//��е���ջ�
				place_playload3();	//�������ϵ�����3
				CAR_MODE = 10;
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
				CAR_MODE = 11;		//�ڶ��� �ּӹ� -> ���Ʒ
				break;
			}
			case 13: 
			{
				//���Ʒ���²����
				place_under_product1(qr_mes);
				place_under_product2(qr_mes);
				place_under_product3(qr_mes);
				CAR_MODE = 12;									//ȥ����ȥ
				break;
			}
			default: break;
		}
		
		
		
		
		
		/*
		//�ж��Ƿ��յ���е�۶���
		if(IS_UART4_RX_Success==1) 
		{
			car_u1_action_mode = UART4_RX_DATA;
			printf("�յ���е��ָ�%c", UART4_RX_DATA);
			IS_UART4_RX_Success = 0;
		}
		//���ݻ�е��ָ��ִ�ж�Ӧ�Ķ���
		switch(car_u1_action_mode)
		{
			case '1': Mode_Init(), Stop_Find(), CAR_MODE = 2; break;
			case '2': Mode_Init(), Stop_Find(), CAR_MODE = 3; break;
			case '3': Mode_Init(), Stop_Find(), CAR_MODE = 4; break;
			case '4': Mode_Init(), Stop_Find(), CAR_MODE = 5; break;
			case '5': Mode_Init(), Stop_Find(), CAR_MODE = 6; break;
			case '6': Mode_Init(), Stop_Find(), CAR_MODE = 7; break;
			default: break;
		}
		car_u1_action_mode = 100;
		*/
	
	}
}
