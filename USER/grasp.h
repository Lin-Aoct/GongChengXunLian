#ifndef _GRASP_H
#define _GRASP_H
#include "headfiles.h"

extern u16 top_grasp1_arm1,top_grasp1_arm2,top_grasp1_arm3,top_grasp1_arm4;
extern u16 top_grasp2_arm1,top_grasp2_arm2,top_grasp2_arm3,top_grasp2_arm4;
extern u16 top_grasp3_arm1,top_grasp3_arm2,top_grasp3_arm3,top_grasp3_arm4;

extern u16 under_grasp1_arm1, under_grasp1_arm2, under_grasp1_arm3, under_grasp1_arm4;
extern u16 under_grasp2_arm1, under_grasp2_arm2, under_grasp2_arm3, under_grasp2_arm4;
extern u16 under_grasp3_arm1, under_grasp3_arm2, under_grasp3_arm3, under_grasp3_arm4;

extern u16 first_plcace1_arm1,first_plcace1_arm2,first_plcace1_arm3,first_plcace1_arm4;
extern u16 first_plcace2_arm1,first_plcace2_arm2,first_plcace2_arm3,first_plcace2_arm4;
extern u16 first_plcace3_arm1,first_plcace3_arm2,first_plcace3_arm3,first_plcace3_arm4;

extern u16 second_place1_arm1,second_place1_arm2,second_place1_arm3,second_place1_arm4;
extern u16 second_place2_arm1,second_place2_arm2,second_place2_arm3,second_place2_arm4;
extern u16 second_place3_arm1,second_place3_arm2,second_place3_arm3,second_place3_arm4;

extern u16 third_place1_arm1,third_place1_arm2,third_place1_arm3,third_place1_arm4;
extern u16 third_place2_arm1,third_place2_arm2,third_place2_arm3,third_place2_arm4;
extern u16 third_place3_arm1,third_place3_arm2,third_place3_arm3,third_place3_arm4;










extern void place_playload1(void);//放置第一个物体到小车载物台
extern void place_playload2(void);//
extern void place_playload3(void);

extern void grasp_playload1(void);//夹取载物台第一个物体
extern void grasp_playload2(void);
extern void grasp_playload3(void);


extern void top_grasp1(void);//顶层抓取相对于小车左边
extern void top_grasp2(void);//中间
extern void top_grasp3(void);//右边

extern void First_place1(void);//粗加工放置相对于小车左边
extern void First_place2(void);//中间
extern void First_place3(void);//右边

extern void Second_place1(void);//半成品区上层放置
extern void Second_place2(void);
extern void Second_place3(void);

extern void Third_place1(void);//第三次放置
extern void Third_place2(void);//第三次放置
extern void Third_place3(void);//第三次放置

//下层抓取时要小车退出来后调用void arm_back1()函数
extern void under_grasp1(void);//底层抓取相对于小车左边
extern void under_grasp2(void);//中间
extern void under_grasp3(void);//右边

extern void cujiagongclip1(void );//粗加工区夹取左边相对于小车
extern void cujiagongclip2(void);
extern void cujiagongclip3(void);


extern void scan_qr_on(void);//二维码识别姿势
extern void scan_qr_off(void);
extern void scan_block_top(void);//物块识别颜色姿势上层
extern void scan_block_under(void);//下层物块姿势

extern void grasp_state(void);
extern void reset_state(void);

extern  void  middle_state(void);
extern  void Arm_back(void);
extern  void Arm_back1(void);











#endif
