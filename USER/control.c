#include "control.h"	

u8 CAR_MODE = 0;						//标志小车模式
u8 step=0, count = 10;			//标志执行步骤以及计时变量
u16 front_data, right_data;	//前、右红外循迹模块读数变量
	
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
			case 1: Mode_Start(); break;						//出发
			case 2: Mode_Go_Area1(); break;					//二维码 			-> 	物料堆放区
			case 3: Mode_Area1_To_Area2(); break;		//物料堆放区	->	粗加工区
			case 4: Mode_Area2_To_Area1(); break;		//粗加工区		->	物料堆放区
			case 5: Mode_Area2_To_Area3(); break;		//粗加工区		->	半成品区
			case 6: Mode_Area3_To_Area2(); break;		//半成品区		->	粗加工区
			case 7:; break;		//半成品区		->	原料区
			case 8:; break;		//车往前走一格
			case 9:; break;		//车往后退一格
			case 10: Mode_Area1_To_Area2(); break;		//第二次 物料堆放区	->	粗加工区
			case 11: Mode_Area1_To_Area2(); break;		//第二次 粗加工区		->	成品区
			case 12: Mode_Area1_To_Area2(); break;		//成品区	->	返回区
			default: break;
		}
		printf("\nH1：%d, H2：%d, step：%d\n", front_data, right_data, step);	//打印调试信息
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);			//清除TIM6的中断待处理位
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
//	ENCODER_DATA[0] = Read_Encoder(2);
//	ENCODER_DATA[1] = Read_Encoder(3);
//	ENCODER_DATA[2] = Read_Encoder(4);
//	ENCODER_DATA[3] = Read_Encoder(5);
//	
//	//Set_MOTOR_Left_Front(GO);
//	MOTOR_PWM[0] = abs(PID_Speed_Left_Front(ENCODER_DATA[0]));
//	MOTOR_PWM[1] = PID_Speed_Left_Front(ENCODER_DATA[1]);
//	MOTOR_PWM[2] = PID_Speed_Left_Front(ENCODER_DATA[2]);
//	MOTOR_PWM[3] = PID_Speed_Left_Front(ENCODER_DATA[3]);
//	Car_Go();
	
//	printf("编码器[%d %d %d %d]\t", ENCODER_DATA[0], ENCODER_DATA[1], ENCODER_DATA[2], ENCODER_DATA[3]);// Find_Test();
//	printf("PWM[");
//	for(count=0; count<=3; count++)
//		printf("%d ", MOTOR_PWM[count]);
//	printf("]");
	
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Go_Left();		//左平移
	
	if(front_data == 1001 && step == 0)	Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, step = 1;	//前面处于线中
	Find();
	if(right_data == 1001 && step == 1)	step = 2;	//线1中间
	
	if(right_data == 1110 && step == 2)	step = 3;	//出线1
	
	if(right_data == 1001 && step == 3)	step = 4;	//线2中间
	
	if(right_data == 1110 && step == 4)	count = 3, step = 5;	//出线2
		
	if(count > 0 && step == 5)	count--;						//6*15ms = 150ms

//	if(count <= 0 && step == 5)	Car_Go_Left(), Stop_Find(), step = 6;	//左移

	if(count == 0 && step == 5)	
	{
		Car_Stop();										//退出出发模式
		CAR_MODE = 0;
		ARM_Action =1;		//机械臂扫码
	}
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
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, step = 1;	//前面处于线中
	Find();
	
	if(right_data == 1001 && step == 1)	step = 2;	//线1中间
	if(right_data == 1110 && step == 2)	step = 3;	//出线1
	
	if(right_data == 1001 && step == 3)	step = 4;	//线2中间
	if(right_data == 1110 && step == 4)	step = 5;	//出线2
	
	if(right_data == 1001 && step == 5)	step = 6;	//线3中间
	if(right_data == 1110 && step == 6)	step = 7;	//出线3
	
	if((right_data == 1001 || right_data == 0011) && step == 7)	step = 8, MOTOR_Speed_Down(30), Car_Go_Left(), FIND_DRIVER=1, CURRENT_DIRATION=3;	//碰到线4 左平移

	if(right_data == 0000 && step == 8)	
	{
		step = 9;
		Car_Stop();
		Stop_Find();
		MOTOR_Speed_Up(30);
		ARM_Action = 2;	//机械臂抓取物料
		CAR_MODE = 0;	//到达物料抓取位置 退出模式
	}
}

