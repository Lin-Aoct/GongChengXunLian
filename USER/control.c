#include "control.h"	

u8 CAR_MODE = 0;						//标志小车模式
u8 step = 0, count = 10;		//标志执行步骤以及计时变量
u16 front_data, right_data, behind_data, left_data;	//前 右 后 左 红外循迹模块读数变量
u8 is_stop_mode = 0;				//标志是否为停车模式 便于PID停车
u8 is_car_debug_mode = 0;		//小车 debug 模式标志 若为1则到点后不执行机械臂动作

/*
*===================================================================
*		说明：定时器6中断服务函数 15ms 执行一次
*		参数：无
*		返回：无
*===================================================================
*/
void TIM6_DAC_IRQHandler(void)
{    
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)	//检查指定的TIM中断发生与否
	{
		switch(CAR_MODE)
		{
			case 0: break;
			case 1: Mode_Start(); break;									//出发
			case 2: Mode_Go_Area1(); break;								//二维码 			-> 	物料堆放区
			case 3: Mode_Area1_To_Area2(1); break;				//物料堆放区	->	粗加工区	顶层模式
			case 4: Mode_Area2_To_Area3_Top(); break;			//粗加工区		->	半成品区	顶层模式
			case 5: Mode_Area3_To_Area1(); break;					//半成品区		->	原料区
			case 6: Mode_Go_One_Aera1(1); break;					//车第1次往前走一格
			case 7: Mode_Back_One_Area1(1); break;				//车第1次往后退一格
			case 8: Mode_Go_One_Aera1(2); break;					//车第2次往前走一格
			case 9: Mode_Back_One_Area1(2); break;				//车第2次往后退一格
			case 10: Mode_Go_One_Aera1(3); break;					//车第3次往前走一格
			case 11: Mode_Area1_To_Area2(2); break;				//物料堆放区	->	粗加工区	下层模式
			case 12: Mode_Area2_To_Area3_Bottom(); break;	//粗加工区		->	半成品区	下层模式
			case 13: Mode_Area3_Back(); break;						//半成品区		->	返回区
			
			case 20: Mode_PID_Test(1); break;
			case 21: Mode_PID_Test(2); break;
			case 22: Mode_PID_Test(3); break;
			case 23: Mode_PID_Test(4); break;
			case 24: Mode_PID_Test(5); break;
			case 25: Mode_PID_Test(6); break;
			case 26: Mode_PID_Test(7); break;
			case 27: Mode_PID_Test(8); break;
			case 28: Mode_PID_Test(9); break;
			case 29: Mode_PID_Test(10); break;

			case 41: Cross_Road_Fix(1); break;		
			case 42: Cross_Road_Fix(2); break;		

			default: break;
		}
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);			//清除TIM6的中断待处理位
   }       	
}

/*
*===================================================================
*		说明：路口定点模式函数
*		参数：无
*		返回：无
*===================================================================
*/
void Cross_Road_Fix(u8 mode)
{
	static u8 fix_counter;				//计数变量
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	behind_data = Find_Get_Behind();
	left_data = Find_Get_Left();
	
	Set_Expect_Target_Speed(6);	//减速
	if(mode == 0)
	{
		if(front_data == 1001 && right_data == 1001 && behind_data == 1001 && left_data == 1001) printf("[停车]"), Car_Stop(), Stop_Find(); //CAR_MODE = 0;	//中线
		else if((front_data == 1110 || front_data == 1100) &&
						(right_data == 1110 || right_data == 1100) &&
						(behind_data == 1110 || behind_data == 1100) &&
						(left_data == 1110 || left_data == 1100)) printf("[Yaw向左]"), Car_Yaw_Right();	//Yaw向左
		else if((front_data == 111 || front_data == 11) &&
						(right_data == 111 || right_data == 11) &&
						(behind_data == 111 || behind_data == 11) &&
						(left_data == 111 || left_data == 11)) printf("[Yaw向右]"), Car_Yaw_Right();		//Yaw向右
	}

	if(mode == 1)	//物料区上层定点
	{
		if(left_data == 1001 && right_data == 0)
			Car_Stop(), Stop_Find(), fix_counter = 0, CAR_MODE=0;	//位置合适 停车
		else if(right_data == 0)
		{
			if(left_data == 111 || left_data == 1011 || left_data == 11) Car_Back();				//后退
			else if(left_data == 1110 || left_data == 1101 || left_data == 1100) Car_Go();	//前进
			else if(left_data == 1111 && fix_counter == 0) Car_Back(), fix_counter = 22;		//左侧无数据 前进一下 等待 ((22-2)*15) 300ms 后无数据再进行折返
			else if(left_data == 1111 && fix_counter-- == 1) Car_Go();												//扫描间隔到时间后折返
		}
		else if(right_data == 11 || right_data == 1) Car_Yaw_Left();		//Yaw向左
		else if(right_data == 1100 || right_data == 1000) Car_Yaw_Right();	//Yaw向右
//		else if((right_data == 1110 || right_data == 1100) &&
//						(left_data == 1110 || left_data == 11)) Car_Yaw_Right();	//Yaw向左
//		else if((right_data == 111 || right_data == 11) &&
//						(left_data == 111 || left_data == 11)) Car_Yaw_Right();		//Yaw向右
	}
	
	if(mode == 2)	//粗加工区定点
	{
		if(behind_data == 1001 && front_data == 0)
			Car_Stop(), Stop_Find(), fix_counter = 0, CAR_MODE=0;	//位置合适 停车
		else if(front_data == 0)
		{
			if(behind_data == 111 || behind_data == 1011 || behind_data == 11) Car_Go_Right();				//后退
			else if(behind_data == 1110 || behind_data == 1101 || behind_data == 1100) Car_Go_Left();	//前进
			else if(behind_data == 1111 && fix_counter == 0) Car_Go_Right(), fix_counter = 22;				//左侧无数据 前进一下 等待 ((22-2)*15) 300ms 后无数据再进行折返
			else if(behind_data == 1111 && fix_counter-- == 1) Car_Go_Left();													//扫描间隔到时间后折返
		}
		else if(front_data == 11 || front_data == 1) Car_Yaw_Left();				//Yaw向左
		else if(front_data == 1100 || front_data == 1000) Car_Yaw_Right();	//Yaw向右

		else if((front_data == 1110 || front_data == 1100) &&
						(behind_data == 1110 || behind_data == 11)) Car_Yaw_Right();	//Yaw向左
		else if((front_data == 111 || front_data == 11) &&
						(behind_data == 111 || behind_data == 11)) Car_Yaw_Right();		//Yaw向右
	}
	
	Set_PID_PWM();

}

