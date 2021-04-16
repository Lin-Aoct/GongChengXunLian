#include "grasp.h"

/******************************************
*************************��е�۽Ƕ�******
*******************************************/
u16 Arm_open = 642;

//�ϲ�ץȡ
 u16 top_grasp1_arm1 = 852,top_grasp1_arm2 = 933,\
			top_grasp1_arm3 = 632,top_grasp1_arm4 = 469;
			
 u16 top_grasp2_arm1 = 832,top_grasp2_arm2 = 967,\
			top_grasp2_arm3 = 652,top_grasp2_arm4 = 400;
			
 u16 top_grasp3_arm1 = 904,top_grasp3_arm2 = 766,\
			top_grasp3_arm3 = 548,top_grasp3_arm4 = 343;

//�²�ץȡ
 u16 under_grasp1_arm1 = 717, under_grasp1_arm2 =916, \
			under_grasp1_arm3 = 495, under_grasp1_arm4 = 458;
			
 u16 under_grasp2_arm1 = 745, under_grasp2_arm2 = 915, \
				under_grasp2_arm3 = 515, under_grasp2_arm4 = 400;
				
 u16 under_grasp3_arm1 = 755, under_grasp3_arm2 =864 ,\
			under_grasp3_arm3 = 482, under_grasp3_arm4 = 345;

//�ּӹ���
 u16 first_plcace1_arm1 = 655,first_plcace1_arm2 = 945,\
			first_plcace1_arm3 = 475,first_plcace1_arm4 = 740;
			
 u16 first_plcace2_arm1 = 587,first_plcace2_arm2 = 1037,\
			first_plcace2_arm3 = 493,first_plcace2_arm4 = 670;
			
 u16 first_plcace3_arm1 = 667,first_plcace3_arm2 = 945,
			first_plcace3_arm3 = 476,first_plcace3_arm4 = 599;

//���Ʒ���ϲ�
 u16 second_place1_arm1 = 762,second_place1_arm2 = 861,\
			second_place1_arm3 = 479,second_place1_arm4 = 1021;
			
 u16 second_place2_arm1 = 689,second_place2_arm2 = 990,\
			second_place2_arm3 = 539,second_place2_arm4 = 956;
			
 u16 second_place3_arm1 = 708,second_place3_arm2 = 970,\
			second_place3_arm3 = 538,second_place3_arm4 = 889;

//���Ʒ���²�
 u16 third_place1_arm1 = 729,third_place1_arm2 = 877,\
			third_place1_arm3 = 458,third_place1_arm4 = 1003;
			
 u16 third_place2_arm1 = 639,third_place2_arm2 = 974,\
			third_place2_arm3 = 479,third_place2_arm4 = 939;	
			
 u16 third_place3_arm1 = 692,third_place3_arm2 = 917,\
		 third_place3_arm3 = 489,third_place3_arm4 = 871;

		 
 //���Ʒ�����
 u16 Place_Plus1_arm0 = 642,Place_Plus1_arm1 = 863,\
				Place_Plus1_arm2 = 790,Place_Plus1_arm3 = 530,Place_Plus1_arm4  =1022 ;
				
u16 Place_Plus2_arm0 = 642,Place_Plus2_arm1 = 758,\
			Place_Plus2_arm2 = 1020,Place_Plus2_arm3 = 635,Place_Plus2_arm4 = 957;
 
u16 Place_Plus3_arm0 = 642,Place_Plus3_arm1 = 823,\
			Place_Plus3_arm2 = 925,Place_Plus3_arm3 = 600,Place_Plus3_arm4 = 889;
			

 //��һ������̨�����ؽڵ�ֵ
 u16 place1_arm1 = 975;
 u16 place1_arm2 = 1192;
 u16 place1_arm3 = 1012;
 u16 place1_arm4 = 265;
 
 //�ڶ�������̨�����ؽڵ�ֵ
 u16 place2_arm1 = 959;
 u16 place2_arm2 = 1215;
 u16 place2_arm3 = 1031;
 u16 place2_arm4 = 1183;
 
 //����������̨�����ؽڵ�ֵ
 u16 place3_arm1 = 948;
 u16 place3_arm2 = 1189;
 u16 place3_arm3 = 1006;
 u16 place3_arm4 = 1091;

