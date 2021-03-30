#include "motor.h"

u16 MOTOR_PWM[4] = {20000, 20000, 20000, 20000,};						//当前电机CCR值
u16 MAX_MOTOR_PWM = 32000;	//电机最大CCR值

/*
*===================================================================
*		说明：配置电机驱动 IN 口
*		参数：无
*		返回：无
*===================================================================
*/
void MOTO_GPIO_Config(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;																							//定义 GPIO_InitTypeDef 类型的结构体

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF, ENABLE);  		//开启GPIO的外设时钟
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;	//设置控制的GPIO引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                    //通用复用推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 //设置引脚速率为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);                            //初始化GPIO

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7;	//设置控制的GPIO引脚
	GPIO_Init(GPIOE, &GPIO_InitStructure);				//初始化GPIO
}


/*
*===================================================================
*		说明：配置左前电机 IN 口状态
*		参数：state	电机运动状态
*		返回：无
*===================================================================
*/
void Set_MOTOR_Left_Front(char state)
{
	if(state == GO)		//左前电机前进
	{
		IN1(0);
		IN2(1);
	}
	if(state == BACK)	//左前电机后退
	{
		IN1(1);
		IN2(0);
	}
	if(state == STOP)	//左前电机停转
	{
	  IN1(0);
		IN2(0);
	}
}

/*
*===================================================================
*		说明：配置左后电机 IN 口状态
*		参数：state	电机运动状态
*		返回：无
*===================================================================
*/
void Set_MOTOR_Left_Behind(char state)
{
	if(state == GO)		//左后电机前进
	{
		IN3(0);
		IN4(1);
	}
	if(state == BACK)	//左后电机后退
	{
		IN3(1);
		IN4(0);
	}
	if(state == STOP)//左后电机停转
	{
	  IN3(0);
		IN4(0);
	}
}

/*
*===================================================================
*		说明：配置右前电机 IN 口状态
*		参数：state	电机运动状态
*		返回：无
*===================================================================
*/
void Set_MOTOR_Right_Front(char state)
{
	if(state == GO)		//左前电机前进
	{
		IN5(0);
		IN6(1);
	}
	if(state == BACK)	//左前电机后退
	{
		IN5(1);
		IN6(0);
	}
	if(state == STOP)	//左前电机停转
	{
	  IN5(0);
		IN6(0);
	}
}

/*
*===================================================================
*		说明：配置右后电机 IN 口状态
*		参数：state	电机运动状态
*		返回：无
*===================================================================
*/
void Set_MOTOR_Right_Behind(char state)
{
	if(state == GO)		//左后电机前进
	{
		IN7(0);
		IN8(1);
	}
	if(state == BACK)	//左后电机后退
	{
		IN7(1);
		IN8(0);
	}
	if(state == STOP)//左后电机停转
	{
	  IN7(0);
		IN8(0);
	}
}


/*
*===================================================================
*		说明：小车往前走
*		参数：无
*		返回：无
*===================================================================
*/
void Car_Go(void)
{
	Set_MOTOR_Left_Front(GO);
	Set_MOTOR_Left_Behind(GO);
	Set_MOTOR_Right_Front(GO);
	Set_MOTOR_Right_Behind(GO);
}


//***************************小车后退***************************//
void Car_Back(void)
{
	Set_MOTOR_Left_Front(BACK);
	Set_MOTOR_Left_Behind(BACK);
	Set_MOTOR_Right_Front(BACK);
	Set_MOTOR_Right_Behind(BACK);
}

////***************************小车向右直行***************************//
void Car_Go_Right(void)
{
	Set_MOTOR_Left_Front(GO);
	Set_MOTOR_Left_Behind(BACK);
	Set_MOTOR_Right_Front(BACK);
	Set_MOTOR_Right_Behind(GO);
}

//***************************小车向左直行***************************//
void Car_Go_Left(void)
{
	Set_MOTOR_Left_Front(BACK);
	Set_MOTOR_Left_Behind(GO);
	Set_MOTOR_Right_Front(GO);
	Set_MOTOR_Right_Behind(BACK);
}