/*
*===================================================================
*		说明：PID测试模式函数
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_PID_Test(u8 mode)
{
	switch(mode)
	{
		case 1: Car_Go(); FIND_DRIVER=0, CURRENT_DIRATION=1; Find(); break;
		case 2: Car_Back(); FIND_DRIVER=2, CURRENT_DIRATION=2; Find(); break;
		case 3: Car_Go_Left(); FIND_DRIVER=3, CURRENT_DIRATION=3; Find(); break;
		case 4: Car_Go_Right(); FIND_DRIVER=1, CURRENT_DIRATION=4; Find(); break;
		case 5: Set_MOTOR_Left_Front(GO); Set_MOTOR_Left_Behind(STOP); Set_MOTOR_Right_Front(STOP); Set_MOTOR_Right_Behind(STOP); break;
		case 6: Set_MOTOR_Left_Front(STOP); Set_MOTOR_Left_Behind(GO); Set_MOTOR_Right_Front(STOP); Set_MOTOR_Right_Behind(STOP); break;
		case 7: Set_MOTOR_Left_Front(STOP); Set_MOTOR_Left_Behind(STOP); Set_MOTOR_Right_Front(GO); Set_MOTOR_Right_Behind(STOP); break;
		case 8: Set_MOTOR_Left_Front(STOP); Set_MOTOR_Left_Behind(STOP); Set_MOTOR_Right_Front(STOP); Set_MOTOR_Right_Behind(GO); break;
		case 9: Car_Go(); is_stop_mode = 0; Set_Expect_Target_Speed(30); break;
		case 10: Car_Back(); is_stop_mode = 1; Set_Expect_Target_Speed(0); break;
		default: break;
	}
	Set_PID_PWM();
}

/*
*===================================================================
*		说明：PID控制电机输出PWM 定时调用本函数
*		参数：无
*		返回：无
*===================================================================
*/
void Set_PID_PWM(void)
{
	ENCODER_DATA[0] = abs(Read_Encoder(2));
	ENCODER_DATA[1] = abs(Read_Encoder(3));
	ENCODER_DATA[2] = abs(Read_Encoder(4));
	ENCODER_DATA[3] = abs(Read_Encoder(5));
	
	if(IS_MOTOR_ALL_STOP == 0)	//判断是否上锁
	{
		if(is_stop_mode == 1)//判断是否为停车模式
		{
			printf("停车模式");
			TIM8->CCR1 = -PID_Speed_Left_Front(ENCODER_DATA[0]);
			TIM8->CCR2 = -PID_Speed_Left_Behind(ENCODER_DATA[1]);
			TIM8->CCR4 = -PID_Speed_Right_Front(ENCODER_DATA[2]);
			TIM8->CCR3 = -PID_Speed_Right_Behind(ENCODER_DATA[3]);
		}
		else
		{
			TIM8->CCR1 = MOTOR_PWM[0] + PID_Speed_Left_Front(ENCODER_DATA[0]);
			TIM8->CCR2 = MOTOR_PWM[1]	+ PID_Speed_Left_Behind(ENCODER_DATA[1]);
			TIM8->CCR4 = MOTOR_PWM[2] + PID_Speed_Right_Front(ENCODER_DATA[2]);
			TIM8->CCR3 = MOTOR_PWM[3] + PID_Speed_Right_Behind(ENCODER_DATA[3]);
		}
		ENCODER_DATA[5] = TIM8->CCR3 -100;
	}
	
//	printf("%x%x%x%d%x", 0xFF, 0XF0, 0X0F, ENCODER_DATA[0], 0x00);
//	printf("%x%x%x%d%x", 0xFF, 0XF1, 0X0E, ENCODER_DATA[1], 0x00);
//	printf("%x%x%x%d%x", 0xFF, 0XF2, 0X0D, ENCODER_DATA[2], 0x00);
//	printf("%x%x%x%d%x", 0xFF, 0XF3, 0X0C, ENCODER_DATA[3], 0x00);
	
	if(is_car_debug_mode)
	{
		printf("编码器[%d %d %d %d]\t", ENCODER_DATA[0], ENCODER_DATA[1], ENCODER_DATA[2], ENCODER_DATA[3]);
		printf("PWM[%d %d %d %d]\t", TIM8->CCR1, TIM8->CCR2, TIM8->CCR4, TIM8->CCR3);
		printf("TS[%.0f %.0f %.0f %.0f]\t", LF_speed_target, LB_speed_target, RF_speed_target, RB_speed_target);	//打印目标速度
		printf("H[%d | %d]\tstep[%d]\n", front_data, right_data, step);	//打印调试信息
	}
}