//��е�۵���
 void Arm3_low_speed1(unsigned int target, unsigned int curt)
{
	int tem;
	for(tem=curt;tem>=target;tem-=3)		
	{
		Arm3 = tem;
		delay_ms(9);
	}
	
}


 void Arm3_low_speed2(unsigned int target, unsigned int curt)
{
	int tem;
	for(tem=curt;tem<=target;tem+=2)		
	{
		Arm3 = tem;
		delay_ms(9);
	}
	
}

 void Arm3_low_speed3(unsigned int target, unsigned int curt)
{
	int tem;
	for(tem=curt;tem<=target;tem+=2)		
	{
		Arm3 = tem;
		delay_ms(9);
	
}

}
 void Arm1_low_speed(unsigned int target,unsigned int curt)
 {
	 int tem;
	for(tem=curt;tem<=target;tem+=3)		
	{
		Arm1  = tem;
		delay_ms(8);
	}
 }
 
 
 //����̨���ü���
 void Arm2_low_speed(unsigned int target,unsigned int curt)
 {
	 int tem;
	for(tem=curt;tem<=target;tem+=2)		
	{
		Arm2  = tem;
		delay_ms(11);
	}
 }



 //����е�ۼ���
  void  place_plus_arm3_lowspeed(unsigned int target, unsigned int curt)
 {
	 int tem;
	for(tem=curt;tem>=target;tem-=2)		
	{
		Arm3 = tem;
		delay_ms(12);
	}
	
 }

 //endif
 
 
 //��е�����ֶ���
 void Arm_back(void)
 {
	 
	Arm3 = 800;
	delay_ms(50);
	Arm2 = 1130;
	delay_ms(100);
	Arm3_low_speed3(915,850);
    Arm1_low_speed(929,900);	 
	delay_ms(200);
 }
 void third_place3_armback()
 {
	Arm4 = 998;
	Arm3 = 800;
	delay_ms(50);
	Arm2 = 1130;
	delay_ms(100);
	Arm3_low_speed3(907,850);
  Arm1_low_speed(929,900);	 
	delay_ms(200);
 }
 //�²�����
 void Arm_back1(void)
 {
	 Arm3 = 800;
	delay_ms(50);
	Arm2 = 1060;
	delay_ms(100);
	Arm3_low_speed3(925,850);
  Arm1_low_speed(959,850);
 }
 
 void under_Arm_back()
 {
	 Arm1= 662;
	 delay_ms(100);
	 Arm3 = 850;
	 delay_ms(50);
   Arm1_low_speed(959,850);
	delay_ms(100);
	Arm3_low_speed3(925,850);
	 Arm2 = 1060;

 
 }
 //�м䶯��
 void middle_state()
 {
	  Arm1 = 959;
	 delay_ms(30);
	  Arm2 = 1060;
	 delay_ms(70);
	 Arm3 = 907;
	 delay_ms(100);
	
	 
 }
 //��̨800
  void place_back()
 {
	
	 Arm2 = 1060;
	 Arm1 = 959;
	 delay_ms(300);
	 Arm3 = 907;
	 delay_ms(500);
	 Arm4 = 800;
	 delay_ms(300);
 }

