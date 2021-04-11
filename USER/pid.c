#include "pid.h"


float Balance_Kp = 25.0, Balance_Ki = 0.00, Balance_Kd = 100.0;		//X 轴位置环 PID相关参数

float Y_side_Kp = 20.0, Y_side_Ki = 0.0, Y_side_Kd = 200.0;				//Y 轴位置环 PID相关参数


float LF_Speed_Kp = -230.5, LF_Speed_Ki = -0.37, LF_Speed_Kd = 13.0;					//PID相关参数
//float LB_Speed_Kp = -285.5, LB_Speed_Ki = -0.01, LB_Speed_Kd = 78.0;					//PID相关参数
float LB_Speed_Kp = -285.5, LB_Speed_Ki = -0.32, LB_Speed_Kd = 19.0;					//PID相关参数
float RF_Speed_Kp = -285.5, RF_Speed_Ki = -0.1, RF_Speed_Kd = 19.0;					//PID相关参数
//float RB_Speed_Kp = -230.5, RB_Speed_Ki = 0.0, RB_Speed_Kd = 0.0;					//PID相关参数
float RB_Speed_Kp = -230.5, RB_Speed_Ki = -0.26, RB_Speed_Kd = 19.0;					//PID相关参数

//float LF_Speed_Kp = -200.5, LF_Speed_Ki = 0.2, LF_Speed_Kd = -5.0;					//PID相关参数
//float LB_Speed_Kp = -125.5, LB_Speed_Ki = 0.1, LB_Speed_Kd = -6.0;					//PID相关参数
//float RF_Speed_Kp = -125.5, RF_Speed_Ki = 0.1, RF_Speed_Kd = -2.0;					//PID相关参数
//float RB_Speed_Kp = -195.5, RB_Speed_Ki = 0.1, RB_Speed_Kd = -5.0;					//PID相关参数


float LF_speed_target = 30.0, LF_PID_MAX_VALUE = 150.0;
float LB_speed_target = 30.0, LB_PID_MAX_VALUE = 150.0;
float RF_speed_target = 30.0, RF_PID_MAX_VALUE = 150.0;
float RB_speed_target = 30.0, RB_PID_MAX_VALUE = 150.0;

u8 Expect_Target_Speed_Sta;		//标志目标速度期望改变的状态	bit0~6	->	改变的目标值	bit7 -> 改变状态

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
	printf("[%0.1f %0.2f %0.1f]\t", LF_Speed_Kp, LF_Speed_Ki, LF_Speed_Kd);
	printf("[%0.1f %0.2f %0.1f]\t", LB_Speed_Kp, LB_Speed_Ki, LB_Speed_Kd);
	printf("[%0.1f %0.2f %0.1f]\t", RF_Speed_Kp, RF_Speed_Ki, RF_Speed_Kd);
	printf("[%0.1f %0.2f %0.1f]\n", RB_Speed_Kp, RB_Speed_Ki, RB_Speed_Kd);
}


/*
*===================================================================
*		说明：改变电机目标速度值
*		参数：side		<u8>		电机编号	合法值 0 1 2 3 4		0 代表全部电机
*					action	<u8>		0	减	1	加
*					value		<u8>		要改变的值大小
*		返回：无
*===================================================================
*/
void Change_Speed_Target(u8 side, u8 action, u8 value)
{
	switch(side)
	{
		case 0: 	//所有电机
		{
			if(action == 0)
				LF_speed_target -= value, LB_speed_target -= value, RF_speed_target -= value, RB_speed_target -= value;
			else
				LF_speed_target += value, LB_speed_target += value, RF_speed_target += value, RB_speed_target += value;
			break;
		}
		case 1: 	//电机1
		{
			if(action == 0)	LF_speed_target -= value;	else	LF_speed_target += value;
			break;
		}
		case 2: 	//电机2
		{
			if(action == 0)	LB_speed_target -= value;	else	LB_speed_target += value;
			break;
		}
		case 3: 	//电机3
		{
			if(action == 0)	RF_speed_target -= value;	else	RF_speed_target += value;
			break;
		}
		case 4: 	//电机4
		{
			if(action == 0)	RB_speed_target -= value;	else	RB_speed_target += value;
			break;
		}
		default: break;
	}
}


/*
*===================================================================
*		说明：设置电机目标速度值
*		参数：side		<u8>		电机编号	合法值 0 1 2 3 4		0 代表全部电机
*					value		<u8>		要改变的值
*		返回：无
*===================================================================
*/
void Set_Speed_Target(u8 side, u8 value)
{
	switch(side)
	{
		case 0: LF_speed_target = LB_speed_target = RF_speed_target = RB_speed_target = value; break;
		case 1: LF_speed_target = value; break;
		case 2: LB_speed_target = value; break;
		case 3: RF_speed_target = value; break;
		case 4: RB_speed_target = value; break;
		default: break;
	}
}

/*
*===================================================================
*		说明：重设电机目标速度值
*		参数：无
*		返回：无
*===================================================================
*/
void Reset_Target_Speed(void)
{
	if(Expect_Target_Speed_Sta&0x80)	//判断目标预期值是否改变
	{
		LF_speed_target = Expect_Target_Speed_Sta&0x7F;
		LB_speed_target = Expect_Target_Speed_Sta&0x7F;
		RF_speed_target = Expect_Target_Speed_Sta&0x7F;
		RB_speed_target = Expect_Target_Speed_Sta&0x7F;
	}
	else
	{
		LF_speed_target = 30;
		LB_speed_target = 30;
		RF_speed_target = 30;
		RB_speed_target = 30;
	}
}

