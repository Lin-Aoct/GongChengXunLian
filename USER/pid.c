#include "pid.h"


float Balance_Kp = 25.0, Balance_Ki = 0.00, Balance_Kd = 100.0;		//X 轴位置环 PID相关参数

float Y_side_Kp = 20.0, Y_side_Ki = 0.0, Y_side_Kd = 200.0;				//Y 轴位置环 PID相关参数

float speed_Kp = -10.0, speed_Ki = 0.0, speed_Kd = 50.0;					//PID相关参数

float Y_speed_Kp = 8.0, Y_speed_Ki = 0.0, Y_speed_Kd = -65.0;					//PID相关参数

u8 target = 0, speed_max = 100;

/**************************************************************************
函数功能：X方向平衡PD控制
入口参数：角度,
返回  值：直立控制PWM
**************************************************************************/
int balanceX(float Angle)
{
	float Differential, Bias;//定义差分变量和偏差
	static float Last_Bias, Integration, Balance_Integration, Flag_Target;  //上一次的偏差值
	int balance;											//返回值变量

	Bias = Angle - target;  					//求出平衡的中值
	Differential = Bias - Last_Bias;  //求得偏差的变化率	 
	if(++Flag_Target > 30) 						//错频处理积分控制
	{
		Flag_Target = 0;
		Integration += Bias;  // 检测到小球且舵机使能则积分
		if(Integration<-500) Integration = -500;	//积分限幅
		if(Integration>500)  Integration = 500;	
		Balance_Integration = Integration * Balance_Ki;  //积分控制
	}		
	balance = (Balance_Kp * Bias)/100 + Balance_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  	//保存上一次的偏差
	//printf("%0.1f,%0.1f", (Balance_Kp * Bias)/100, Bias);
	return balance;  		//返回值
}
/**************************************************************************
函数功能：Y方向平衡PD控制
入口参数：角度
返回  值：直立控制PWM
**************************************************************************/
int balanceY(float Angle)
{  
	float Differential,Bias;		//定义差分变量和偏差
	static float Last_Bias,Integration,Balance_Integration,Flag_Target;  //上一次的偏差值
	int balance;								//返回值变量

	Bias = Angle - target;  					//求出平衡的中值 
	Differential = Bias - Last_Bias;  //求得偏差的变化率	 
	if(++Flag_Target > 30) 						//错频处理积分控制
	{
		Flag_Target = 0;
		Integration += Bias;  // 积分
		if(Integration<-500) Integration = -500;	//积分限幅
		if(Integration>500)  Integration = 500;	
		Balance_Integration = Integration * Y_side_Ki;   //积分控制
	}		
	balance = (Y_side_Kp * Bias)/100 + Y_side_Kd*Differential/10 + Balance_Integration;   //计算控制的PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差
	return balance;  //返回值
}


/**************************************************************************
函数功能：X方向速度环PD控制
入口参数：速度
返回  值：直立控制PWM
**************************************************************************/
int Speed_X(float side)
{
	float Differential, Bias;		//定义差分变量和偏差
	static float Last_Bias, Integration, Balance_Integration, last_side;  //上一次的偏差值
	int balance;								//平衡的返回值
	u8 speed_now;
	
	speed_now = side - last_side;
	Bias = speed_now - speed_max;  		//求出速度偏差

	Differential = Bias - Last_Bias;  //求得偏差的变化率	 

	Balance_Integration = Integration * speed_Ki;   //积分控制
	
	balance = (speed_Kp * Bias)/100 + speed_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差
	last_side = side;
	//printf("%0.1f,%0.1f", (Balance_Kp * Bias)/100, Bias);
	return balance;  //返回值
}

/**************************************************************************
函数功能：Y方向速度环PD控制
入口参数：速度
返回  值：直立控制PWM
**************************************************************************/
int Speed_Y(float side)
{  
	float Differential, Bias;		//定义差分变量和偏差
	static float Last_Bias, Integration, Balance_Integration, last_side;  //上一次的偏差值
	int balance;								//平衡的返回值
	u8 speed_now;
	
	speed_now = side - last_side;
	Bias = speed_now - speed_max;  		//求出平衡的角度中值

	Differential = Bias - Last_Bias;  //求得偏差的变化率	 
	
	Balance_Integration = Integration * Y_speed_Ki;   //积分控制

	balance = (Y_speed_Kp * Bias)/100 + Y_speed_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差
	last_side = side;
	return balance;  //返回值
}