//����������
 void Plus_arm_back()
 {
	 	 Arm0 = 600;
	 delay_ms(50);
	 Arm3 =  800;
	 delay_ms(100);
	 Arm2 = 1082;
	 delay_ms(100);
	 Arm3_low_speed3(925,850);
	 Arm1_low_speed(929,900);	 
	 
 }
 
 
 
 //���õ�һ����鵽
 void place_playload1()
 {
	 //��
	 	Arm4 = place1_arm4;
	 delay_ms(500);
	 Arm1 = place1_arm1;
	 delay_ms(100);
	 Arm3 = place1_arm3;
	 delay_ms(100);
	 Arm2_low_speed(place1_arm2,1060);
	 delay_ms(50);
	 
	 Arm0 = Arm_open;//צ��΢΢��
	 delay_ms(300);
	 //��
	
	 Arm2 = 1060;
	 Arm1 = 959;
	 delay_ms(50);
	 Arm3 = 907;
	 delay_ms(500);
	 Arm4 = 430;
	 delay_ms(200);
	 Arm0 = 600;
	 
	 
 }
  void place_playload2()
 {
	 //��
	 Arm4 = place2_arm4;
	 delay_ms(900);
	 Arm1 = place2_arm1;
	 delay_ms(150);
	 Arm3 = place2_arm3;
	 delay_ms(100);
	 Arm2_low_speed(place2_arm2,1060);
	 delay_ms(50);
	
	 Arm0 = Arm_open;//צ��΢΢��
	 delay_ms(300);
	 
	 place_back();
	 Arm0 = 600;

	 
	 
 }
  void place_playload3()
 {
	 //��
	  Arm4 = place3_arm4;
	 delay_ms(800);
	 Arm1 = place3_arm1;
	 delay_ms(100);
	 Arm3 = place3_arm3;
	 delay_ms(50);
	 Arm2_low_speed(place3_arm2,1060);
	 delay_ms(50);
	
	 Arm0 = Arm_open;//צ��΢΢��
	 delay_ms(300);
	 
	 place_back();
	 Arm0 = 600;


	 
 }
 //����̨��һ������ȡ
 
 void grasp_playload1()
 {
	  //ץ
     Arm0= Arm_open;
	 Arm4 = place1_arm4;
	 delay_ms(700);
	 Arm1 = place1_arm1;
	 delay_ms(50);
	 Arm3 = place1_arm3;
	 delay_ms(50);
	 Arm2_low_speed(place1_arm2,1060);
	 delay_ms(100);
	 Arm0 = 740;
	 delay_ms(300);
	 //��
	
	
	 Arm1 = 959;
	 delay_ms(50);
	 Arm2 = 1060;
	 delay_ms(50);
	 Arm3 = 907;
	 delay_ms(50);
	 Arm4 = 430;
	 delay_ms(50);
	
	 
	 
 }
 
 void grasp_playload2()
 {
	 	  //ץ
	 delay_ms(50);
	 Arm0 = Arm_open;
	 Arm4 = place2_arm4;
	 delay_ms(900);
	 Arm1 = place2_arm1;
	 delay_ms(50);
	 Arm3 = place2_arm3;
	 delay_ms(100);  
	 Arm2_low_speed(place2_arm2,1060);
	 delay_ms(50); 
	 Arm0 = 740;
	 delay_ms(300);
	 
	 place_back();
	 
 }
 
 void grasp_playload3()
 {
	 Arm0 = Arm_open;
	 Arm4 = place3_arm4;
	 delay_ms(900);
	 Arm1 = place3_arm1;
	 delay_ms(50);
	 Arm3 = place3_arm3;
	 delay_ms(100);  
	 Arm2_low_speed(place3_arm2,1060);
	 delay_ms(50);
	 Arm0 = 740;
	 delay_ms(300);
	 
	 place_back();
	 
 }

//��λ��е��״̬
void reset_state()
{
	
	Arm0 = 600;//�Ƕ�1
	Arm2 = 1034;//5
	delay_ms(100);
	Arm3 = 1078;//
	delay_ms(300);
	Arm4 = 430;
	delay_ms(500);
	Arm1 = 1250;//2		 
}
//end

//��ά��ʶ������
void scan_qr_on(void)
{
	Arm3 = 1021;
	delay_ms(500);
	Arm4 = 448;
	delay_ms(500);
	Arm0 = 600;
	delay_ms(100);
	Arm1 = 900;
	delay_ms(200);
	Arm2 = 1076;
	Arm1 = 1220;
	
}