/*
*===================================================================
*		说明：设置电机目标速度期望值
*		参数：无
*		返回：无
*===================================================================
*/
void Set_Expect_Target_Speed(u8 speed)
{
	Expect_Target_Speed_Sta |= 0x80;	//标志期望值改变
	Expect_Target_Speed_Sta |= speed;	//标志速度值
	Reset_Target_Speed();
}


/**************************************************************************
函数功能：左前速度环PD控制
入口参数：速度
返回  值：控制PWM
**************************************************************************/
int PID_Speed_Left_Front(float speed)
{
	float Differential, Bias;		//定义差分变量和偏差
	static float Last_Bias, Integration, Balance_Integration, Flag_Target;  //上一次的偏差值
	int balance;								//平衡的返回值

	Bias = speed - LF_speed_target;  		//求出速度偏差

	Differential = Bias - Last_Bias;  //求得偏差的变化率	 

//	if(++Flag_Target > 10) 						//错频处理积分控制
//	{
		Flag_Target = 0;
		Integration += Bias;  // 积分
		if(Integration<-50) Integration = -50;	//积分限幅
		if(Integration>50)  Integration = 50;	
		Balance_Integration = Integration * LF_Speed_Ki;   //积分控制
//	}
	
	balance = (LF_Speed_Kp * Bias)/10 + LF_Speed_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差
	
	PID_Limit(1, &balance);
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
	static float Last_Bias, Integration, Balance_Integration, Flag_Target;  //上一次的偏差值
	int balance;								//平衡的返回值

	Bias = speed - LB_speed_target;  		//求出速度偏差

	Differential = Bias - Last_Bias;  //求得偏差的变化率	 

//	if(++Flag_Target > 10) 						//错频处理积分控制
//	{
		Flag_Target = 0;
		Integration += Bias;  // 积分
		if(Integration<-50) Integration = -50;	//积分限幅
		if(Integration>50)  Integration = 50;	
		Balance_Integration = Integration * LB_Speed_Ki;   //积分控制
	//}
	
	balance = (LB_Speed_Kp * Bias)/10 + LB_Speed_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差

	PID_Limit(2, &balance);
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
	static float Last_Bias, Integration, Balance_Integration, Flag_Target;  //上一次的偏差值
	int balance;								//平衡的返回值

	Bias = speed - RF_speed_target;  		//求出速度偏差

	Differential = Bias - Last_Bias;  //求得偏差的变化率	 

//	if(++Flag_Target > 10) 						//错频处理积分控制
//	{
		Flag_Target = 0;
		Integration += Bias;  // 积分
		if(Integration<-50) Integration = -50;	//积分限幅
		if(Integration>50)  Integration = 50;	
		Balance_Integration = Integration * RF_Speed_Ki;   //积分控制
	//}
	
	balance = (RF_Speed_Kp * Bias)/10 + RF_Speed_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差

	PID_Limit(3, &balance);
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
	static float Last_Bias, Integration, Balance_Integration, Flag_Target;  //上一次的偏差值
	int balance;								//平衡的返回值

	Bias = speed - RB_speed_target;  		//求出速度偏差

	Differential = Bias - Last_Bias;  //求得偏差的变化率	 

//	if(++Flag_Target > 10) 						//错频处理积分控制
//	{
		Flag_Target = 0;
		Integration += Bias;  // 积分
		if(Integration<-50) Integration = -50;	//积分限幅
		if(Integration>50)  Integration = 50;	
		Balance_Integration = Integration * RB_Speed_Ki;   //积分控制
//	}
	
	balance = (RB_Speed_Kp * Bias)/10 + RB_Speed_Kd*Differential/10 + Balance_Integration;   //计算控制PWM  PD控制
	Last_Bias = Bias;  //保存上一次的偏差

	PID_Limit(4, &balance);
	return balance;  //返回值
}


/**************************************************************************
函数功能：PID限幅
入口参数：side	<u8>	限幅的电机编号
					value	<int>	要限幅的值指针
返回  值：无
**************************************************************************/
void PID_Limit(u8 side, int* value)
{
	switch(side)
	{
		case 1:
		{
			if(*value > LF_PID_MAX_VALUE)	*value = LF_PID_MAX_VALUE;
			if(*value < -LF_PID_MAX_VALUE)	*value = -LF_PID_MAX_VALUE;
			break;
		}
		case 2:
		{
			if(*value > LB_PID_MAX_VALUE)	*value = LB_PID_MAX_VALUE;
			if(*value < -LB_PID_MAX_VALUE)	*value = -LB_PID_MAX_VALUE;
			break;
		}
		case 3:
		{
			if(*value > RF_PID_MAX_VALUE)	*value = RF_PID_MAX_VALUE;
			if(*value < -RF_PID_MAX_VALUE)	*value = -RF_PID_MAX_VALUE;
			break;
		}
		case 4:
		{
			if(*value > RB_PID_MAX_VALUE)	*value = RB_PID_MAX_VALUE;
			if(*value < -RB_PID_MAX_VALUE)	*value = -RB_PID_MAX_VALUE;
			break;
		}
		default: break;
	}

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


