#ifndef _GRASP_H
#define _GRASP_H
#include "headfiles.h"


extern void place_playload1(void);//���õ�һ�����嵽С������̨
extern void place_playload2(void);//
extern void place_playload3(void);

extern void grasp_playload1(void);//��ȡ����̨��һ������
extern void grasp_playload2(void);
extern void grasp_playload3(void);


extern void top_grasp1(void);//����ץȡ�����С�����
extern void top_grasp2(void);//�м�
extern void top_grasp3(void);//�ұ�

extern void First_place1(void);//�ּӹ����������С�����
extern void First_place2(void);//�м�
extern void First_place3(void);//�ұ�

extern void Second_place1(void);//���Ʒ���ϲ����
extern void Second_place2(void);
extern void Second_place3(void);

extern void Third_place1(void);//�����η���
extern void Third_place2(void);//�����η���
extern void Third_place3(void);//�����η���

//�²�ץȡʱҪС���˳��������void arm_back1()����
extern void under_grasp1(void);//�ײ�ץȡ�����С�����
extern void under_grasp2(void);//�м�
extern void under_grasp3(void);//�ұ�

extern void cujiagongclip1(void );//�ּӹ�����ȡ��������С��
extern void cujiagongclip2(void);
extern void cujiagongclip3(void);


extern void scan_qr_on(void);//��ά��ʶ������
extern void scan_qr_off(void);
extern void scan_block_top(void);//���ʶ����ɫ�����ϲ�
extern void scan_block_under(void);//�²��������

extern void grasp_state(void);
extern void reset_state(void);

extern void middle_state(void);
extern  void Arm_back(void);
extern  void Arm_back1(void);











#endif