void scan_qr_off(void)
{
	//��ά��ɨ����ɺ�ָ���ɨ���ϲ���ɫ����
	Arm4 =  439;
	delay_ms(800);
	Arm3_low_speed2(750,514);
	delay_ms(300);
	Arm2 = 1034;
	delay_ms(800);
	Arm3 = 1078;
	delay_ms(800);
	Arm1 = 1250;
	delay_ms(500);
	
}



//���ʶ�������ϲ�
void scan_block_top(void)
{
	Arm0 = 600;
	Arm4 =  448;
	delay_ms(20);
	Arm1 = 1250;
	delay_ms(50);
	Arm3 = 1042;
	delay_ms(50);
	Arm2 = 1034;
	delay_ms(50);
}


//���ʶ�������²�
void scan_block_under(void)
{
	Arm0 = 600;
	Arm4 =  457;
	Arm1 = 1172;
	delay_ms(50);
	Arm3 = 949;
	delay_ms(100);
	Arm2 = 1034;
	delay_ms(100);
}

  
//����ץȡ���
void top_grasp1()
{
	//ץ
	Arm4 = top_grasp1_arm4;
	delay_ms(400);
	Arm1 = top_grasp1_arm1;
	delay_ms(50);
	Arm3 = 800;
	delay_ms(300);
	Arm2 = top_grasp1_arm2;
	delay_ms(400);
	Arm3_low_speed1(top_grasp1_arm3,710);//
	delay_ms(100);
	Arm0 = 740;
	delay_ms(200);
	
	
	//��

	Arm_back();

	
}




//�м�
void top_grasp2(void)
{
	//ץ
	Arm4 = top_grasp2_arm4;
	delay_ms(400);
	Arm1 = top_grasp2_arm1;
	delay_ms(50);
	Arm3 = 800;
	delay_ms(300);
	Arm2 = top_grasp2_arm2;
	delay_ms(300);
	Arm3_low_speed1(top_grasp2_arm3,710);
	delay_ms(100);
	Arm0 = 760;
	//��
	delay_ms(200);

	Arm_back();


	
}



//�ұ�
void top_grasp3(void)
{
	//ץ
	Arm4 = top_grasp3_arm4;
	delay_ms(700);
	Arm1 = top_grasp3_arm1;
	delay_ms(50);
	Arm3 = 800;
	delay_ms(300);
	Arm2 = top_grasp3_arm2;
	delay_ms(300);
	Arm3_low_speed1(top_grasp3_arm3,710);
	delay_ms(100);
	Arm0 = 740;
	delay_ms(200);
	//��
		Arm_back();


	
	
}

//�ײ�ץȡ��
void under_grasp1()
{
	//ץ
	Arm4 = under_grasp1_arm4;
	delay_ms(300);
	Arm1 = under_grasp1_arm1;
	delay_ms(200);
	Arm3 = 800;
	delay_ms(200);
	Arm2 = under_grasp1_arm2;
	delay_ms(200);
	Arm3_low_speed1(under_grasp1_arm3,650);
	delay_ms(100);
	//��
//	Arm3_low_speed2(800,508);
//	delay_ms(100);
//	Arm2 = 1034;
//	delay_ms(800);
//  Arm3_low_speed3(1078,800);
//	delay_ms(800);
//	Arm1_low_speed(1250,716);
//	delay_ms(150);\
//	Arm4 = 430;
	
		
}
//��
void under_grasp2(void)
{
	Arm4 = under_grasp2_arm4;
	delay_ms(300);
	Arm1 = under_grasp2_arm1;
	delay_ms(200);
	Arm3 = 800;
	delay_ms(200);
	Arm2 = under_grasp2_arm2;
	delay_ms(200);
	Arm3_low_speed1(under_grasp2_arm3,650);
	delay_ms(100);
	//��
//	Arm3_low_speed2(800,538);
//	delay_ms(100);
//	Arm2 = 1034;
//	delay_ms(800);
// Arm3_low_speed3(1078,800);
//	delay_ms(800);
//	Arm1_low_speed(1250,628);
//	delay_ms(150);\
//	Arm4 = 430;
	
}
//��

void under_grasp3(void)
{
	Arm4 = under_grasp3_arm4;
	delay_ms(300);
	Arm1 = under_grasp3_arm1;
	delay_ms(300);
	Arm3 = 800;
	delay_ms(300);
	Arm2 = under_grasp3_arm2;
	delay_ms(200);
	Arm3_low_speed1(under_grasp3_arm3,650);
	delay_ms(100);
	//��
//	Arm3_low_speed2(800,508);
//	delay_ms(100);
//	Arm2 = 1034;
//	delay_ms(800);
// Arm3_low_speed3(1078,800);
//	delay_ms(800);
//	Arm1_low_speed(1250,916);
//	delay_ms(150);\
//	Arm4 = 430;

	
}




//�ּӹ�������
void First_place1(void)
{
	//��
	Arm4 = first_plcace1_arm4;
	delay_ms(500);
	Arm1= first_plcace1_arm1;
	delay_ms(50);
	Arm3 = 800;
	delay_ms(50);
	Arm2 = first_plcace1_arm2;
	delay_ms(50);
	Arm3_low_speed1(first_plcace1_arm3,800);
	delay_ms(50);
	Arm0 = 600;
	delay_ms(200);
	
	
	//��
	Arm_back1();
	
//  Arm3 = 800;
//	delay_ms(800);
//	Arm2 = 1034;
//	delay_ms(800);
//  Arm3_low_speed3(1078,800);
//	delay_ms(800);
//  Arm1_low_speed(1250,872);
//	delay_ms(1000);	
	
}



//��
void First_place2(void)
{
	//��
	Arm4 = first_plcace2_arm4;
	delay_ms(500);
	Arm1= first_plcace2_arm1;
	delay_ms(50);
	Arm3 = 800;
	delay_ms(50);
	Arm2 = first_plcace2_arm2;
	delay_ms(50);
	Arm3_low_speed1(first_plcace2_arm3,800);
	delay_ms(50);
	Arm0 = 600;
	delay_ms(200);
	//��
	Arm_back1();

//	Arm3_low_speed2(800,592);
//	delay_ms(400);
//	Arm2 = 1034;
//	delay_ms(800);
//  Arm3_low_speed3(1078,800);
//	delay_ms(800);
//  Arm1_low_speed(1250,872);
//	Arm4 = 430;
//	delay_ms(1000);
}

//��
void First_place3(void)
{
	//��
	Arm4 = first_plcace3_arm4;
	delay_ms(600);
	Arm1= first_plcace3_arm1;
	delay_ms(50);
	Arm3 = 800;
	delay_ms(50);
	Arm2 = first_plcace3_arm2;
	delay_ms(50);
	Arm3_low_speed1(first_plcace3_arm3,800);
	delay_ms(50);
	Arm0 = 600;
	delay_ms(200);
	//��
	Arm_back1();


//	Arm3_low_speed2(800,502);
//	delay_ms(400);
//	Arm2 = 1034;
//	delay_ms(800);
// Arm3_low_speed3(1078,800);
//	delay_ms(800);
//  Arm1_low_speed(1250,672);
//	Arm4 = 430;
//	delay_ms(1000);
}

