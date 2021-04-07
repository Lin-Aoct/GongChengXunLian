#include "control.h"	

u8 CAR_MODE = 0;						//��־С��ģʽ
u8 step=0, count = 10;			//��־ִ�в����Լ���ʱ����
u16 front_data, right_data;	//ǰ���Һ���ѭ��ģ���������
	
/*
*===================================================================
*		˵������ʱ��6�жϷ����� 15ms ִ��һ��
*		��������
*		���أ���
*===================================================================
*/
void TIM6_DAC_IRQHandler(void)
{    
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)	//���ָ����TIM�жϷ������
	{
		switch(CAR_MODE)
		{
			case 0: break;
			case 1: Mode_Start(); break;						//����
			case 2: Mode_Go_Area1(); break;					//��ά�� 			-> 	���϶ѷ���
			case 3: Mode_Area1_To_Area2(); break;		//���϶ѷ���	->	�ּӹ���
			case 4: Mode_Area2_To_Area1(); break;		//�ּӹ���		->	���϶ѷ���
			case 5: Mode_Area2_To_Area3(); break;		//�ּӹ���		->	���Ʒ��
			case 6: Mode_Area3_To_Area2(); break;		//���Ʒ��		->	�ּӹ���
			case 7:; break;		//���Ʒ��		->	ԭ����
			case 8:; break;		//����ǰ��һ��
			case 9:; break;		//��������һ��
			case 10: Mode_Area1_To_Area2(); break;		//�ڶ��� ���϶ѷ���	->	�ּӹ���
			case 11: Mode_Area1_To_Area2(); break;		//�ڶ��� �ּӹ���		->	��Ʒ��
			case 12: Mode_Area1_To_Area2(); break;		//��Ʒ��	->	������
			default: break;
		}
		//printf("\nH1��%d, H2��%d, step��%d\n", front_data, right_data, step);	//��ӡ������Ϣ
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);			//���TIM6���жϴ�����λ
   }       	
}

void Cross_Road_Locate(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(front_data == 1001 && right_data == 1001) Car_Stop(), Stop_Find(); //CAR_MODE = 0;	//����
	else if(front_data == 1110 || front_data == 1100) Car_Go_Right();	//X��ƫ��
	else if(front_data == 111 || front_data == 11) Car_Go_Left();	//X��ƫ��
	else if(right_data == 1110 || right_data == 1100) Car_Back();	//Y��ƫ��
	else if(right_data == 111 || right_data == 11) Car_Go();	//Y��ƫ��
}

void Set_PID_PWM(void)
{
	ENCODER_DATA[0] = abs(Read_Encoder(2));
	ENCODER_DATA[1] = abs(Read_Encoder(3));
	ENCODER_DATA[2] = abs(Read_Encoder(4));
	ENCODER_DATA[3] = abs(Read_Encoder(5));
	
	if(IS_MOTOR_ALL_STOP == 0)
	{
		TIM8->CCR1 = MOTOR_PWM[0] + PID_Speed_Left_Front(ENCODER_DATA[0]);
		TIM8->CCR2 = MOTOR_PWM[1] + PID_Speed_Left_Behind(ENCODER_DATA[1]);
		TIM8->CCR4 = MOTOR_PWM[2] + PID_Speed_Right_Front(ENCODER_DATA[2]);
		TIM8->CCR3 = MOTOR_PWM[3] + PID_Speed_Right_Behind(ENCODER_DATA[3]);
	}
	
	printf("������[%d %d %d %d]\t", ENCODER_DATA[0], ENCODER_DATA[1], ENCODER_DATA[2], ENCODER_DATA[3]);
	printf("PWM[%d %d %d %d]\t", TIM8->CCR1, TIM8->CCR2, TIM8->CCR4, TIM8->CCR3);
	printf("TS[%.0f]", speed_target);	//��ӡĿ���ٶ�
	printf("\n");
}

