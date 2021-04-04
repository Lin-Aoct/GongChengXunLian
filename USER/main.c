#include "sys.h"


u8 CONTROL_MODE;				//����ģʽ����
u8 IS_USART1_RX_HEAD;		//��־�Ƿ���յ�����ͷ
u8 USART1_RX_BUF[4];		//USART1���ջ���
u8 USART1_RX_DATA[4];		//�洢USART1���յ�������

u8 UART4_RX_DATA;				//�洢UART4���յ�������

u16 led_val = 50;
u8 up_flag = 1;
u32 count_flag;
u8 action_mode = 10;				//����1����ָ�����
u8 u4_action_mode = 0;			//��е�۶���ָ�����
u8 IS_USART1_RX_Success = 0;

u8 TFT_String[2];

u8 ARM_Action = 0;						//��е�۶�������

int	main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//�����ж����ȼ�����
	delay_init(168);						//��ʱ������ʼ��
	//KEY_Init();								//������ʼ��
	//LED_Init();								//LED �Ƴ�ʼ��
	uart_init(115200);					//USART1 ��ʼ��
	//uart4_init(9600);						//UART4 ��ʼ��
	Lcd_Init();									//TFT��Ļ��ʼ��
	Find_IO_Init();							//����ѭ��ģ���ʼ��
	MOTO_GPIO_Config();					//����������ų�ʼ��
	MOTOR_PWM_Init(499, 83);	 	//TIM8 ������� PWM ��ʼ�� 7199 16799
	Encoder_Init_TIM2();				//TIM2 ��ʱ����ʼ������ģʽ
	Encoder_Init_TIM3();				//TIM3 ��ʱ����ʼ������ģʽ
	Encoder_Init_TIM4();				//TIM4 ��ʱ����ʼ������ģʽ
	Encoder_Init_TIM5();				//TIM5 ��ʱ����ʼ������ģʽ
	TIM6_Init(150, 8399);				//TIM6 ���� 15ms ��ʱ�ж�
	TIM7_Init(2000, 8399);			//TIM7 ��ʱ 200ms �ж�

	Car_Stop();
	printf("��ʼ�����\n");
	//u4_printf("u4��ʼ�����");
	
	while(1)
	{
		//USART_SendData(UART4, '3');

//		if(count_flag == 265535) 
//			count_flag = 0;
//		count_flag ++;

		/*
		//�ж��Ƿ��յ���е�۶���
		if(IS_UART4_RX_Success==1) 
		{
			u4_action_mode = UART4_RX_DATA;
			printf("�յ���е��ָ�%c", UART4_RX_DATA);
			IS_UART4_RX_Success = 0;
		}
		//���ݻ�е��ָ��ִ�ж�Ӧ�Ķ���
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
		
		//�ж��Ƿ��յ�����1����
		if(IS_USART1_RX_Success==1) 
		{
			memcpy(USART1_RX_DATA, USART1_RX_BUF, 4*sizeof(u8));	//��ȡ����1����������
			action_mode = USART1_RX_DATA[0];
			printf("�յ�u1ָ�%x", action_mode);
			Lcd_Clear(GRAY0);
			sprintf((u8*)TFT_String, "%d", action_mode);
			Gui_DrawFont_GBK16(60,80,RED,GRAY0, TFT_String);	
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
			case 0x23: USART_SendData(UART4, '3'); break;
			case 0x24: USART_SendData(UART4, '4'); break;
			case 0x25: USART_SendData(UART4, '5'); break;
			default: break;
		}
		action_mode = 100;
		MOTOR_PWM_Out(MOTOR_PWM[0], MOTOR_PWM[1], MOTOR_PWM[2], MOTOR_PWM[3]);
	
	
	
		
		switch(ARM_Action)
		{
			case 0: break;
			case 1: scan_qr_on(); break;		//ɨ��
			case 2: scan_block_top(), top_grasp_choose1(way1), top_grasp_choose2(way1), top_grasp_choose3(way1); break;	//��ɫʶ�� ����ץȡ
		}
		
		
	
	}
}