//�ּӹ�����ȡ
void cujiagongclip1(void)
{
	Arm4 = first_plcace1_arm4;
	delay_ms(600);
	Arm1= first_plcace1_arm1;
	delay_ms(50);
	Arm3 = 800;
	delay_ms(20);
	
	Arm2 = first_plcace1_arm2;
	delay_ms(50);
	Arm3_low_speed1(first_plcace1_arm3,800);
	delay_ms(50);
	Arm0 = 740;
	delay_ms(200);
	
	//��
  Arm_back1();
	
}
void cujiagongclip2(void)
{
	Arm4 = first_plcace2_arm4;
	delay_ms(700);
	Arm1= first_plcace2_arm1;
	delay_ms(50);
	
	Arm3 = 800;
	delay_ms(50);
	Arm2 = first_plcace2_arm2;
	delay_ms(50);
	Arm3_low_speed1(first_plcace2_arm3,800);
	delay_ms(50);
	Arm0 = 740;
	delay_ms(200);
	
	//��
  Arm_back1();
	
}
void cujiagongclip3(void)
{
	Arm4 = first_plcace3_arm4;
	delay_ms(700);
	Arm1= first_plcace3_arm1;
	delay_ms(50);
	Arm3 = 800;
	delay_ms(50);
	
	Arm2 = first_plcace3_arm2;
	delay_ms(50);
	Arm3_low_speed1(first_plcace3_arm3,800);
	delay_ms(50);
	Arm0 = 740;
	delay_ms(200);
	
	//��
  Arm_back1();
	Arm4 = 430;
}

//�ӹ�����һ�η���
void Second_place1(void)
{
	//��
		Arm4 = second_place1_arm4;
		delay_ms(500);
	  Arm1 = second_place1_arm1;
    delay_ms(100);
	  
	  Arm3 = 800;
	  delay_ms(50);  
	  Arm2 = second_place1_arm2;
	 delay_ms(50);
	 Arm3_low_speed1(second_place1_arm3,800);
	 delay_ms(100);
   Arm0 = 600;
	 delay_ms(200);
	
	//��
	Arm_back1();
		
	
}


void Second_place2(void)
{
	//��
		Arm4 = second_place2_arm4;
		delay_ms(500);
	  Arm1 = second_place2_arm1;
	  delay_ms(50);
	  
	  Arm3 = 800;
		delay_ms(50);	
	 Arm2 = second_place2_arm2;
	 delay_ms(50);
	Arm3_low_speed1(second_place2_arm3,800);
	delay_ms(50);
	Arm0 = 600;
	delay_ms(200);
	
	//��
	Arm_back1();
}

void Second_place3(void)
{
	//��
		Arm4 = second_place3_arm4;
	 delay_ms(500);
	  Arm1 = second_place3_arm1;
	 delay_ms(100);
	
	Arm3 = 800;
	delay_ms(50);
	
	 Arm2 = second_place3_arm2;
	 delay_ms(50);
	Arm3_low_speed1(second_place3_arm3,800);
	delay_ms(100);
	Arm0 = 600;
	delay_ms(200);
	
	//��
	Arm_back1();
}


//�ӹ����ڶ��η���

void Third_place1(void)
{
	//��
	Arm4 = third_place1_arm4;
	 delay_ms(500);
	  Arm1 = third_place1_arm1;
	 delay_ms(50);
	
	 Arm3 = 800;
	 delay_ms(100);
	 
	 Arm2 = third_place1_arm2;
	 delay_ms(50);
	Arm3_low_speed1(third_place1_arm3,800);
	delay_ms(100);
	Arm0 = 600;
	delay_ms(200);
	
	//��
	Arm3 = 800;
	delay_ms(150);
	Arm2 = 1130;
	delay_ms(100);
	Arm3_low_speed3(958,850);
	delay_ms(150);
  Arm1_low_speed(929,900);	 
	delay_ms(200);
	
}

void Third_place2(void)
{
	//��
		Arm4 = third_place2_arm4;
		delay_ms(600);
	  Arm1 = third_place2_arm1;
	 delay_ms(50);
	  
	  Arm3 = 750;
		delay_ms(100);
	 Arm2 = third_place2_arm2;
	 delay_ms(100);
	Arm3_low_speed1(third_place2_arm3,750);
	delay_ms(50);
	Arm0 = 600;
	delay_ms(200);
	
	//��
	Arm_back();
}

