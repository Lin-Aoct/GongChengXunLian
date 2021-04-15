#include "uart2.h"


u8 AT = 'N';
static u8 flag = 0 ;

//����һ���ֽ�
void uart2_sendByte(u8 dat)
{
	USART2->DR = dat;
	while((USART2->SR &(1<<7))==0)
	;
}

//�����ַ���
void uart2_sendStr(char *str)
{
	while(*str != '\0')
	{
		uart2_sendByte(*str);
		str++;
	}
}

//����3���ݷ���
void uart3_sendByte(u8 dat)
{
	USART3->DR = dat;
	while((USART3->SR &(1<<7))==0)
	;
}

 void uart3_sendStr(u8 *str)
 {
	 while(*str != '\0')
	{
		uart3_sendByte(*str);
		str++;
	}
	 
 }


static void flag_state(u8 num)
{
	if(num=='A')
		flag = 'A';
	else if(num=='B')
		flag = 'B'; 
	else if(num == 'C')
		flag = 'C';
		return;
	
}

//openmv�źŴ����ֹû�н��յ������

void OPENMV_Cmd(char* s)
{
	while(AT!='Y')
		{
				uart2_sendStr(s);
			delay_ms(150);
		}
		AT = 'N';
	
}

//u16 USART_RX_STA=0; 
//u8 USART_RX_BUF[USART_REC_LEN]; 
//����2�ж�
u8 color = 0;
u8 way1[] = "000";
u8 way2[] = "000";
u8 qr_mes[] = "123+123";

 

void USART2_IRQHandler(void) 
{
	static char res,len = 0,qr_i = 0;

		if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{
			res = USART_ReceiveData(USART2);
			flag_state(res);//��flag��ֵȷ�����ն�ά�뻹��ɫ��λ����
			if(res=='Y')
				AT = 'Y';
			else 
				AT = 'N';
		printf("AT[%c]\n", AT);
		if(flag=='A')//�����ά�����ݽ��ս׶�
		{
			if(!(res=='A'))
			{
				if(res!='\0')
				{
					qr_mes[qr_i] = res;
			    qr_i++;
				}
			}
			if(qr_i == 7)
				qr_i = 0, flag=0, LED0=0, Mode_Init(), CAR_MODE = 2, scan_block_top(), printf("���յ�����˳��[%s]\n", qr_mes), Lcd_Clear(BLACK), GUI_Draw_Long_Font(1, 1, WHITE, BLACK, (u8*)qr_mes);	//TFT ��ʾ˳��
		}
			
	else if(flag =='B')//����ɫ��λ�ý��ս׶�
	{
		
		
	if(!(res=='B'))
			{
				if(res!='\0')
				{
					way1[len] = res;
			    len++;
				}
			}
			if(len >2)
				len= 0, flag=0, LED0=0, Gui_DrawFont_GBK16(1,67,WHITE,BLACK, (u8*)"way1:"), Gui_DrawFont_GBK16(35,67,WHITE,BLACK, way1), printf("���յ��ϲ�ɫ��λ����Ϣ[%s]\n", way1), ARM_Action = 3;	//�����ϲ���ɫ��Ϣ���
		}
		else if(flag=='C')
		{
			if(!(res=='C'))
			{
				if(res!='\0')
				{
					way2[len] = res;
			    len++;
				}
			}
			if(len >2)
				len = 0, flag=0, LED0=0, Gui_DrawFont_GBK16(60,67,WHITE,BLACK, (u8*)"way2:"), Gui_DrawFont_GBK16(95,67,WHITE,BLACK, way2), printf("���յ��²�ɫ��λ����Ϣ[%s]\n", way2), ARM_Action = 7;	//�²���ɫ��Ϣ�������
	}
		
	}
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);			
}



void OPENMV_init(u32 baud)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
 
	//���ڶ�Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2����ΪUSART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3����ΪUSART2
	
	//USART2�˿�����
  //TX
   GPIO_InitStructure.GPIO_Pin = OPENMV_TX_Pin; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(OPENMV_TX_Port, &GPIO_InitStructure);
  //RX
   GPIO_InitStructure.GPIO_Pin = OPENMV_RX_Pin; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(OPENMV_RX_Port, &GPIO_InitStructure);

   //USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = baud;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
	USART_Init(USART2, &USART_InitStructure); //��ʼ������2	
  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�
	USART_ClearFlag(USART2, USART_FLAG_TC);

	//Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}