/*
*===================================================================
*		说明：出发模式，前往二维码扫码区域
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_Start(void)
{
	static u8 y_line_step;		//启动模式数y线步骤变量  避免斜移时丢线
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	
		Set_Expect_Target_Speed(35), Car_Left_Front(), step++, count = 35;		//左上平移	减速 
	
	if(count > 0 && step == 1)	count--;	//延时510ms
	
	if(front_data == 1001 && step == 1 && count == 0)
		Car_Go(), Set_Expect_Target_Speed(30), FIND_MODE=0, FIND_DRIVER = 0, CURRENT_DIRATION = 1, step++;	//前面处于线中
	Find();
	
	if(right_data == 1001 && y_line_step == 0)	y_line_step++;	//Y线1 中间
	
	if(right_data == 1110 && y_line_step == 1)	y_line_step++;	//出线1
	
	if(right_data == 1001 && y_line_step == 2)	y_line_step++;	//线2中间
	
	if(right_data == 1110 && y_line_step == 3)	count = 3, y_line_step++, step++;	//出线2
		
	if(count > 0 && step == 3)	count--;						//3*15ms = 45ms

	if(count == 0 && step == 3)	
	{
		Car_Stop();				//退出出发模式
		Stop_Find();			//停止巡迹
		CAR_MODE = 0;
		y_line_step = 0;
		if(!is_car_debug_mode)
			ARM_Action = 1;		//机械臂扫码
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		说明：二维码扫描完毕后 前往物料堆放区域
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_Go_Area1(void)
{
	static u8 y_line_step;		//启动模式数y线步骤变量  避免斜移时丢线
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	left_data = Find_Get_Left();

	
//	if(step == 0)	Set_Expect_Target_Speed(30), Car_Left_Front(), step++;	//走左上角

//	if((left_data == 1001 || left_data == 0) && step == 1) y_line_step=1, step++;	//左侧碰线
//	
//	if(front_data == 1001 && step == 2)
//		Car_Go(), Set_Expect_Target_Speed(40), FIND_MODE=0, FIND_DRIVER = 0, CURRENT_DIRATION = 1, step++;	//前面处于线中

//	Find();
//	if(right_data == 1001 && step == 3)	step++;	//Y线2 中间
//	if(right_data == 1110 && step == 4)	step++;	//出 Y线2
//	
//	if(right_data == 1001 && step == 5)	step++;	//Y线3 中间
//	if(right_data == 1110 && step == 6)	
//		step++, Set_Expect_Target_Speed(15);			//出Y线3 减速 准备转向
//	
//	if((right_data == 1001 || right_data == 11) && step == 7)
//		Set_Expect_Target_Speed(7), Car_Go_Right(), FIND_DRIVER = 3, CURRENT_DIRATION = 3, step++;	//碰到线4 左平移

//	Set_PID_PWM();

//	if(right_data == 0 && step == 8)	
//	{
//		step++;
//		Car_Stop();
//		Stop_Find();
//		y_line_step = 0;
//		Expect_Target_Speed_Sta = 0;
//		Reset_Target_Speed();					//恢复速度
//		//CAR_MODE = 0;								//到达物料抓取位置
//		CAR_MODE = 41;								//到达物料抓取位置 开始定点
//		if(!is_car_debug_mode)
//			ARM_Action = 2;							//机械臂扫描上层
//	}
//	
	
	
	
	
	
	
	
	
	
	
	if(step == 0)	Set_Expect_Target_Speed(40), Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, step = 1;	//前面处于线中
	
	Find();
	
	if(right_data == 1001 && step == 1)	step++;	//线1中间
	if(right_data == 1110 && step == 2)	step++;	//出线1
	
	if(right_data == 1001 && step == 3)	step++;	//线2中间
	if(right_data == 1110 && step == 4)	step++;	//出线2
	
	if(right_data == 1001 && step == 5)	step++;	//线3中间
	if(right_data == 1110 && step == 6)	
		step++, Set_Expect_Target_Speed(15);			//出线3 减速 准备转向
	
	if((right_data == 1001 || right_data == 11) && step == 7)
		Set_Expect_Target_Speed(7), Car_Go_Left(), FIND_DRIVER = 3, CURRENT_DIRATION = 3, step++;	//碰到线4 左平移

	Set_PID_PWM();

	if(right_data == 0 && step == 8)	
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();					//恢复速度
		//CAR_MODE = 0;								//到达物料抓取位置
		CAR_MODE = 41;								//到达物料抓取位置 开始定点
		if(!is_car_debug_mode)
			ARM_Action = 2;							//机械臂扫描上层
	}
}

/*
*===================================================================
*		说明：物料堆放区域前往粗加工区
*		参数：mode	<u8>	
*		返回：无
*===================================================================
*/
void Mode_Area1_To_Area2(u8 mode)
{
	static u8 down_temp, dis_temp;
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)
		Set_Expect_Target_Speed(25), Find_Target_Speed = 25, Car_Go_Left(), FIND_DRIVER = 3, CURRENT_DIRATION = 3, step++;	//左平移	Y轴循迹
	Find();
	
	if(front_data == 1001 && step == 1)
		step++, Expect_Target_Speed_Sta = 0, Reset_Target_Speed();	//X线1 中间 恢复速度
	if(front_data == 1110 && step == 2)	step++;	//出线1
	
	if(front_data == 1001 && step == 3)	step++;	//X线2 中间
	if(front_data == 1110 && step == 4) step++;	//出 X线2 降低巡线速度 
	
