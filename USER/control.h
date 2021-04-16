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

//���ֵ�mode������������1�����ϲ㣬���ڰ����²������ʹ������2

//����ĵ�һ��ץȡ���������С��λ����ߵ���
//CONTROL ��grasp�������control��ѡ����ö�grasp�Ǽ�¼������control����

extern void  top_grasp_choose1(u8*ptr);//��һ��ץȡ
extern void  top_grasp_choose2(u8*ptr);//�ڶ���
extern void  top_grasp_choose3(u8*ptr);//������

extern void  under_grasp_choose1(u8 *ptr);//�²�ץȡ
extern void  under_grasp_choose2(u8 *ptr);
extern void  under_grasp_choose3(u8 *ptr);

extern void  cujiagong_choose_grasp1(u8 *ptr,u8 mode);//�ּӹ���ץȡץ��������������̨��
extern void  cujiagong_choose_grasp2(u8 *ptr,u8 mode);//
extern void  cujiagong_choose_grasp3(u8 *ptr,u8 mode);



extern void  First_choose_place1(u8* ptr,u8 mode);//mode����1�Ƿ����ϲ㣬����2�Ƿ����²�
extern void  First_choose_place2(u8* ptr,u8 mode);//��һ�η��õ��ּӹ��������²㹫��ͬһ������
extern void  First_choose_place3(u8* ptr,u8 mode);


//���Ʒ�������ϲ�����²���鹫��һ�������ò���mode����1�ϲ�2�²�
//�ú�����һ����Ϊͬ��
extern void  place_top_product1(u8* ptr);//���Ʒ���������
extern void  place_top_product2(u8* ptr);
extern void  place_top_product3(u8* ptr);
 
extern void  place_under_product1(u8* ptr);//���Ʒ���ײ����
extern void  place_under_product2(u8* ptr);
extern void  place_under_product3(u8* ptr);



//������˳��ѡ��
extern void Place_Plus1_choose(u8* ptr);
extern void Place_Plus2_choose(u8* ptr);
extern void Place_Plus3_choose(u8* ptr);






//��������ȶ������ʹ��ǰ��һ������������
extern void  top_grasp_choose(u8* ptr);//һ��ץ����
extern void  under_grasp_all(u8 *ptr);
extern void  place_top_product_all(u8* ptr);//һ�η�����
extern void  place_under_product_all(u8* ptr);
extern void  First_place_all(u8* ptr,u8 mode);//�ּӹ���һ�η�����




#endif
