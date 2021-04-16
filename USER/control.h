#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"

#define PI 3.14159265

void Mode_Start(void);
void Mode_Init(void);
void Mode_Go_Area1(void);
void Mode_Area1_To_Area2(u8 mode);
void Mode_Area2_To_Area3_Top(void);
void Mode_Area3_To_Area1(void);
void Mode_Go_One_Step(void);
void Mode_Back_One_Step(void);
void Mode_Go_One_Aera1(u8 current_step);
void Mode_Back_One_Area1(u8 current_step);
void Mode_Area2_To_Area3_Bottom(void);
void Mode_Area3_Back(void);

void Set_PID_PWM(void);
void Cross_Road_Fix(u8 mode);
void Mode_PID_Test(u8 mode);

//出现的mode参数都是数字1代表上层，当在搬运下层过程中使用数字2

//这里的第一次抓取都是相对于小车位置左边到右
//CONTROL 和grasp区别就是control是选择放置而grasp是记录动作供control调用

extern void  top_grasp_choose1(u8*ptr);//第一次抓取
extern void  top_grasp_choose2(u8*ptr);//第二次
extern void  top_grasp_choose3(u8*ptr);//第三次

extern void  under_grasp_choose1(u8 *ptr);//下层抓取
extern void  under_grasp_choose2(u8 *ptr);
extern void  under_grasp_choose3(u8 *ptr);

extern void  cujiagong_choose_grasp1(u8 *ptr,u8 mode);//粗加工区抓取抓起来放在在载物台上
extern void  cujiagong_choose_grasp2(u8 *ptr,u8 mode);//
extern void  cujiagong_choose_grasp3(u8 *ptr,u8 mode);



extern void  First_choose_place1(u8* ptr,u8 mode);//mode数字1是放置上层，数字2是放置下层
extern void  First_choose_place2(u8* ptr,u8 mode);//第一次放置到粗加工区，上下层公用同一个函数
extern void  First_choose_place3(u8* ptr,u8 mode);


//半成品区放置上层物块下层物块公用一个函数用参数mode区分1上层2下层
//让函数少一点以为同理
extern void  place_top_product1(u8* ptr);//半成品区顶层放置
extern void  place_top_product2(u8* ptr);
extern void  place_top_product3(u8* ptr);
 
extern void  place_under_product1(u8* ptr);//半成品区底层放置
extern void  place_under_product2(u8* ptr);
extern void  place_under_product3(u8* ptr);



//码垛放置顺序选择
extern void Place_Plus1_choose(u8* ptr);
extern void Place_Plus2_choose(u8* ptr);
extern void Place_Plus3_choose(u8* ptr);






//简洁版后期稳定后可以使用前期一个个函数调用
extern void  top_grasp_choose(u8* ptr);//一次抓三个
extern void  under_grasp_all(u8 *ptr);
extern void  place_top_product_all(u8* ptr);//一次放三个
extern void  place_under_product_all(u8* ptr);
extern void  First_place_all(u8* ptr,u8 mode);//粗加工区一次放三个




#endif