//	if(front_data == 1001 && step == 5)						//X线3 中间
//		down_temp = 20, dis_temp=2, Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, FIND_MODE = 1, step++;	//碰到线3 减速 向前运动 X轴巡线

//	if(step == 6)	{dis_temp--;if(dis_temp==0){Set_Expect_Target_Speed(down_temp--);dis_temp=2; if(down_temp == 6) step++;}}

	if(front_data == 1001 && step == 5)						//X线3 中间
		Set_Expect_Target_Speed(10), Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, FIND_MODE = 0, step++;	//碰到线3 减速 向前运动 X轴巡线
	
	if(front_data == 0000 && step == 6)
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();					//恢复速度
		Find_Target_Speed = 35;	//巡线速度恢复
		down_temp = 0;
		dis_temp = 0;
		CAR_MODE = 42;									//粗加工区定点
		//CAR_MODE = 0;									//到达物料抓取位置 开始定点
		if(!is_car_debug_mode)
		{
			if(mode)
				ARM_Action = 4;
			else
				ARM_Action = 14;
		}
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		说明：粗加工区前往半成品区域	顶层模式
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_Area2_To_Area3_Top(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	left_data = Find_Get_Left();
	
	if(step == 0)	Set_Expect_Target_Speed(35), Car_Back(), FIND_DRIVER = 2, CURRENT_DIRATION = 2, FIND_MODE = 1, step++;	//后退	X轴负半轴循迹
	
	Find();
	
	if(right_data == 1001 && step == 1)	step++;		//Y线1 中间
	if(right_data == 1110 && step == 2)	step++;		//出Y线1
	
	if(right_data == 1001 && step == 3)	step++;		//Y线2 中间
	if(right_data == 1110 && step == 4)	step++;		//出Y线2
	
	if((right_data == 1110 || right_data == 1001)&& step == 5)
		Set_Expect_Target_Speed(25), Car_Go_Left(), FIND_MODE = 1, FIND_DRIVER = 3, CURRENT_DIRATION = 3, count = 35, step++;	//Y线3 中间	左走 Y轴正半轴巡线

	if(count > 0 && step == 6)	count--;					//延时 34*15ms = 510ms
	if(count == 0 && step == 6) step++;
	
	if(front_data == 1001 && step == 7)	step++;		//X线1 中间
	if(front_data == 1110 && step == 8)	step++;		//出X线1
	
	if(front_data == 1001 && step == 9)	step++;		//X线2 中间
	if(front_data == 1110 && step == 10) step++, Set_Expect_Target_Speed(15);	//出X线2
	
	if(left_data == 0 && step == 11)					//X线3 中间 停车
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();					//恢复速度
		CAR_MODE = 0;
		if(!is_car_debug_mode)
			ARM_Action = 5;		//机械臂顶层第二次放置
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		说明：半成品区前往原料区
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_Area3_To_Area1(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)
		Car_Go_Right(), FIND_DRIVER = 1, CURRENT_DIRATION = 4, step = 1;	//右移 Y轴循迹
	Find();
	
	if(front_data == 1001 && step == 1)	step++;		//X线1 中间
	if(front_data == 1110 && step == 2)	step++;		//出 X线1
	
	if(front_data == 1001 && step == 3)	step++;		//X线2 中间
	if(front_data == 1110 && step == 4)	step++;		//出 X线2
	
	if(front_data == 1001 && step == 5)	step++;		//X线3 中间
	if(front_data == 1110 && step == 6)	step++;		//出 X线3
	
	if(front_data == 1001 && step == 7)	step++;		//X线4 中间
	if(front_data == 1110 && step == 8)	Set_Expect_Target_Speed(25), step++;		//出 X线4

	if(front_data == 1001 && step == 9)	
		Car_Go(), FIND_MODE=0, FIND_DRIVER = 0, CURRENT_DIRATION = 1, Expect_Target_Speed_Sta=0, Reset_Target_Speed(), step++, count+=11;	//X线5中间	前进	X轴巡线

	if(count > 0 && step == 10)	count--;					//延时 10*15ms = 150ms
	if(count == 0 && step == 10) step++;
	
	if(right_data == 1001 && step == 11)	step++;	//Y线1 中间
	if(right_data == 1110 && step == 12)	step++, Set_Expect_Target_Speed(12);	//出 Y线1
	
	if(right_data == 1001 && step == 13)
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta=0;
		Reset_Target_Speed();
		CAR_MODE = 0;
		if(!is_car_debug_mode)
			ARM_Action = 6;		//Y线2 中间	原料区 机械臂识别颜色 准备抓取动作
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		说明：原料区车往前一格 抓取中间物料
*		参数：step	<u8>	第几次向前走
*		返回：无
*===================================================================
*/
void Mode_Go_One_Aera1(u8 current_step)
{
	if(way2[current_step-1] == '2')							//判断是否抓取中间
	{
		left_data = Find_Get_Left();
		if(step == 0)
			Set_Expect_Target_Speed(15), Car_Go_Right(), FIND_DRIVER = 1, CURRENT_DIRATION = 4, step++;	//右平移 Y轴负半轴循迹
		Find();
		if(left_data == 0 && step == 1) count=16, step++;
		if(count > 0 && step == 2) count--;
		if(count == 0 && step == 2) step++;
		
		if(step == 3)	
		{
			step++;
			Car_Stop();
			Stop_Find();
			Mode_Init();
			Expect_Target_Speed_Sta = 0;
			Reset_Target_Speed();						//恢复速度
			CAR_MODE = 0;										//到达物料抓取位置 退出模式
			if(!is_car_debug_mode)
			{
				if(current_step==1)
					ARM_Action = 8;							//机械臂下层第一次抓取物料
				else if(current_step==2)
					ARM_Action = 10;						//机械臂下层第二次抓取物料
				else if(current_step==3)
					ARM_Action = 12;						//机械臂下层第三次抓取物料
			}
		}
	}
	else
	{
		right_data = Find_Get_Right();
		if(step == 0)
			Set_Expect_Target_Speed(15), Car_Go_Right(), FIND_DRIVER = 1, CURRENT_DIRATION = 4, step++;	//右平移 Y轴负半轴循迹
		Find();
		
		//if(right_data == 0 && step == 1)	
		
		if(right_data == 0 && step == 1) count=3, step++;
		
		if(count > 0 && step == 2) count--;
		if(count == 0 && step == 2) step++;		//3*15 30ms
		
		if(step == 3)
		{
			step++;
			Car_Stop();
			Stop_Find();
			Mode_Init();
			Expect_Target_Speed_Sta = 0;
			Reset_Target_Speed();						//恢复速度
			CAR_MODE = 0;										//到达物料抓取位置 退出模式
			if(!is_car_debug_mode)					//判断是否为车 DEBUG 模式
			{
				if(current_step==1)
					ARM_Action = 8;							//机械臂下层第一次抓取物料
				else if(current_step==2)
					ARM_Action = 10;						//机械臂下层第二次抓取物料
				else if(current_step==3)
					ARM_Action = 12;						//机械臂下层第三次抓取物料
			}
		}
	}

	Set_PID_PWM();
}


/*
*===================================================================
*		说明：原料区车后退一格
*		参数：step	<u8>	第几次后退
*		返回：无
*===================================================================
*/
void Mode_Back_One_Area1(u8 current_step)
{
	front_data = Find_Get_Front();
	
	if(step == 0)
		Set_Expect_Target_Speed(15), Car_Go_Left(), FIND_DRIVER = 3, CURRENT_DIRATION = 3, step++;	//左平移 Y轴正半轴循迹

	Find();
	
	if((front_data == 1001 || front_data == 11) && step == 1)	
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();						//恢复速度
		CAR_MODE = 0;										//到达物料抓取位置 退出模式
		if(!is_car_debug_mode)
		{
			if(current_step==1)
				ARM_Action = 9;							//机械臂存放 下层第一次抓取物料
			else if(current_step==2)
				ARM_Action = 11;						//机械臂存放 下层第二次抓取物料
//			else if(step==3)
//				ARM_Action = 13;						//机械臂存放 下层第三次抓取物料
		}
	}
	
	Set_PID_PWM();
}



