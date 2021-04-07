#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_
#include "headfiles.h"



#define BLUE_TX_PORT    GPIOD
#define BLUE_TX_Pin			GPIO_Pin_8
#define BLUE_RX_PORT    GPIOD
#define BLUE_RX_Pin     GPIO_Pin_9

extern u8 tx,tem;



extern void bluetooth_init(u32 baud);






#endif


