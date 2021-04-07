#include "grasp.h"

/******************************************
*************************机械臂角度******
*******************************************/
//上层抓取
 u16 top_grasp1_arm1 = 803,top_grasp1_arm2 = 955,\
			top_grasp1_arm3 = 637,top_grasp1_arm4 = 469;
			
 u16 top_grasp2_arm1 = 802,top_grasp2_arm2 = 984,\
			top_grasp2_arm3 = 652,top_grasp2_arm4 = 400;
			
 u16 top_grasp3_arm1 = 904,top_grasp3_arm2 = 766,\
			top_grasp3_arm3 = 548,top_grasp3_arm4 = 346;

//下层抓取
 u16 under_grasp1_arm1 = 716, under_grasp1_arm2 =916, \
			under_grasp1_arm3 = 508, under_grasp1_arm4 = 476;
			
 u16 under_grasp2_arm1 = 628, under_grasp2_arm2 = 1043, \
				under_grasp2_arm3 = 538, under_grasp2_arm4 = 400;
 u16 under_grasp3_arm1 = 716, under_grasp3_arm2 =916 ,\
			under_grasp3_arm3 = 508, under_grasp3_arm4 = 349;

//粗加工区
 u16 first_plcace1_arm1 = 655,first_plcace1_arm2 = 945,\
			first_plcace1_arm3 = 475,first_plcace1_arm4 = 737;
 u16 first_plcace2_arm1 = 614,first_plcace2_arm2 = 1020,\
			first_plcace2_arm3 = 510,first_plcace2_arm4 = 671;
			
 u16 first_plcace3_arm1 = 654,first_plcace3_arm2 = 930,
			first_plcace3_arm3 = 466,first_plcace3_arm4 = 605;

//半成品区上层
 u16 second_place1_arm1 = 630,second_place1_arm2 = 1078,\
			second_place1_arm3 = 573,second_place1_arm4 = 1025;
			
 u16 second_place2_arm1 = 591,second_place2_arm2 = 1168,\
			second_place2_arm3 = 609,second_place2_arm4 = 944;
			
 u16 second_place3_arm1 = 636,second_place3_arm2 = 1117,\
			second_place3_arm3 = 602,second_place3_arm4 = 854;

//半成品区下层
 u16 third_place1_arm1 = 729,third_place1_arm2 = 877,\
			third_place1_arm3 = 458,third_place1_arm4 = 1015;
			
 u16 third_place2_arm1 = 616,third_place2_arm2 = 997,\
			third_place2_arm3 = 483,third_place2_arm4 = 936;	
			
 u16 third_place3_arm1 = 665,third_place3_arm2 = 937,\
		 third_place3_arm3 = 485,third_place3_arm4 = 867;

 //第一个载物台各个关节的值
 u16 place1_arm1 = 959;
 u16 place1_arm2 = 1204;
 u16 place1_arm3 = 1003;
 u16 place1_arm4 = 262;
 
 //第二个载物台各个关节的值
 u16 place2_arm1 = 959;
 u16 place2_arm2 = 1207;
 u16 place2_arm3 = 1021;
 u16 place2_arm4 = 1193;
 
 //第三个载物台各个关节的值
 u16 place3_arm1 = 948;
 u16 place3_arm2 = 1210;
 u16 place3_arm3 = 1006;
 u16 place3_arm4 = 1091;

