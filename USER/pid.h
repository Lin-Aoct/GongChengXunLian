#ifndef __PID_H
#define __PID_H

#include "sys.h"

int balanceX(float Angle);
int balanceY(float Angle);

int PID_Speed_Left_Front(float speed);
int PID_Speed_Left_Behind(float speed);
int PID_Speed_Right_Front(float speed);
int PID_Speed_Right_Behind(float speed);

void PID_Limit(u8 side, int* value);
void Set_PID_Value(u8 side, u8 part, u8 action, float value);
void Change_Speed_Target(u8 side, u8 action, u8 value);
void Set_Speed_Target(u8 side, u8 value);
void Reset_Target_Speed(void);
void Set_Expect_Target_Speed(u8 speed);

#endif
