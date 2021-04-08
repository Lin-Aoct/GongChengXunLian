#include "pid.h"


float Balance_Kp = 25.0, Balance_Ki = 0.00, Balance_Kd = 100.0;		//X 轴位置环 PID相关参数

float Y_side_Kp = 20.0, Y_side_Ki = 0.0, Y_side_Kd = 200.0;				//Y 轴位置环 PID相关参数


float LF_Speed_Kp = -115.5, LF_Speed_Ki = 0.1, LF_Speed_Kd = -2.0;					//PID相关参数
float LB_Speed_Kp = -135.5, LB_Speed_Ki = 0.1, LB_Speed_Kd = -2.0;					//PID相关参数
float RF_Speed_Kp = -125.5, RF_Speed_Ki = 0.1, RF_Speed_Kd = -2.0;					//PID相关参数
float RB_Speed_Kp = -125.5, RB_Speed_Ki = 0.1, RB_Speed_Kd = -2.0;					//PID相关参数

float speed_target = 30.0, PID_MAX_VALUE = 150.0;

u8 target = 0;


/*
*===================================================================
*		说明：设置PID的值
*		参数：side		<u8>		电机编号	合法值1234
*					part		<u8>		选择要编辑的PID的部分
*					action	<u8>		0	减	1	加
*					value		<float>	要改变的值大小
*		返回：无
*===================================================================
*/
void Set_PID_Value(u8 side, u8 part, u8 action, float value)
{
	switch(side)	//判断电机
	{
		case 1: 
		{
			if(part == 1)	{if(action) LF_Speed_Kp += value; else LF_Speed_Kp -= value;}
			if(part == 2)	{if(action) LF_Speed_Ki += value; else LF_Speed_Ki -= value;}
			if(part == 3)	{if(action) LF_Speed_Kd += value; else LF_Speed_Kd -= value;}
			break;
		}
		case 2: 
		{
			if(part == 1)	{if(action) LB_Speed_Kp += value; else LB_Speed_Kp -= value;}
			if(part == 2)	{if(action) LB_Speed_Ki += value; else LB_Speed_Ki -= value;}
			if(part == 3)	{if(action) LB_Speed_Kd += value; else LB_Speed_Kd -= value;}
			break;
		}
		case 3: 
		{
			if(part == 1)	{if(action) RF_Speed_Kp += value; else RF_Speed_Kp -= value;}
			if(part == 2)	{if(action) RF_Speed_Ki += value; else RF_Speed_Ki -= value;}
			if(part == 3)	{if(action) RF_Speed_Kd += value; else RF_Speed_Kd -= value;}
			break;
		}
		case 4: 
		{
			if(part == 1)	{if(action) RB_Speed_Kp += value; else RB_Speed_Kp -= value;}
			if(part == 2)	{if(action) RB_Speed_Ki += value; else RB_Speed_Ki -= value;}
			if(part == 3)	{if(action) RB_Speed_Kd += value; else RB_Speed_Kd -= value;}
			break;
		}
		default: break;
	}
	printf("[%.0f %.0f %.0f]\t", LF_Speed_Kp, LF_Speed_Ki, LF_Speed_Kd);
	printf("[%.0f %.0f %.0f]\t", LB_Speed_Kp, LB_Speed_Ki, LB_Speed_Kd);
	printf("[%.0f %.0f %.0f]\t", RF_Speed_Kp, RF_Speed_Ki, RF_Speed_Kd);
	printf("[%.0f %.0f %.0f]\n", RB_Speed_Kp, RB_Speed_Ki, RB_Speed_Kd);
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
	
	PID_Limit(&balance);
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
	
	balance = (LB_Speed_Kp * Bias)/10 + LB_Speed_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差

	PID_Limit(&balance);
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
	
	balance = (RF_Speed_Kp * Bias)/10 + RF_Speed_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差

	PID_Limit(&balance);
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
	
	balance = (RB_Speed_Kp * Bias)/10 + RB_Speed_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差

	PID_Limit(&balance);
	return balance;  //返回值
}


/**************************************************************************
函数功能：PID限幅
入口参数：value	<int>	要限幅的值指针
返回  值：无
**************************************************************************/
void PID_Limit(int* value)
{
	if(*value > PID_MAX_VALUE)	*value = PID_MAX_VALUE;
	if(*value < -PID_MAX_VALUE)	*value = -PID_MAX_VALUE;
}



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


