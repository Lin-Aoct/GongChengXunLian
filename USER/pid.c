#include "pid.h"


float Balance_Kp = 25.0, Balance_Ki = 0.00, Balance_Kd = 100.0;		//X 轴位置环 PID相关参数

float Y_side_Kp = 20.0, Y_side_Ki = 0.0, Y_side_Kd = 200.0;				//Y 轴位置环 PID相关参数


float LF_Speed_Kp = -340.5, LF_Speed_Ki = 1.3, LF_Speed_Kd = 0.0;					//PID相关参数
float LB_Speed_Kp = -240.5, LB_Speed_Ki = 0.3, LB_Speed_Kd = 1.0;					//PID相关参数
float RF_Speed_Kp = -240.5, RF_Speed_Ki = 0.3, RF_Speed_Kd = 1.0;					//PID相关参数
float RB_Speed_Kp = -240.5, RB_Speed_Ki = 0.3, RB_Speed_Kd = 1.0;					//PID相关参数

float speed_target = 40.0, speed_max = 600.0;

u8 target = 0;

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
函数功能：左前速度环PD控制
入口参数：速度
返回  值：控制PWM
**************************************************************************/
int PID_Speed_Left_Front(float speed)
{
	float Differential, Bias;		//定义差分变量和偏差
	static float Last_Bias, Integration, Balance_Integration;  //上一次的偏差值
	int balance;								//平衡的返回值

	Bias = speed - speed_target;  		//求出速度偏差

	Differential = Bias - Last_Bias;  //求得偏差的变化率	 

	Balance_Integration = Integration * LF_Speed_Ki;   //积分控制
	
	balance = (LF_Speed_Kp * Bias)/10 + LF_Speed_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差
	//printf("%d", speed);
	return balance;  //返回值
}

/**************************************************************************
函数功能：左后速度环PD控制
入口参数：速度
返回  值：控制PWM
**************************************************************************/
int PID_Speed_Left_Behind(float speed)
{
	float Differential, Bias;		//定义差分变量和偏差
	static float Last_Bias, Integration, Balance_Integration;  //上一次的偏差值
	int balance;								//平衡的返回值

	Bias = speed - speed_target;  		//求出速度偏差

	Differential = Bias - Last_Bias;  //求得偏差的变化率	 

	Balance_Integration = Integration * LB_Speed_Ki;   //积分控制
	
	balance = (LB_Speed_Kp * Bias)/100 + LB_Speed_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差

	return balance;  //返回值
}

/**************************************************************************
函数功能：右前速度环PD控制
入口参数：速度
返回  值：控制PWM
**************************************************************************/
int PID_Speed_Right_Front(float speed)
{
	float Differential, Bias;		//定义差分变量和偏差
	static float Last_Bias, Integration, Balance_Integration;  //上一次的偏差值
	int balance;								//平衡的返回值

	Bias = speed - speed_target;  		//求出速度偏差

	Differential = Bias - Last_Bias;  //求得偏差的变化率	 

	Balance_Integration = Integration * RF_Speed_Ki;   //积分控制
	
	balance = (RF_Speed_Kp * Bias)/100 + RF_Speed_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差

	return balance;  //返回值
}

/**************************************************************************
函数功能：右后速度环PD控制
入口参数：速度
返回  值：控制PWM
**************************************************************************/
int PID_Speed_Right_Behind(float speed)
{
	float Differential, Bias;		//定义差分变量和偏差
	static float Last_Bias, Integration, Balance_Integration;  //上一次的偏差值
	int balance;								//平衡的返回值

	Bias = speed - speed_target;  		//求出速度偏差

	Differential = Bias - Last_Bias;  //求得偏差的变化率	 

	Balance_Integration = Integration * RB_Speed_Ki;   //积分控制
	
	balance = (RB_Speed_Kp * Bias)/100 + RB_Speed_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差

	return balance;  //返回值
}