/*
*===================================================================
*		说明：原料区车往前一格
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_Go_One_Step(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)
		Set_Expect_Target_Speed(15), Car_Go_Right(), FIND_DRIVER = 1, CURRENT_DIRATION = 4, step++;	//右平移 Y轴负半轴循迹

	Find();
	
	if(right_data == 0 && step == 1)	
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();						//恢复速度
		CAR_MODE = 0;										//到达物料抓取位置 退出模式
		if(!is_car_debug_mode)
			ARM_Action = 8;								//机械臂抓取物料
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		说明：原料区车后退一格
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_Back_One_Step(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)
		Set_Expect_Target_Speed(15), Car_Go_Left(), FIND_DRIVER = 3, CURRENT_DIRATION = 3, step++;	//左平移 Y轴正半轴循迹

	Find();
	
	if((front_data == 1001 || front_data == 11) && step == 1)	
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();						//恢复速度
		CAR_MODE = 0;			//到达物料抓取位置 退出模式
		if(!is_car_debug_mode)
			ARM_Action = 9;		//机械臂抓取物料
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		说明：粗加工区前往半成品区域	底层模式
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_Area2_To_Area3_Bottom(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	left_data = Find_Get_Left();
	
	if(step == 0)	Set_Expect_Target_Speed(35), Car_Back(), FIND_DRIVER = 2, CURRENT_DIRATION = 2, FIND_MODE = 1, step++;	//后退	X轴负半轴循迹
	
	Find();
	
	if(right_data == 1001 && step == 1)	step++;		//Y线1 中间
	if(right_data == 1110 && step == 2)	step++;		//出Y线1
	
	if(right_data == 1001 && step == 3)	step++;		//Y线2 中间
	if(right_data == 1110 && step == 4)	step++;		//出Y线2
	
	if((right_data == 1110 || right_data == 1001)&& step == 5)
		Set_Expect_Target_Speed(25), Car_Go_Left(), FIND_MODE = 1, FIND_DRIVER = 3, CURRENT_DIRATION = 3, count = 35, step++;	//Y线3 中间	左走 Y轴正半轴巡线

	if(count > 0 && step == 6)	count--;					//延时 34*15ms = 510ms
	if(count == 0 && step == 6) step++;
	
	if(front_data == 1001 && step == 7)	step++;		//X线1 中间
	if(front_data == 1110 && step == 8)	step++, Set_Expect_Target_Speed(15);		//出X线1
	
	if((front_data == 1001 || front_data == 111) && step == 9)	step++, Set_Expect_Target_Speed(7);		//X线2 中间

	if(front_data == 1110 && step == 10)					//X线2 上侧 停车
	{
		step++;
		Car_Stop();
		Stop_Find();
		Expect_Target_Speed_Sta = 0;
		Reset_Target_Speed();					//恢复速度
		CAR_MODE = 0;
		if(!is_car_debug_mode)
			ARM_Action = 15;						//机械臂底层半成品区放置
	}
	
	Set_PID_PWM();
}


/*
*===================================================================
*		说明：半成品区返回
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_Area3_Back(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Set_Expect_Target_Speed(35), Car_Back(), FIND_DRIVER=2, CURRENT_DIRATION=2, FIND_MODE=0, count=31, step++;	//后退 X轴负半轴循迹
	Find();
	
	if(count>0 && step == 1) count--;
	if(count == 0 && step == 1)step++;						//延时 30*15 450ms
	
	if(right_data == 1001 && step == 2)	step++;		//Y线1 中间
	if(right_data == 1110 && step == 3)	step++;		//出 Y线1
	
	if(right_data == 1001 && step == 4)	step++;		//Y线2 中间
	if(right_data == 1110 && step == 5)	step++;		//出 Y线2

	if(right_data == 1001 && step == 6)	Car_Go_Left(), FIND_DRIVER=3, CURRENT_DIRATION=3, count=31, step++;	//Y线3中间 左移 Y轴正半轴巡线

	if(count>0 && step == 7) count--;
	if(count == 0 && step == 7)step++;						//延时 30*15 450ms
	
	if(front_data == 1001 && step == 8)	step++;		//X线1 中间
	if(front_data == 1110 && step == 9)	step++;		//出 X线1
	
	if(right_data == 0 && step == 10)	Stop_Find(), Car_Back(), Set_Expect_Target_Speed(10), step++;	//出X线2
	
	if(front_data == 0 && step == 11)	Car_Stop(), Stop_Find(), CAR_MODE = 0, step++;	//前面与黑线重合 停车 到达返回区
	
	Set_PID_PWM();
}

void Mode_Init(void)
{
	step = 0;
	count = 10;
}




/********************机械臂部分控制************************/


