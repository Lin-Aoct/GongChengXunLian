#include "grasp.h"

/******************************************
*************************��е�۽Ƕ�******
*******************************************/
//�ϲ�ץȡ
 u16 top_grasp1_arm1 = 803,top_grasp1_arm2 = 955,\
			top_grasp1_arm3 = 637,top_grasp1_arm4 = 469;
			
 u16 top_grasp2_arm1 = 802,top_grasp2_arm2 = 984,\
			top_grasp2_arm3 = 652,top_grasp2_arm4 = 400;
			
 u16 top_grasp3_arm1 = 904,top_grasp3_arm2 = 766,\
			top_grasp3_arm3 = 548,top_grasp3_arm4 = 346;

//�²�ץȡ
 u16 under_grasp1_arm1 = 716, under_grasp1_arm2 =916, \
			under_grasp1_arm3 = 508, under_grasp1_arm4 = 476;
			
 u16 under_grasp2_arm1 = 628, under_grasp2_arm2 = 1043, \
				under_grasp2_arm3 = 538, under_grasp2_arm4 = 400;
 u16 under_grasp3_arm1 = 716, under_grasp3_arm2 =916 ,\
			under_grasp3_arm3 = 508, under_grasp3_arm4 = 349;

//�ּӹ���
 u16 first_plcace1_arm1 = 655,first_plcace1_arm2 = 945,\
			first_plcace1_arm3 = 475,first_plcace1_arm4 = 737;
 u16 first_plcace2_arm1 = 614,first_plcace2_arm2 = 1020,\
			first_plcace2_arm3 = 510,first_plcace2_arm4 = 671;
			
 u16 first_plcace3_arm1 = 654,first_plcace3_arm2 = 930,
			first_plcace3_arm3 = 466,first_plcace3_arm4 = 605;

//���Ʒ���ϲ�
 u16 second_place1_arm1 = 762,second_place1_arm2 = 846,\
			second_place1_arm3 = 490,second_place1_arm4 = 1009;
			
 u16 second_place2_arm1 = 689,second_place2_arm2 = 990,\
			second_place2_arm3 = 568,second_place2_arm4 = 952;
			
 u16 second_place3_arm1 = 680,second_place3_arm2 = 970,\
			second_place3_arm3 = 538,second_place3_arm4 = 875;

//���Ʒ���²�
 u16 third_place1_arm1 = 729,third_place1_arm2 = 877,\
			third_place1_arm3 = 458,third_place1_arm4 = 1003;
			
 u16 third_place2_arm1 = 639,third_place2_arm2 = 999,\
			third_place2_arm3 = 503,third_place2_arm4 = 928;	
			
 u16 third_place3_arm1 = 684,third_place3_arm2 = 917,\
		 third_place3_arm3 = 466,third_place3_arm4 = 856;

 //��һ������̨�����ؽڵ�ֵ
 u16 place1_arm1 = 959;
 u16 place1_arm2 = 1182;
 u16 place1_arm3 = 1003;
 u16 place1_arm4 = 262;
 
 //�ڶ�������̨�����ؽڵ�ֵ
 u16 place2_arm1 = 959;
 u16 place2_arm2 = 1207;
 u16 place2_arm3 = 1021;
 u16 place2_arm4 = 1193;
 
 //����������̨�����ؽڵ�ֵ
 u16 place3_arm1 = 948;
 u16 place3_arm2 = 1210;
 u16 place3_arm3 = 1006;
 u16 place3_arm4 = 1091;

//��е�۵���
static void Arm3_low_speed1(unsigned int target, unsigned int curt)
{
	int tem;
	for(tem=curt;tem>=target;tem-=2)		
	{
		Arm3 = tem;
		delay_ms(15);
	}
	
}


static void Arm3_low_speed2(unsigned int target, unsigned int curt)
{
	int tem;
	for(tem=curt;tem<=target;tem+=2)		
	{
		Arm3 = tem;
		delay_ms(13);
	}
	
}