//***************************小车停车***************************//
void Car_Stop(void)
{
	Set_MOTOR_Left_Front(STOP);
	Set_MOTOR_Left_Behind(STOP);
	Set_MOTOR_Right_Front(STOP);
	Set_MOTOR_Right_Behind(STOP);
}

//***************************右前45度***************************//
void Car_Right_Front(void)
{
	Set_MOTOR_Left_Front(GO);
	Set_MOTOR_Left_Behind(STOP);
	Set_MOTOR_Right_Front(STOP);
	Set_MOTOR_Right_Behind(GO);
}

//***************************左前45度***************************//
void Car_Left_Front(void)
{
	Set_MOTOR_Left_Front(STOP);
	Set_MOTOR_Left_Behind(GO);
	Set_MOTOR_Right_Front(GO);
	Set_MOTOR_Right_Behind(STOP);
}

//***************************原地左转***************************//
void Car_Raw_Left(void)
{
	Set_MOTOR_Left_Front(BACK);
	Set_MOTOR_Left_Behind(BACK);
	Set_MOTOR_Right_Front(GO);
	Set_MOTOR_Right_Behind(GO);
}

//***************************原地右转***************************//
void Car_Raw_Right(void)
{
	Set_MOTOR_Left_Front(GO);
	Set_MOTOR_Left_Behind(GO);
	Set_MOTOR_Right_Front(BACK);
	Set_MOTOR_Right_Behind(BACK);
}

//***************************原地180度掉头***************************//
void Car_Turn(void)
{
	Set_MOTOR_Left_Front(GO);
	Set_MOTOR_Left_Behind(STOP);
	Set_MOTOR_Right_Front(BACK);
	Set_MOTOR_Right_Behind(STOP);
}

/*
*===================================================================
*		说明：小车提速
*		参数：motor_pwm	<u16>	小车提速的CCR值
*		返回：无
*===================================================================
*/
void MOTOR_Speed_Up(u16 motor_pwm)
{
	MOTOR_PWM[0]+=motor_pwm;
	MOTOR_PWM[1]+=motor_pwm;
	MOTOR_PWM[2]+=motor_pwm;
	MOTOR_PWM[3]+=motor_pwm;
	printf("\t%d, %d", MOTOR_PWM[0], MOTOR_PWM[1]);
}

/*
*===================================================================
*		说明：小车减速
*		参数：motor_pwm	<u16>	小车减速的CCR值
*		返回：无
*===================================================================
*/
void MOTOR_Speed_Down(u16 motor_pwm)
{
	MOTOR_PWM[0]-=motor_pwm;
	MOTOR_PWM[1]-=motor_pwm;
	MOTOR_PWM[2]-=motor_pwm;
	MOTOR_PWM[3]-=motor_pwm;
	printf("\t%d, %d", MOTOR_PWM[0], MOTOR_PWM[1]);
}

/*
*===================================================================
*		说明：给定 X Y W 三个方向参数计算电机运动速度
*		参数：xSpeed：X 方向速度
*					ySpeed：Y 方向速度
*					wSpeed：W 方向速度
*		返回：无
*===================================================================
*/
void Calc_Motor_PWM(float xSpeed, float ySpeed, float wSpeed)
{
    float m1_speed = ySpeed - xSpeed + wSpeed; 
    float m2_speed = ySpeed + xSpeed - wSpeed;
    float m3_speed = ySpeed - xSpeed - wSpeed;
    float m4_speed = ySpeed + xSpeed + wSpeed;
    
    float max = m1_speed;
    if (max < m2_speed)   max = m2_speed;
    if (max < m3_speed)   max = m3_speed;
    if (max < m4_speed)   max = m4_speed;
    
    if (max > MAX_MOTOR_PWM)
    {
        m1_speed = m1_speed / max * MAX_MOTOR_PWM;
        m2_speed = m2_speed / max * MAX_MOTOR_PWM;
        m3_speed = m3_speed / max * MAX_MOTOR_PWM;
        m4_speed = m4_speed / max * MAX_MOTOR_PWM;
    }
    
    MOTOR_PWM_Out(m2_speed, m3_speed, m1_speed, m4_speed);
}
