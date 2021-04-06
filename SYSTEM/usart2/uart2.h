#ifndef _UART2_H_
#define _UART2_H_

#include "headfiles.h"
#define USART_REC_LEN  			200  	

//���ű仯��ע���޸�ʱ�ӵ�����
#define OPENMV_TX_Port      GPIOA
#define OPENMV_TX_Pin				GPIO_Pin_2
#define OPENMV_RX_Port			GPIOA
#define OPENMV_RX_Pin       GPIO_Pin_3

//extern u8  USART_RX_BUF0[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
//extern u16 USART_RX_STA0;  
extern u8 color;//
extern u8 way2[];
extern u8 way1[];
extern u8 redx[];
extern u8 qr_mes[];
extern u8 flag;


extern void OPENMV_init(u32 baud);
extern void uart2_sendByte(u8 dat);
extern void uart2_sendStr(char *str);
extern void uart3_sendByte(u8 dat);
extern void uart3_sendStr(char *str);



#endif

