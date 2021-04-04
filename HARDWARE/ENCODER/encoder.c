#include "encoder.h"

int ENCODER_DATA[4];		//编码器读数

/*
 *         M1         |           M2          |          M3         |          M4        
 *PC.0--A01 PA.1--A02 | PC.13--A01 PC.15--A02 | PC.1--A01 PC.3--A02 | PC.5--A01 PB.1--A02
 *
*/


/*
*===================================================================
*		说明：单位时间读取编码器计数
*		参数：定时器
*		返回：定时器计数值
*===================================================================
*/
int Read_Encoder(u8 TIMX)
{
	int Encoder_TIM;    
	switch(TIMX)
	{
		case 2:  Encoder_TIM = (short)TIM2 -> CNT;  TIM2 -> CNT=0; break;	
		case 3:  Encoder_TIM = -(short)TIM3 -> CNT; TIM3 -> CNT=0; break;	
		case 4:  Encoder_TIM = (short)TIM4 -> CNT;  TIM4 -> CNT=0; break;	
		case 5:  Encoder_TIM = (short)TIM5 -> CNT;  TIM5 -> CNT=0; break;	
		default:  Encoder_TIM=0;
	}
	return Encoder_TIM;
}
