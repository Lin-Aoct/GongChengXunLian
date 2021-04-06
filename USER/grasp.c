#include "grasp.h"

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
	for(tem=curt;tem<=target;tem+=1)		
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
	 Arm3 = 700;
	 delay_ms(200);
	 Arm2 = 1060;
	 delay_ms(300);
	 Arm3 = 907;
	 delay_ms(300);
	 Arm1 = 959;
	 delay_ms(200);
	 
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
 //第一个载物台各个关节的值
 u16 place1_arm1 = 942;
 u16 place1_arm2 = 1193;
 u16 place1_arm3 = 981;
 u16 place1_arm4 = 261;
 
 //第一个载物台各个关节的值
 u16 place2_arm1 = 956;
 u16 place2_arm2 = 1193;
 u16 place2_arm3 = 1015;
 u16 place2_arm4 = 1188;
 
 //第一个载物台各个关节的值
 u16 place3_arm1 = 930;
 u16 place3_arm2 = 1211;
 u16 place3_arm3 = 1006;
 u16 place3_arm4 = 1097;
 
 //放置第一个物块到
 void place_playload1()
 {
	 //放
	 	Arm4 = place1_arm4;
	 delay_ms(500);
	 Arm3 = place1_arm3;
	 delay_ms(800);
	 Arm2 = place1_arm2;
	 delay_ms(800);
	 Arm1 = place1_arm1;
	 delay_ms(800);
	 Arm0 = 654;//爪子微微开
	 delay_ms(800);
	 //收
	 Arm1 = 959;
	 delay_ms(800);
	 Arm2 = 1060;
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
	 Arm2 = place2_arm2;
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
	 Arm2 = place3_arm2;
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
	 Arm2 = place1_arm2;
	 delay_ms(800); 
	 Arm1 = place1_arm1;
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
	 Arm2 = place2_arm2;
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
	 Arm2 = place3_arm2;
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
	Arm0 = 600;
	delay_ms(100);
	Arm1 = 1217;
	delay_ms(500);
  Arm3 = 1042;
	delay_ms(500);
	Arm2 = 1076;
	delay_ms(500);
	Arm4 = 448;
 
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
	Arm4 = 475;
	delay_ms(500);
	Arm1 = 872;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm2 = 850;
	delay_ms(800);
	Arm3_low_speed1(592,800);//
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
	Arm4 = 400;
	delay_ms(100);
	Arm1 = 802;
	delay_ms(600);
	Arm3 = 800;
	delay_ms(700);
	Arm2 = 984;
	delay_ms(800);
	Arm3_low_speed1(652,800);
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
	Arm4 = 349;
	delay_ms(200);
	Arm1 = 844;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm2 = 844;
	delay_ms(800);
	Arm3_low_speed1(578,800);
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
	Arm4 = 476;
	Arm1 = 716;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm2 = 916;
	delay_ms(800);
	Arm3_low_speed1(508,800);
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
	Arm4 = 400;
	Arm1 = 628;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm2 = 1043;
	delay_ms(800);
	Arm3_low_speed1(538,800);
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
	Arm4 = 349;
	Arm1 = 716;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm2 = 916;
	delay_ms(800);
	Arm3_low_speed1(508,800);
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
	Arm1= 658;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm4 = 740;
	delay_ms(800);
	Arm2 = 972;
	delay_ms(800);
	Arm3_low_speed1(502,800);
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
	
	Arm1= 620;
	delay_ms(500);
	Arm3 = 800;
	delay_ms(800);
	Arm4 = 680;
	delay_ms(800);
	Arm2 = 1038;
	delay_ms(800);
	Arm3_low_speed1(522,800);
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
	
	Arm1= 672;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm4 = 605;
	delay_ms(800);
	Arm2 = 954;
	delay_ms(800);
	Arm3_low_speed1(502,800);
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
	
	Arm1= 658;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm4 = 740;
	delay_ms(200);
	Arm2 = 972;
	delay_ms(800);
	Arm3_low_speed1(502,800);
	delay_ms(200);
	Arm0 = 740;
	delay_ms(800);
	
	//收
  Arm_back1();
	
}
void cujiagongclip2(void)
{
	Arm1= 620;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm4 = 740;
	delay_ms(800);
	Arm2 = 1038;
	delay_ms(500);
	Arm3_low_speed1(522,800);
	delay_ms(200);
	Arm0 = 740;
	delay_ms(800);
	
	//收
  Arm_back1();
	
}
void cujiagongclip3(void)
{
	Arm1= 672;
	delay_ms(800);
	Arm3 = 800;
	delay_ms(800);
	Arm4 = 605;
	delay_ms(800);
	Arm2 = 954;
	delay_ms(500);
	Arm3_low_speed1(502,800);
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
		
	  Arm1 = 690;
    delay_ms(600);
	  Arm3 = 800;
	  delay_ms(800);
	  Arm4 = 1025;
		delay_ms(800);
	  Arm2 = 1054;
	 delay_ms(800);
	 Arm3_low_speed1(605,800);
	 delay_ms(200);
   Arm0 = 600;
	 delay_ms(200);
	
	//收
	Arm_back1();
		
	
}


void Second_place2(void)
{
	//放
		
	  Arm1 = 627;
	  delay_ms(600);
	  Arm3 = 800;
		delay_ms(800);

	  Arm4 = 944;
		delay_ms(800);
	 Arm2 = 1165;
	 delay_ms(800);
	Arm3_low_speed1(653,800);
	delay_ms(200);
	Arm0 = 600;
	delay_ms(800);
	
	//收
	Arm_back1();
}

void Second_place3(void)
{
	//放
		
	  Arm1 = 603;
	 delay_ms(600);
	 Arm3 = 800;
	delay_ms(800);
	Arm4 = 866;
	 delay_ms(800);
	 Arm2 = 1132;
	 delay_ms(800);
	Arm3_low_speed1(614,800);
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
	
	  Arm1 = 765;
	 delay_ms(600);
	 Arm3 = 800;
	delay_ms(800);
		Arm4 = 997;
	 delay_ms(800);
	 Arm2 = 808;
	 delay_ms(500);
	Arm3_low_speed1(446,800);
	delay_ms(50);
	Arm0 = 600;
	delay_ms(200);
	
	//收
	Arm_back();
	
}

void Third_place2(void)
{
	//放
		
	  Arm1 = 664;
	 delay_ms(600);
	 Arm3 = 750;
		delay_ms(800);

	Arm4 = 927;
		delay_ms(50);
	 delay_ms(50);
	 Arm2 = 1054;
	 delay_ms(500);
	Arm3_low_speed1(497,750);
	delay_ms(50);
	Arm0 = 600;
	delay_ms(200);
	
	//收
	Arm_back();
}

void Third_place3(void)
{
	//放
	
	  Arm1 = 743;
	 delay_ms(600);
	 Arm3 = 800;
		delay_ms(800);

	Arm4 = 867;
	delay_ms(50);
	 delay_ms(50);
	 Arm2 = 883;
	 delay_ms(500);
	Arm3_low_speed1(488,800);
	delay_ms(50);
	Arm0 = 600;
	delay_ms(200);
	
	//收
	Arm_back();
}







