#ifndef __UART4_H
#define __UART4_H
#include "sys.h" 
#include <stdio.h>


#define UART4_REC_LEN		200  	//�����������ֽ��� 200
#define EN_USART4_RX 			1			//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  UART4_RX_BUF[UART4_REC_LEN]; //���ջ���,���UART4_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 UART4_RX_STA;         				//����״̬���	

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart4_init(u32 bound);
void u4_printf(char* fmt,...);


#endif