//抓三个
void top_grasp_choose(u8* ptr)
{
	int i;
	for( i= 0;i<3;i++)
	{
		switch(ptr[i])
		{
			case '1':{top_grasp1();place_playload1(); break;}
			case '2':{top_grasp2();place_playload2(); break;}
			case '3':{top_grasp3();place_playload3();break;}	  
			default: break;		
	  }
}
}

//上层抓取
void top_grasp_choose1(u8*ptr)
{
  if(ptr[0]=='1')
		top_grasp1();
	else if(ptr[0]=='2')
     top_grasp2();
	else if(ptr[0]=='3')
			top_grasp3();
	place_playload1();
}
	

void top_grasp_choose2(u8*ptr)
{
	if(ptr[1]=='1')
		top_grasp1();
	else if(ptr[1]=='2')
     top_grasp2();
	else if(ptr[1]=='3')
			top_grasp3();
	place_playload2();

}

void top_grasp_choose3(u8*ptr)
{
	if(ptr[2]=='1')
		top_grasp1();
	else if(ptr[2]=='2')
     top_grasp2();
	else if(ptr[2]=='3')
			top_grasp3();
	place_playload3();

}

//下层抓取
void  under_grasp_choose1(u8 *ptr)
{
	//printf("1%c\n", ptr[0]);
	if(ptr[0]=='1')
		under_grasp1();
	else if(ptr[0]=='2')
     under_grasp2();
	else if(ptr[0]=='3')
			under_grasp3(), printf("抓红色");
//	place_playload1();

}