static void Arm3_low_speed3(unsigned int target, unsigned int curt)
{
	int tem;
	for(tem=curt;tem<=target;tem+=2)		
	{
		Arm3 = tem;
		delay_ms(15);
	}
	
}


 void Arm1_low_speed(unsigned int target,unsigned int curt)
 {
	 int tem;
	for(tem=curt;tem<=target;tem+=2)		
	{
		Arm1  = tem;
		delay_ms(15);
	}
 }
 
 
 //����̨���ü���
 void Arm2_low_speed(unsigned int target,unsigned int curt)
 {
	 int tem;
	for(tem=curt;tem<=target;tem+=1)		
	{
		Arm2  = tem;
		delay_ms(15);
	}
 }

 //endif
 
 
 //��е�����ֶ���
 void Arm_back(void)
 {
	 
	Arm3 = 800;
	delay_ms(500);
	Arm2 = 1060;
	delay_ms(800);
	Arm3_low_speed3(907,800);
	delay_ms(200);
  Arm1_low_speed(959,880);	 
//	delay_ms(200);
 }
 
 //�²�����
 void Arm_back1(void)
 {
	 Arm3 = 800;
	delay_ms(800);
	Arm2 = 1060;
	delay_ms(800);
	Arm3_low_speed3(907,800);
	delay_ms(200);
  Arm1_low_speed(959,716);
 }
 //�м䶯��
 void middle_state()
 {
	  Arm1 = 959;
	 delay_ms(800);
	  Arm2 = 1060;
	 delay_ms(800);
	 Arm3 = 907;
	 delay_ms(500);
	
	 
 }
 //��̨800
 static void place_back()
 {
	 Arm2 = 1060;
	 delay_ms(500);
	 Arm1 = 959;
	 delay_ms(300);
	 Arm3 = 907;
	 delay_ms(500);
	 Arm4 = 800;
	 delay_ms(500);
 }

 //���õ�һ����鵽
 void place_playload1()
 {
	 //��
	 	Arm4 = place1_arm4;
	 delay_ms(800);
	 Arm3 = place1_arm3;
	 delay_ms(750);
	 Arm2_low_speed(place1_arm2,1060);
	 delay_ms(500);
	 Arm1 = place1_arm1;
	 delay_ms(800);
	 Arm0 = 654;//צ��΢΢��
	 delay_ms(800);
	 //��
	
	 Arm2 = 1060;
	 delay_ms(800);
	 Arm1 = 959;
	 delay_ms(800);
	 Arm3 = 907;
	 delay_ms(800);
	 Arm4 = 430;
	 delay_ms(600);
	 Arm0 = 600;
	 delay_ms(200);
	 
	 
 }
  void place_playload2()
 {
	 //��
	 Arm4 = place2_arm4;
	 delay_ms(800);
	 Arm3 = place2_arm3;
	 delay_ms(750);
	 Arm2_low_speed(place2_arm2,1060);
	 delay_ms(500);
	 Arm1 = place2_arm1;
	 delay_ms(800);
	 Arm0 = 654;//צ��΢΢��
	 delay_ms(800);
	 
	 place_back();
	 Arm0 = 600;

	 
	 
 }
  void place_playload3()
 {
	 //��
	  Arm4 = place3_arm4;
	 delay_ms(900);
	 Arm3 = place3_arm3;
	 delay_ms(750);
	 Arm2_low_speed(place3_arm2,1060);
	 delay_ms(500);
	 Arm1 = place3_arm1;
	 delay_ms(800);
	 Arm0 = 654;//צ��΢΢��
	 delay_ms(800);
	 
	 place_back();
	 Arm0 = 600;


	 
 }
 //����̨��һ������ȡ
 
 void grasp_playload1()
 {
	  //ץ
   Arm0= 654;
	 Arm4 = place1_arm4;
	 delay_ms(800);
	 Arm3_low_speed3(place1_arm3,907);
	 delay_ms(200);    
	 Arm1 = place1_arm1;
	 delay_ms(800);
	 Arm2_low_speed(place1_arm2,1060);
	 delay_ms(500);
	 Arm0 = 740;
	 delay_ms(800);
	 //��
	
	
	 Arm1 = 959;
	 delay_ms(800);
	 Arm2 = 1060;
	 delay_ms(800);
	 Arm3 = 907;
	 delay_ms(800);
	 Arm4 = 430;
	 delay_ms(800);
	
	 
	 
 }
 
 void grasp_playload2()
 {
	 	  //ץ
	 Arm0 = 654;
	 Arm4 = place2_arm4;
	 delay_ms(800);
	 Arm3_low_speed3(place2_arm3,907);
	 delay_ms(200);  
	 Arm1 = place2_arm1;
	 delay_ms(800);
	 Arm2_low_speed(place2_arm2,1060);
	 delay_ms(200);
	 
	 Arm0 = 740;
	 delay_ms(800);
	 place_back();
	 
 }
 
 void grasp_playload3()
 {
	 Arm0 = 654;
	 Arm4 = place3_arm4;
	 delay_ms(800);
	 Arm3_low_speed3(place3_arm3,907);
	 delay_ms(200);  
	 Arm1 = place3_arm1;
	 delay_ms(750);
	 Arm2_low_speed(place3_arm2,1060);
	 delay_ms(200);
	 Arm0 = 740;
	 delay_ms(800);
	 
	 place_back();
	 
 }