/*
*===================================================================
*		说明：物料堆放区域前往粗加工区
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_Area1_To_Area2(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Go_Left(), FIND_DRIVER=1, CURRENT_DIRATION=3, step = 1;	//左平移	Y轴循迹
	Find();
	
	if(front_data == 1001 && step == 1)	step = 2;	//线1中间
	if(front_data == 1110 && step == 2)	step = 3;	//出线1
	
	if(front_data == 1001 && step == 3)	step = 4;	//线2中间
	if(front_data == 1110 && step == 4)	step = 5;	//出线2
	
	if(front_data == 1001 && step == 5)						//线3中间
	{
		step = 6;
		MOTOR_Speed_Down(3000), Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1;	//碰到线3 减速 向前运动 X轴巡线
	}

	if(front_data == 0000 && step == 6)
	{
		step = 7;
		Car_Stop();
		Stop_Find();
		ARM_Action = 4;								//机械臂第一次放置物料
		MOTOR_Speed_Up(3000);
		CAR_MODE = 0;									//粗加工区
	}
}

/*
*===================================================================
*		说明：粗加工区前往物料堆放区域
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_Area2_To_Area1(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, step = 1;	//后退	X轴循迹
	Find();

//	if(front_data == 1001 && step == 2)	step = 3;	//线1中间
//	if(front_data == 1110 && step == 3)	step = 4;	//出线1
//	
//	if(front_data == 1001 && step == 4)	step = 5;	//线2中间
//	if(front_data == 1110 && step == 5)	step = 6;	//出线2

//	if(right_data == 0000 && step == 6)	
//	{
//		step = 7;
//		Car_Stop();
//		Stop_Find();
//		USART_SendData(UART4, '4');
//		CAR_MODE = 0;	//原料区
//	}
}

/*
*===================================================================
*		说明：粗加工区前往半成品区域1
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_Area2_To_Area3(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Back(), FIND_DRIVER=0, CURRENT_DIRATION=2, step = 1;	//后退	X轴循迹
	Find();
	
	if(right_data == 1001 && step == 1)	Car_Go_Left(), FIND_DRIVER=1, CURRENT_DIRATION=3, step = 2;	//Y轴线中间 左平移 Y轴循迹
	
	if(front_data == 1001 && step == 2)	step = 3;	//线1中间
	if(front_data == 1110 && step == 3)	step = 4;	//出线1
	
	if(front_data == 1001 && step == 4)	step = 5;	//线2中间
	if(front_data == 1110 && step == 5)	step = 6;	//出线2

	if(front_data == 1001 && step == 6)	Car_Back(), FIND_DRIVER=0, CURRENT_DIRATION=2, step = 7;	//X线3中间	后退	X轴巡线
	
	if(right_data == 1001 && step == 7)	step = 8;	//Y线1中间
	if(right_data == 1110 && step == 8)	step = 9;	//出Y线1
	
	if(right_data == 1001 && step == 9)	step = 10;		//Y线2中间
	if(right_data == 1110 && step == 10)	step = 11;	//出Y线2
	
	if(right_data == 1001 && step == 11)
	{
		Car_Stop();
		Stop_Find();
		CAR_MODE = 0;
		ARM_Action = 5;
		step = 12;		//Y线3中间	半成品区
	}
}

/*
*===================================================================
*		说明：半成品区域1前往粗加工区
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_Area3_To_Area2(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, step = 1;	//前进	X轴循迹
	Find();
	
	if(right_data == 1001 && step == 1)	step = 2;	//Y线1中间
	if(right_data == 1110 && step == 2)	step = 3;	//出Y线1
	
	if(right_data == 1001 && step == 3)	step = 4;	//Y线2中间
	if(right_data == 1110 && step == 4)	step = 5;	//出Y线2

	if(right_data == 1001 && step == 5)	Car_Go_Right(), FIND_DRIVER=1, CURRENT_DIRATION=4, step = 6;	//Y线3中间	右移	Y轴巡线
	
	if(front_data == 1001 && step == 6)	step = 7;	//X线1中间
	if(front_data == 1110 && step == 7)	step = 8;	//出X线1
	
	if(front_data == 1001 && step == 8)	step = 9;		//X线2中间
	if(front_data == 1110 && step == 9)	step = 10;	//出X线2
	
	if(front_data == 1001 && step == 10)	Car_Stop(), Stop_Find(), CAR_MODE = 0, step = 11;		//Y线3中间	半成品区
}

/*
*===================================================================
*		说明：半成品区域2返回
*		参数：无
*		返回：无
*===================================================================
*/
void Mode_Area3_2_Back(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Back(), FIND_DRIVER=0, CURRENT_DIRATION=2, step = 1;	//后退	X轴循迹
	Find();
	
	if(right_data == 1001 && step == 1)	step = 2;	//Y线1中间
	if(right_data == 1110 && step == 2)	step = 3;	//出Y线1
	
	if(right_data == 1001 && step == 3)	step = 4;	//Y线2中间
	if(right_data == 1110 && step == 4)	step = 5;	//出Y线2

	if(right_data == 1001 && step == 5)	Car_Go_Right(), FIND_DRIVER=1, CURRENT_DIRATION=4, step = 6;	//Y线3中间	右移	Y轴巡线
	
	if(front_data == 1001 && step == 7)	step = 8;	//X线1中间
	if(front_data == 1110 && step == 8)	step = 9;	//出X线1
	
	if(front_data == 1001 && step == 9)	step = 10;		//X线2中间
	if(front_data == 1110 && step == 10)	step = 11;	//出X线2
	
	if(front_data == 1001 && step == 11)	Car_Stop(), Stop_Find(), CAR_MODE = 0, step = 12;		//Y线3中间	半成品区
}

