#ifndef __PID_H
#define __PID_H

#include "sys.h"

int balanceX(float Angle);
int balanceY(float Angle);

int PID_Speed_Left_Front(float speed);
int PID_Speed_Left_Behind(float speed);
int PID_Speed_Right_Front(float speed);
int PID_Speed_Right_Behind(float speed);
void PID_Limit(int* value);
void Set_PID_Value(u8 side, u8 part, u8 action, float value);

#endif