void Third_place3(void)
{
	//��
	Arm4 = third_place3_arm4;
	delay_ms(500);
	  Arm1 = third_place3_arm1;
	 delay_ms(50);
		
	 Arm3 = 800;
		delay_ms(100);


	 delay_ms(50);
	 Arm2 = third_place3_arm2;
	 delay_ms(50);
	Arm3_low_speed1(third_place3_arm3,800);
	delay_ms(100);
	Arm0 = 600;
	delay_ms(200);
	
	//��
	Arm_back();
}

//�����ú���
//�����С����
void Place_Plus1()
{
	Arm4 = Place_Plus1_arm4;
	delay_ms(500);
	Arm1 = Place_Plus1_arm1;
	delay_ms(50);
	Arm3 = 800;
	delay_ms(100);
	Arm2 = Place_Plus1_arm2;
	delay_ms(100);
	place_plus_arm3_lowspeed(Place_Plus1_arm3,750);
	delay_ms(50);
	Arm0 = Place_Plus1_arm0;
	delay_ms(300);
	Arm3 = 518;
	delay_ms(300);
	delay_ms(200);
	Arm0 = 715;
	delay_ms(250);
	
	
	Plus_arm_back();
}

//�����С����
void Place_Plus2()
{
	Arm4 = Place_Plus2_arm4;
	delay_ms(500);
	Arm1 = Place_Plus2_arm1;
	delay_ms(50);
	Arm3 = 800;
	delay_ms(100);
	Arm2 = Place_Plus2_arm2;
	delay_ms(100);
	place_plus_arm3_lowspeed(Place_Plus2_arm3,750);
	delay_ms(50);
	Arm0 = Place_Plus2_arm0;
	delay_ms(300);
	Arm3 = 620;
	delay_ms(300);
	delay_ms(200);
	Arm0 = 715;
	delay_ms(250);
	
	Plus_arm_back();
}

//�����С����
void Place_Plus3()
{
	Arm4 = Place_Plus3_arm4;
	delay_ms(500);
	Arm1 = Place_Plus3_arm1;
	delay_ms(50);
	Arm3 = 800;
	delay_ms(100);
	Arm2 = Place_Plus3_arm2;
	delay_ms(100);
	place_plus_arm3_lowspeed(Place_Plus3_arm3,750);
	delay_ms(50);
	Arm0 = Place_Plus3_arm0;
	delay_ms(300);
	Arm3 = 585;
	delay_ms(200);
	Arm0 = 715;
	delay_ms(250);

	
	
	Plus_arm_back();
	
}



//��е����ɶ������׼����̬
//�ϲ�
void finish_top_grasp_status()
{
	  Arm0= Arm_open;
	 Arm4 = place1_arm4;
	 delay_ms(700);
	 Arm1 = place1_arm1;
	 delay_ms(50);
	 Arm3 = place1_arm3;
	 delay_ms(50);
	 Arm2_low_speed(place1_arm2,1060);
	 delay_ms(100);
	
}

//�²�
 void finish_under_grasp_status()
 {
	 //grasp1��д
	 Arm0= Arm_open;
	 Arm4 = place1_arm4;
	 delay_ms(700);
	 Arm1 = place1_arm1;
	 delay_ms(50);
	 Arm3 = place1_arm3;
	 delay_ms(50);
	 Arm2_low_speed(place1_arm2,1060);
	 delay_ms(100);
 }
 
 //�ּӹ���ɶ���
 void finish_rough_status()
 {
	 //grasp3��д
    Arm0 = Arm_open;
	 Arm4 = place3_arm4;
	 delay_ms(900);
	 Arm1 = place3_arm1;
	 delay_ms(50);
	 Arm3 = place3_arm3;
	 delay_ms(100);  
	 Arm2_low_speed(place3_arm2,1060);
	 delay_ms(50);
 }
 //���Ʒ�ϲ������̬
 void finish_top_product_status()
 {
	 scan_block_under();
 }
 