//��λ��е��״̬
void reset_state()
{
	
	Arm0 = 600;//�Ƕ�1
	delay_ms(300);
	Arm2 = 1034;//5
	delay_ms(300);
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
	Arm1 = 1220;
	delay_ms(500);
	Arm2 = 1076;
	
 
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
	delay_ms(400);
	Arm1 = 1250;
	delay_ms(300);
	Arm3 = 1042;
	delay_ms(500);
	Arm2 = 1034;
	delay_ms(300);
}


//���ʶ�������²�
void scan_block_under(void)
{
	Arm0 = 600;
	Arm4 =  457;
	delay_ms(400);
	Arm1 = 1172;
	delay_ms(300);
	Arm3 = 949;
	delay_ms(500);
	Arm2 = 1034;
	delay_ms(300);
}

  
//����ץȡ���
void top_grasp1()
{
	//ץ
	Arm4 = top_grasp1_arm4;
	delay_ms(500);
	Arm1 = top_grasp1_arm1;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm2 = top_grasp1_arm2;
	delay_ms(800);
	Arm3_low_speed1(top_grasp1_arm3,800);//
	delay_ms(300);
	Arm0 = 740;
	delay_ms(800);
	
	
	//��
//	delay_ms(1000);
	Arm_back();
//	
//	Arm3 = 800;
//	delay_ms(200);
//	Arm2 = 1034;
//	delay_ms(800);
//	Arm3_low_speed3(1078,800);
//	delay_ms(200);
//  Arm1_low_speed(1250,872);
//	Arm4 = 430;
//	delay_ms(500);
	
}




//�м�
void top_grasp2(void)
{
	//ץ
	Arm4 = top_grasp2_arm4;
	delay_ms(100);
	Arm1 = top_grasp2_arm1;
	delay_ms(600);
	Arm3 = 800;
	delay_ms(700);
	Arm2 = top_grasp2_arm2;
	delay_ms(800);
	Arm3_low_speed1(top_grasp2_arm3,800);
	delay_ms(200);
	Arm0 = 760;
	//��
	delay_ms(800);

	Arm_back();

//	delay_ms(1000);
//Arm3 = 800;
//	delay_ms(200);
//	Arm2 = 1034;
//	delay_ms(800);
// Arm3_low_speed3(1078,800);
//	delay_ms(800);
//	Arm1_low_speed(1250,802);
//	delay_ms(150);\
//	Arm4 = 430;
	
}



//�ұ�
void top_grasp3(void)
{
	//ץ
	Arm4 = top_grasp3_arm4;
	delay_ms(200);
	Arm1 = top_grasp3_arm1;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm2 = top_grasp3_arm2;
	delay_ms(800);
	Arm3_low_speed1(top_grasp3_arm3,800);
	delay_ms(200);
	Arm0 = 740;
	delay_ms(1000);
	//��
		Arm_back();

//	Arm3 = 800;
//	delay_ms(200);
//	Arm2 = 1034;
//	delay_ms(800);
//	
// Arm3_low_speed3(1078,800);
//	delay_ms(800);
//	Arm1_low_speed(1250,844);
//	delay_ms(100);
//	Arm4 = 430;
	
	
}