//机械臂调速
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
 
 
 //载物台放置减速
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
 
 
 //机械臂收手动作
 void Arm_back(void)
 {
	 
	Arm3 = 800;
	delay_ms(500);
	Arm2 = 1060;
	delay_ms(800);
	Arm3_low_speed3(907,800);
	delay_ms(200);
  Arm1_low_speed(959,880);	 
	delay_ms(200);
 }
 
 //下层收手
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
 //中间动作
 void middle_state()
 {
	  Arm1 = 959;
	 delay_ms(800);
	  Arm2 = 1060;
	 delay_ms(800);
	 Arm3 = 907;
	 delay_ms(500);
	
	 
 }
 //云台800
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

 //放置第一个物块到
 void place_playload1()
 {
	 //放
	 	Arm4 = place1_arm4;
	 delay_ms(800);
	 Arm3 = place1_arm3;
	 delay_ms(900);
	 Arm2_low_speed(place1_arm2,1060);
	 delay_ms(800);
	 Arm1 = place1_arm1;
	 delay_ms(800);
	 Arm0 = 654;//爪子微微开
	 delay_ms(800);
	 //收
	
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
	 //放
	 Arm4 = place2_arm4;
	 delay_ms(800);
	 Arm3 = place2_arm3;
	 delay_ms(800);
	 Arm2_low_speed(place2_arm2,1060);
	 delay_ms(800);
	 Arm1 = place2_arm1;
	 delay_ms(800);
	 Arm0 = 654;//爪子微微开
	 delay_ms(800);
	 
	 place_back();
	 Arm0 = 600;

	 
	 
 }
  void place_playload3()
 {
	 //放
	  Arm4 = place3_arm4;
	 delay_ms(900);
	 Arm3 = place3_arm3;
	 delay_ms(800);
	 Arm2_low_speed(place3_arm2,1060);
	 delay_ms(800);
	 Arm1 = place3_arm1;
	 delay_ms(800);
	 Arm0 = 654;//爪子微微开
	 delay_ms(800);
	 
	 place_back();
	 Arm0 = 600;


	 
 }
 //载物台第一个物块夹取
 
 void grasp_playload1()
 {
	  //抓
   Arm0= 654;
	 Arm4 = place1_arm4;
	 delay_ms(800);
	 Arm3_low_speed3(place1_arm3,907);
	 delay_ms(200);    
	 Arm1 = place1_arm1;
	 delay_ms(800);
	 Arm2_low_speed(place1_arm2,1060);
	 delay_ms(800);
	 Arm0 = 740;
	 delay_ms(800);
	 //收
	
	
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
	 	  //抓
	 Arm0 = 654;
	 Arm4 = place2_arm4;
	 delay_ms(800);
	 Arm3_low_speed3(place2_arm3,907);
	 delay_ms(200);  
	 Arm1 = place2_arm1;
	 delay_ms(800);
	 Arm2_low_speed(place2_arm2,1060);
	 delay_ms(800);
	 
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
	 delay_ms(800);
	 Arm2_low_speed(place3_arm2,1060);
	 delay_ms(800);
	 Arm0 = 740;
	 delay_ms(800);
	 
	 place_back();
	 
 }

//复位机械臂状态
void reset_state()
{
	
	Arm0 = 600;//角度1
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

//二维码识别姿势
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
	//二维码扫描完成后恢复成扫描上层颜色姿势
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



//物块识别姿势上层
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


//物块识别姿势下层
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

  
//顶层抓取左边
void top_grasp1()
{
	//抓
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
	
	
	//收
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




//中间
void top_grasp2(void)
{
	//抓
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
	//收
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



//右边
void top_grasp3(void)
{
	//抓
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
	//收
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

//底层抓取左
void under_grasp1()
{
	//抓
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
	//收
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
//中
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
	//收
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
//右

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
	//收
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




//粗加工区放置
void First_place1(void)
{
	//放
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
	
	
	//收
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



//中
void First_place2(void)
{
	//放
	
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
	//收
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

//右
void First_place3(void)
{
	//放
	
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
	//收
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

//粗加工区夹取
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
	
	//收
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
	
	//收
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
	
	//收
  Arm_back1();
	Arm4 = 430;
}

//加工区第一次放置
void Second_place1(void)
{
	//放
		
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
	
	//收
	Arm_back1();
		
	
}


void Second_place2(void)
{
	//放
		
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
	
	//收
	Arm_back1();
}

void Second_place3(void)
{
	//放
		
	  Arm1 = second_place3_arm1;
	 delay_ms(600);
	 Arm3 = 602;
	delay_ms(800);
	Arm4 = second_place3_arm4;
	 delay_ms(800);
	 Arm2 = second_place3_arm2;
	 delay_ms(800);
	Arm3_low_speed1(second_place3_arm3,800);
	delay_ms(200);
	Arm0 = 600;
	delay_ms(800);
	
	//收
	Arm_back1();
}


//加工区第二次放置

void Third_place1(void)
{
	//放
	
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
	
	//收
	Arm_back();
	
}

void Third_place2(void)
{
	//放
		
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
	
	//收
	Arm_back();
}

void Third_place3(void)
{
	//放
	
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
	
	//收
	Arm_back();
}







