#include "sys.h"


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);//初始化串口波特率为115200
	//TIM14_PWM_Init(500-1,84-1);	//84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.     
	printf("done");
	while(1) //实现比较值从0-300递增，到300后从300-0递减，循环
	{
		//QDTFT_Test_Demo(); 
		delay_ms(1000);
		printf("out");
	}
}