void Mode_Init(void)
{
	step = 0;
	count = 10;
}








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
	if(ptr[4]=='1')
		under_grasp1();
	else if(ptr[4]=='2')
     under_grasp2();
	else if(ptr[4]=='3')
			under_grasp3();
//	place_playload1();

}

void  under_grasp_choose2(u8 *ptr)
{
	if(ptr[5]=='1')
		under_grasp1();
	else if(ptr[5]=='2')
     under_grasp2();
	else if(ptr[5]=='3')
			under_grasp3();
//	place_playload2();

}

void  under_grasp_choose3(u8 *ptr)
{
	if(ptr[6]=='1')
		under_grasp1();
	else if(ptr[6]=='2')
     under_grasp2();
	else if(ptr[6]=='3')
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
	place_playload1();
		
		
	}
	else if(mode==2)
	{
			if(ptr[4]=='1')
		cujiagongclip2();
	else if(ptr[4]=='2')
     cujiagongclip3();
	else if(ptr[4]=='3')
			cujiagongclip1();
		place_playload1();

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
	place_playload3();
	}
	else if(mode==2)
	{
			if(ptr[6]=='1')
		cujiagongclip2();
	else if(ptr[6]=='2')
     cujiagongclip3();
	else if(ptr[6]=='3')
			cujiagongclip1();
		place_playload3();

	}
}

//半成品上层放置
void place_top_product1(u8* ptr)
{
	
	
	grasp_playload1();
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

	grasp_playload3();
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
	
	grasp_playload1();
	if(ptr[0]=='1')
		Third_place2();
	else if(ptr[0]=='2')
     Third_place3();
	else if(ptr[0]=='3')
			Third_place1();
  
	
}

void place_under_product2(u8* ptr)
{
	
	grasp_playload2();
	if(ptr[1]=='1')
		Third_place2();
	else if(ptr[1]=='2')
     Third_place3();
	else if(ptr[1]=='3')
			Third_place1();

	
}

void place_under_product3(u8* ptr )
{
	
	
	grasp_playload3();
	if(ptr[2]=='1')
		Third_place2();
	else if(ptr[2]=='2')
     Third_place3();
	else if(ptr[2]=='3')
			Third_place1();
  
	
	
}

