void  under_grasp_choose2(u8 *ptr)
{
		//printf("2%c\n", ptr[1]);

	
	if(ptr[1]=='1')
		under_grasp1();
	else if(ptr[1]=='2')
     under_grasp2(), printf("抓绿色");
	else if(ptr[1]=='3')
			under_grasp3();
//	place_playload2();

}

void  under_grasp_choose3(u8 *ptr)
{
		//printf("3%c\n", ptr[2]);

	if(ptr[2]=='1')
		under_grasp1(), printf("抓蓝色");
	else if(ptr[2]=='2')
     under_grasp2();
	else if(ptr[2]=='3')
			under_grasp3();
//	place_playload3();

}

void under_grasp_all(u8 * ptr)
{
	int i = 5;
	for(;i<8;i++)
	{
		switch(ptr[i])
		{
			case '1':{under_grasp1();place_playload1();break;}
			case '2':{under_grasp2();place_playload2();break;}
			case '3':{under_grasp3();place_playload3();break;}
			default : break;

		}
	}
}



//粗加工放置
void  First_choose_place1(u8* ptr,u8 mode)
{
	if(mode==1)
	{
	grasp_playload1();
	if(ptr[0]=='1')
		First_place2();
	else if(ptr[0]=='2')
     First_place3();
	else if(ptr[0]=='3')
			First_place1();
}
	else if(mode==2)
	{
		grasp_playload1();
	if(ptr[4]=='1')
		First_place2();
	else if(ptr[4]=='2')
     First_place3();
	else if(ptr[4]=='3')
			First_place1();
		
	}
}

