#include "uart4.h"	  


//#if EN_UART4_RX   //���ʹ���˽���
//����4�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 UART4_RX_BUF[USART_REC_LEN];     //���ջ���,���UART4_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 UART4_RX_STA=0;       //����״̬���	  
u16 UART4_TX_BUF[100];


u8 IS_UART4_RX_Success;		//��־�Ƿ���ճɹ�

void uart4_init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);	//ʹ�� UART4 AFIO ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//ʹ�� UART4 GPIOA ʱ��
	
	//UART4_TX 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 				//PC.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//�����������
  GPIO_Init(GPIOC, &GPIO_InitStructure);						//��ʼ��GPIOC.10
   
  //UART4_RX
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;						//PC.11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
  GPIO_Init(GPIOC, &GPIO_InitStructure);								//��ʼ��GPIOC.11

  //UART4 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
  //USART ����
	USART_InitStructure.USART_BaudRate = bound;									//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;					//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;									//�շ�ģʽ

  USART_Init(UART4, &USART_InitStructure); 			//��ʼ������4
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	//�������ڽ����ж�
  USART_Cmd(UART4, ENABLE);                    	//ʹ�ܴ���4
}


/*
*===================================================================
*		˵��������4�жϷ������
*		��������
*		���أ���
*===================================================================
*/
void UART4_IRQHandler(void)
{
	u8 Res;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res = USART_ReceiveData(UART4);		//��ȡ���յ�������
		UART4_RX_DATA = Res;
		printf("u4�жϣ�%c", UART4_RX_DATA);
		IS_UART4_RX_Success = 1;
		if((UART4_RX_STA&0x8000)==0)			//����δ���
		{
			if(UART4_RX_STA&0x4000)				//���յ���0x0d
			{
				if(Res!=0x0a)UART4_RX_STA=0;	//���մ���,���¿�ʼ
				else UART4_RX_STA|=0x8000;		//��������� 
			}
			else //��û�յ�0x0D
			{	
				if(Res==0x0d)UART4_RX_STA|=0x4000;
				else
				{
					UART4_RX_BUF[UART4_RX_STA&0X3FFF]=Res ;						//��λ�� ��ǰ14λ�õ���Ч�ֽڳ���
					UART4_RX_STA++;
					if(UART4_RX_STA>(USART_REC_LEN-1))UART4_RX_STA=0;	//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
	} 
}


/*
*===================================================================
*		˵��������4�������ݺ���
*		������ch��Ҫ���͵��ַ���ָ��
*		���أ���
*===================================================================
*/
void u4_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)UART4_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)UART4_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(UART4, USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(UART4, UART4_TX_BUF[j]); 
	} 
}
