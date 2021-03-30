#include "uart4.h"	  


//#if EN_UART4_RX   //如果使能了接收
//串口4中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 UART4_RX_BUF[USART_REC_LEN];     //接收缓冲,最大UART4_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 UART4_RX_STA=0;       //接收状态标记	  
u16 UART4_TX_BUF[100];


u8 IS_UART4_RX_Success;		//标志是否接收成功

void uart4_init(u32 bound)
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);	//使能 UART4 AFIO 时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//使能 UART4 GPIOA 时钟
	
	//UART4_TX 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 				//PC.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//复用推挽输出
  GPIO_Init(GPIOC, &GPIO_InitStructure);						//初始化GPIOC.10
   
  //UART4_RX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;						//PC.11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
  GPIO_Init(GPIOC, &GPIO_InitStructure);								//初始化GPIOC.11

  //UART4 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
  //USART 配置
	USART_InitStructure.USART_BaudRate = bound;									//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;					//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;									//收发模式

  USART_Init(UART4, &USART_InitStructure); 			//初始化串口4
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	//开启串口接受中断
  USART_Cmd(UART4, ENABLE);                    	//使能串口4
}


/*
*===================================================================
*		说明：串口4中断服务程序
*		参数：无
*		返回：无
*===================================================================
*/
void UART4_IRQHandler(void)
{
	u8 Res;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res = USART_ReceiveData(UART4);		//读取接收到的数据
		UART4_RX_DATA = Res;
		printf("u4中断：%c", UART4_RX_DATA);
		IS_UART4_RX_Success = 1;
		if((UART4_RX_STA&0x8000)==0)			//接收未完成
		{
			if(UART4_RX_STA&0x4000)				//接收到了0x0d
			{
				if(Res!=0x0a)UART4_RX_STA=0;	//接收错误,重新开始
				else UART4_RX_STA|=0x8000;		//接收完成了 
			}
			else //还没收到0x0D
			{	
				if(Res==0x0d)UART4_RX_STA|=0x4000;
				else
				{
					UART4_RX_BUF[UART4_RX_STA&0X3FFF]=Res ;						//按位与 与前14位得到有效字节长度
					UART4_RX_STA++;
					if(UART4_RX_STA>(USART_REC_LEN-1))UART4_RX_STA=0;	//接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
	} 
}


/*
*===================================================================
*		说明：串口4发送数据函数
*		参数：ch：要发送的字符串指针
*		返回：无
*===================================================================
*/
void u4_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)UART4_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)UART4_TX_BUF);		//此次发送数据的长度
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(UART4, USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(UART4, UART4_TX_BUF[j]); 
	} 
}