void  First_choose_place2(u8* ptr,u8 mode)
{
	if(mode==1)
	{
	grasp_playload2();
	if(ptr[1]=='1')
		First_place2();
	else if(ptr[1]=='2')
     First_place3();
	else if(ptr[1]=='3')
			First_place1();
}
	else if(mode==2)
	{
		grasp_playload2();
	if(ptr[5]=='1')
		First_place2();
	else if(ptr[5]=='2')
     First_place3();
	else if(ptr[5]=='3')
			First_place1();
	}
	
}
void  First_choose_place3(u8* ptr,u8 mode)
{
	if(mode==1)
	{
	grasp_playload3();
	if(ptr[2]=='1')
		First_place2();
	else if(ptr[2]=='2')
     First_place3();
	else if(ptr[2]=='3')
			First_place1();
}
	else if(mode==2)
	{
			grasp_playload3();
	if(ptr[6]=='1')
		First_place2();
	else if(ptr[6]=='2')
     First_place3();
	else if(ptr[6]=='3')
			First_place1();
	}
}

void  First_place_all(u8* ptr,u8 mode)
{
	int i = 0;
		if(mode==1)
	{
	for(i=0;i<3;i++)
	{
			switch(ptr[i])
		{
			case '1':{grasp_playload1(); First_place2();break;}
			case '2':{grasp_playload2(); First_place3(); break;}
			case '3':{grasp_playload3(); First_place1();break;}
		  default:  break;
			    
		}
	}
}
	else if(mode==2)
	{
	for(i=4;i<7;i++)
	{
			switch(ptr[i])
		{
			case '1':{grasp_playload1(); First_place2();break;}
			case '2':{grasp_playload2();First_place3(); break;}
			case '3':{grasp_playload3(); First_place1();break;}
		  default:  break;
			    
		}
	}
}
}



//粗加工区夹取参数为qe_mes
void  cujiagong_choose_grasp1(u8 *ptr,u8 mode)
{
	if(mode==1)
	{
	if(ptr[0]=='1')
		cujiagongclip2();
	else if(ptr[0]=='2')
     cujiagongclip3();
	else if(ptr[0]=='3')
			cujiagongclip1();
	place_playload3();
		
		
	}
	else if(mode==2)
	{
			if(ptr[4]=='1')
		cujiagongclip2();
	else if(ptr[4]=='2')
     cujiagongclip3();
	else if(ptr[4]=='3')
			cujiagongclip1();
		place_playload3();

	}
	
}
void  cujiagong_choose_grasp2(u8 *ptr,u8 mode)
{
	if(mode==1)
	{
	if(ptr[1]=='1')
		cujiagongclip2();
	else if(ptr[1]=='2')
     cujiagongclip3();
	else if(ptr[1]=='3')
			cujiagongclip1();
	place_playload2();
		
		
	}
	else if(mode==2)
	{
			if(ptr[5]=='1')
		cujiagongclip2();
	else if(ptr[5]=='2')
     cujiagongclip3();
	else if(ptr[5]=='3')
			cujiagongclip1();
		place_playload2();

	}
}
void  cujiagong_choose_grasp3(u8 *ptr,u8 mode)
{
	if(mode==1)
	{
	if(ptr[2]=='1')
		cujiagongclip2();
	else if(ptr[2]=='2')
     cujiagongclip3();
	else if(ptr[2]=='3')
			cujiagongclip1();
	place_playload1();
	}
	else if(mode==2)
	{
			if(ptr[6]=='1')
		cujiagongclip2();
	else if(ptr[6]=='2')
     cujiagongclip3();
	else if(ptr[6]=='3')
			cujiagongclip1();
		place_playload1();

	}
}

//半成品上层放置
void place_top_product1(u8* ptr)
{
	
	
	grasp_playload3();
	if(ptr[0]=='1')
		Second_place2();
	else if(ptr[0]=='2')
     Second_place3();
	else if(ptr[0]=='3')
			Second_place1();
   
	
	
}

void place_top_product2(u8* ptr)
{

	grasp_playload2();
	if(ptr[1]=='1')
		Second_place2();
	else if(ptr[1]=='2')
     Second_place3();
	else if(ptr[1]=='3')
			Second_place1();
   
	
}

void place_top_product3(u8* ptr)
{

	grasp_playload1();
	if(ptr[2]=='1')
		Second_place2();
	else if(ptr[2]=='2')
     Second_place3();
	else if(ptr[2]=='3')
			Second_place1();
 
	
}


//半成品区下层放置
void place_under_product1(u8* ptr)
{
	
	grasp_playload3();
	if(ptr[4]=='1')
		Third_place2();
	else if(ptr[4]=='2')
     Third_place3();
	else if(ptr[4]=='3')
			Third_place1();
  
	
}

void place_under_product2(u8* ptr)
{
	
	grasp_playload2();
	if(ptr[5]=='1')
		Third_place2();
	else if(ptr[5]=='2')
     Third_place3();
	else if(ptr[5]=='3')
			Third_place1();

	
}

void place_under_product3(u8* ptr )
{

	grasp_playload1();
	if(ptr[6]=='1')
		Third_place2();
	else if(ptr[6]=='2')
     Third_place3();
	else if(ptr[6]=='3')
			Third_place1();
  
}