//�ײ�ץȡ��
void under_grasp1()
{
	//ץ
	Arm4 = under_grasp1_arm4;
	delay_ms(300);
	Arm1 = under_grasp1_arm1;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm2 = under_grasp1_arm2;
	delay_ms(800);
	Arm3_low_speed1(under_grasp1_arm3,800);
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
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm2 = under_grasp2_arm2;
	delay_ms(800);
	Arm3_low_speed1(under_grasp2_arm3,800);
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
	Arm1 = under_grasp3_arm1;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm2 = under_grasp3_arm2;
	delay_ms(800);
	Arm3_low_speed1(under_grasp3_arm3,800);
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
	Arm1= first_plcace1_arm1;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm4 = first_plcace1_arm4;
	delay_ms(800);
	Arm2 = first_plcace1_arm2;
	delay_ms(800);
	Arm3_low_speed1(first_plcace1_arm3,800);
	delay_ms(100);
	Arm0 = 600;
	delay_ms(800);
	
	
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
	
	Arm1= first_plcace2_arm1;
	delay_ms(500);
	Arm3 = 800;
	delay_ms(800);
	Arm4 = first_plcace2_arm4;
	delay_ms(800);
	Arm2 = first_plcace2_arm2;
	delay_ms(800);
	Arm3_low_speed1(first_plcace2_arm3,800);
	delay_ms(200);
	Arm0 = 600;
	delay_ms(1000);
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
	
	Arm1= first_plcace3_arm1;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm4 = first_plcace3_arm4;
	delay_ms(800);
	Arm2 = first_plcace3_arm2;
	delay_ms(800);
	Arm3_low_speed1(first_plcace3_arm3,800);
	delay_ms(200);
	Arm0 = 600;
	delay_ms(1000);
	//��
	Arm_back1();
  delay_ms(200);


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
	
	Arm1= first_plcace1_arm1;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm4 = first_plcace1_arm4;
	delay_ms(200);
	Arm2 = first_plcace1_arm2;
	delay_ms(800);
	Arm3_low_speed1(first_plcace1_arm3,800);
	delay_ms(200);
	Arm0 = 740;
	delay_ms(800);
	
	//��
  Arm_back1();
	
}
void cujiagongclip2(void)
{
	Arm1= first_plcace2_arm1;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm4 = first_plcace2_arm4;
	delay_ms(800);
	Arm2 = first_plcace2_arm2;
	delay_ms(500);
	Arm3_low_speed1(first_plcace2_arm3,800);
	delay_ms(200);
	Arm0 = 740;
	delay_ms(800);
	
	//��
  Arm_back1();
	
}
void cujiagongclip3(void)
{
	Arm1= first_plcace3_arm1;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm4 = first_plcace3_arm4;
	delay_ms(800);
	Arm2 = first_plcace3_arm2;
	delay_ms(500);
	Arm3_low_speed1(first_plcace3_arm3,800);
	delay_ms(200);
	Arm0 = 740;
	delay_ms(800);
	
	//��
  Arm_back1();
	Arm4 = 430;
}

//�ӹ�����һ�η���
void Second_place1(void)
{
	//��
		
	  Arm1 = second_place1_arm1;
    delay_ms(600);
	  Arm3 = 800;
	  delay_ms(800);
	  Arm4 = second_place1_arm4;
		delay_ms(800);
	  Arm2 = second_place1_arm2;
	 delay_ms(800);
	 Arm3_low_speed1(second_place1_arm3,800);
	 delay_ms(200);
   Arm0 = 600;
	 delay_ms(200);
	
	//��
	Arm_back1();
		
	
}


void Second_place2(void)
{
	//��
		
	  Arm1 = second_place2_arm1;
	  delay_ms(600);
	  Arm3 = 800;
		delay_ms(800);

	  Arm4 = second_place2_arm4;
		delay_ms(800);
	 Arm2 = second_place2_arm2;
	 delay_ms(800);
	Arm3_low_speed1(second_place2_arm3,800);
	delay_ms(200);
	Arm0 = 600;
	delay_ms(800);
	
	//��
	Arm_back1();
}

void Second_place3(void)
{
	//��
		
	  Arm1 = second_place3_arm1;
	 delay_ms(600);
	 Arm3 = 800;
	delay_ms(800);
	Arm4 = second_place3_arm4;
	 delay_ms(800);
	 Arm2 = second_place3_arm2;
	 delay_ms(800);
	Arm3_low_speed1(second_place3_arm3,800);
	delay_ms(200);
	Arm0 = 600;
	delay_ms(800);
	
	//��
	Arm_back1();
}


//�ӹ����ڶ��η���

void Third_place1(void)
{
	//��
	
	  Arm1 = third_place1_arm1;
	 delay_ms(600);
	 Arm3 = 800;
	 delay_ms(800);
	 Arm4 = third_place1_arm4;
	 delay_ms(800);
	 Arm2 = third_place1_arm2;
	 delay_ms(500);
	Arm3_low_speed1(third_place1_arm3,800);
	delay_ms(50);
	Arm0 = 600;
	delay_ms(200);
	
	//��
	Arm_back();
	
}

void Third_place2(void)
{
	//��
		
	  Arm1 = third_place2_arm1;
	 delay_ms(600);
	 Arm3 = 750;
		delay_ms(800);

	  Arm4 = third_place2_arm4;
		delay_ms(50);
	 delay_ms(50);
	 Arm2 = third_place2_arm2;
	 delay_ms(500);
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
	
	  Arm1 = third_place3_arm1;
	 delay_ms(600);
	 Arm3 = 800;
		delay_ms(800);

	Arm4 = third_place3_arm4;
	delay_ms(50);
	 delay_ms(50);
	 Arm2 = third_place3_arm2;
	 delay_ms(500);
	Arm3_low_speed1(third_place3_arm3,800);
	delay_ms(50);
	Arm0 = 600;
	delay_ms(200);
	
	//��
	Arm_back();
}







