#include "Vcan_Oscilloscope.h"
#include "stm32f4xx_usart.h"

void send_char(uint8_t dat)
{
   USART3->DR = dat;
	while((USART3->SR &(1<<7))==0)
	;
}

void send_putbuff (uint8_t *buff, uint32_t len)
{
    while(len--)
    {
         send_char(*buff);
         buff++;
    }
}


void vcan_sendware(uint8_t *wareaddr, uint32_t waresize)
{ 
    uint8_t cmdf[2] = {0x03, 0xfc};
    uint8_t cmdr[2] = {0xfc, 0x03};
   
    send_putbuff(cmdf,sizeof(cmdf));
    send_putbuff(wareaddr,waresize);
    send_putbuff(cmdr,sizeof(cmdr));
		//printf("123");
		uart3_sendStr("1");
}













#if 0

void vcan_sendware(u8 *wareaddr, u8 waresize)
{
#define CMD_WARE     3
    u8 cmdf[2] = {CMD_WARE, ~CMD_WARE};    //串口调试 使用的前命令
    u8 cmdr[2] = {~CMD_WARE, CMD_WARE};    //串口调试 使用的后命令

    uart3_sendStr(cmdf);    //先发送前命令
    uart3_sendStr(wareaddr);    //发送数据
    uart3_sendStr(cmdr);    //发送后命令

}

void Vcan_Oscilloscope(u16 data1, u16 data2, u16 data3, u16 data4, u16 data5, u16 data6, u16 data7, u16 data8)
{
	u16 var[8];
	var[0] = data1;
	var[1] = data2;
	var[2] = data3;
	var[3] = data4;
//	var[4] = data5;
//	var[5] = data6;
//	var[6] = data7;
//	var[7] = data8;
  uart3_sendStr((u8 *)var);
}

#endif
