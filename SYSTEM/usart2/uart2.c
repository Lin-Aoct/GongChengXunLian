#include "uart2.h"


static u8 flag = 0 ;

//发送一个字节
void uart2_sendByte(u8 dat)
{
	USART2->DR = dat;
	while((USART2->SR &(1<<7))==0)
	;
}

//发送字符串
void uart2_sendStr(char *str)
{
	while(*str != '\0')
	{
		uart2_sendByte(*str);
		str++;
	}
}

//串口3数据发送
void uart3_sendByte(u8 dat)
{
	USART3->DR = dat;
	while((USART3->SR &(1<<7))==0)
	;
}
 void uart3_sendStr(char *str)
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
	else 
		return;
	
}


//u16 USART_RX_STA=0; 
//u8 USART_RX_BUF[USART_REC_LEN]; 
//串口2中断
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
			flag_state(res);									//给flag赋值确定接收二维码还是色块位置信息
		if(flag=='A')												//进入二维码数据接收阶段
		{
			if(!(res=='A'))
			{
				Mode_Init();
				CAR_MODE = 2;		//小车二维码 -> 原料区
				if(res!='\0')
				{
					qr_mes[qr_i] = res;
			    qr_i++;
				}
			}
			if(qr_i == 7)
				qr_i = 0, GUI_Draw_Long_Font(1, 1, RED, GRAY0, (u8*)qr_mes);	//TFT 显示顺序
		}
			
	else if(flag =='B')//进入色块位置接收阶段
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
				len= 0, ARM_Action = 3;	//接收颜色信息完成
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
				len = 0, ARM_Action = 7;	//第二次接收颜色信息完成
	}
		
	}
			USART_ClearITPendingBit(USART2,USART_IT_RXNE);			
	}


void OPENMV_init(u32 baud)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
 
	//串口对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2复用为USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3复用为USART2
	
	//USART2端口配置
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

   //USART2 初始化设置
	USART_InitStructure.USART_BaudRate = baud;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  
	USART_Init(USART2, &USART_InitStructure); //初始化串口2	
  USART_Cmd(USART2, ENABLE);  //使能串口2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断
	USART_ClearFlag(USART2, USART_FLAG_TC);

	//Usart2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、


}