/*
*===================================================================
*		˵��������ģʽ��ǰ����ά��ɨ������
*		��������
*		���أ���
*===================================================================
*/
void Mode_Start(void)
{
	//Car_Go();
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Go_Left();		//��ƽ��
	
	if(front_data == 1001 && step == 0)	Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, step = 1;	//ǰ�洦������
	Find();
	if(right_data == 1001 && step == 1)	step = 2;	//��1�м�
	
	if(right_data == 1110 && step == 2)	step = 3;	//����1
	
	if(right_data == 1001 && step == 3)	step = 4;	//��2�м�
	
	if(right_data == 1110 && step == 4)	count = 3, step = 5;	//����2
		
	if(count > 0 && step == 5)	count--;						//6*15ms = 150ms

//	if(count <= 0 && step == 5)	Car_Go_Left(), Stop_Find(), step = 6;	//����
	
	if(count == 0 && step == 5)	
	{
		Car_Stop();				//�˳�����ģʽ
		CAR_MODE = 0;
		ARM_Action = 1;		//��е��ɨ��
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		˵������ά��ɨ����Ϻ� ǰ�����϶ѷ�����
*		��������
*		���أ���
*===================================================================
*/
void Mode_Go_Area1(void)
{
	//Car_Back();
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, step = 1;	//ǰ�洦������
	Find();
	
	if(right_data == 1001 && step == 1)	step = 2;	//��1�м�
	if(right_data == 1110 && step == 2)	step = 3;	//����1
	
	if(right_data == 1001 && step == 3)	step = 4;	//��2�м�
	if(right_data == 1110 && step == 4)	step = 5;	//����2
	
	if(right_data == 1001 && step == 5)	step = 6;	//��3�м�
	if(right_data == 1110 && step == 6)	step = 7, speed_target-=10;	//����3
	
	if((right_data == 1001 || right_data == 11) && step == 7)	step = 8, Car_Stop();	//������4 ��ƽ��
	
	if(step == 8)	Cross_Road_Locate();
//	if((right_data == 1001 || right_data == 11) && step == 7)	step = 8, Car_Go_Left(), FIND_DRIVER=1, CURRENT_DIRATION=3;	//������4 ��ƽ��

//	if(right_data == 0000 && step == 8)	
//	{
//		step = 9;
//		Car_Stop();
//		Stop_Find();
//		speed_target+=10;
//		ARM_Action = 2;	//��е��ץȡ����
//		CAR_MODE = 0;	//��������ץȡλ�� �˳�ģʽ
//	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		˵�������϶ѷ�����ǰ���ּӹ���
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area1_To_Area2(void)
{
	//Car_Go_Left();
	
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Go_Left(), FIND_DRIVER=1, CURRENT_DIRATION=3, step = 1;	//��ƽ��	Y��ѭ��
	Find();
	
	if(front_data == 1001 && step == 1)	step = 2;	//��1�м�
	if(front_data == 1110 && step == 2)	step = 3;	//����1
	
	if(front_data == 1001 && step == 3)	step = 4;	//��2�м�
	if(front_data == 1110 && step == 4)	step = 5;	//����2
	
	if(front_data == 1001 && step == 5)						//��3�м�
	{
		step = 6;
		speed_target-=10, Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1;	//������3 ���� ��ǰ�˶� X��Ѳ��
	}

	if(front_data == 0000 && step == 6)
	{
		step = 7;
		Car_Stop();
		Stop_Find();
		ARM_Action = 4;								//��е�۵�һ�η�������
		speed_target+=10;
		CAR_MODE = 0;									//�ּӹ���
	}
	
	Set_PID_PWM();
}

/*
*===================================================================
*		˵�����ּӹ���ǰ�����϶ѷ�����
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area2_To_Area1(void)
{

	//Car_Go_Right();
//	if(step == 0)	Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, step = 1;	//����	X��ѭ��
//	Find();

//	MOTOR_PWM_Out(MOTOR_PWM[0], MOTOR_PWM[1], MOTOR_PWM[2], MOTOR_PWM[3]);
	
	Cross_Road_Locate();
	
	Set_PID_PWM();

}

/*
*===================================================================
*		˵�����ּӹ���ǰ�����Ʒ����1
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area2_To_Area3(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Back(), FIND_DRIVER=0, CURRENT_DIRATION=2, step = 1;	//����	X��ѭ��
	Find();
	
	if(right_data == 1001 && step == 1)	Car_Go_Left(), FIND_DRIVER=1, CURRENT_DIRATION=3, step = 2;	//Y�����м� ��ƽ�� Y��ѭ��
	
	if(front_data == 1001 && step == 2)	step = 3;	//��1�м�
	if(front_data == 1110 && step == 3)	step = 4;	//����1
	
	if(front_data == 1001 && step == 4)	step = 5;	//��2�м�
	if(front_data == 1110 && step == 5)	step = 6;	//����2

	if(front_data == 1001 && step == 6)	Car_Back(), FIND_DRIVER=0, CURRENT_DIRATION=2, step = 7;	//X��3�м�	����	X��Ѳ��
	
	if(right_data == 1001 && step == 7)	step = 8;	//Y��1�м�
	if(right_data == 1110 && step == 8)	step = 9;	//��Y��1
	
	if(right_data == 1001 && step == 9)	step = 10;		//Y��2�м�
	if(right_data == 1110 && step == 10)	step = 11;	//��Y��2
	
	if(right_data == 1001 && step == 11)
	{
		Car_Stop();
		Stop_Find();
		CAR_MODE = 0;
		ARM_Action = 5;
		step = 12;		//Y��3�м�	���Ʒ��
	}
}

/*
*===================================================================
*		˵�������Ʒ����1ǰ���ּӹ���
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area3_To_Area2(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Go(), FIND_DRIVER=0, CURRENT_DIRATION=1, step = 1;	//ǰ��	X��ѭ��
	Find();
	
	if(right_data == 1001 && step == 1)	step = 2;	//Y��1�м�
	if(right_data == 1110 && step == 2)	step = 3;	//��Y��1
	
	if(right_data == 1001 && step == 3)	step = 4;	//Y��2�м�
	if(right_data == 1110 && step == 4)	step = 5;	//��Y��2

	if(right_data == 1001 && step == 5)	Car_Go_Right(), FIND_DRIVER=1, CURRENT_DIRATION=4, step = 6;	//Y��3�м�	����	Y��Ѳ��
	
	if(front_data == 1001 && step == 6)	step = 7;	//X��1�м�
	if(front_data == 1110 && step == 7)	step = 8;	//��X��1
	
	if(front_data == 1001 && step == 8)	step = 9;		//X��2�м�
	if(front_data == 1110 && step == 9)	step = 10;	//��X��2
	
	if(front_data == 1001 && step == 10)	Car_Stop(), Stop_Find(), CAR_MODE = 0, step = 11;		//Y��3�м�	���Ʒ��
}

/*
*===================================================================
*		˵�������Ʒ����2����
*		��������
*		���أ���
*===================================================================
*/
void Mode_Area3_2_Back(void)
{
	front_data = Find_Get_Front();
	right_data = Find_Get_Right();
	
	if(step == 0)	Car_Back(), FIND_DRIVER=0, CURRENT_DIRATION=2, step = 1;	//����	X��ѭ��
	Find();
	
	if(right_data == 1001 && step == 1)	step = 2;	//Y��1�м�
	if(right_data == 1110 && step == 2)	step = 3;	//��Y��1
	
	if(right_data == 1001 && step == 3)	step = 4;	//Y��2�м�
	if(right_data == 1110 && step == 4)	step = 5;	//��Y��2

	if(right_data == 1001 && step == 5)	Car_Go_Right(), FIND_DRIVER=1, CURRENT_DIRATION=4, step = 6;	//Y��3�м�	����	Y��Ѳ��
	
	if(front_data == 1001 && step == 7)	step = 8;	//X��1�м�
	if(front_data == 1110 && step == 8)	step = 9;	//��X��1
	
	if(front_data == 1001 && step == 9)	step = 10;		//X��2�м�
	if(front_data == 1110 && step == 10)	step = 11;	//��X��2
	
	if(front_data == 1001 && step == 11)	Car_Stop(), Stop_Find(), CAR_MODE = 0, step = 12;		//Y��3�м�	���Ʒ��
}

void Mode_Init(void)
{
	step = 0;
	count = 10;
}








//ץ����
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

//�ϲ�ץȡ
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

//�²�ץȡ
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



//�ּӹ�����
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



//�ּӹ�����ȡ����Ϊqe_mes
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

//���Ʒ�ϲ����
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


//���Ʒ���²����
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

























