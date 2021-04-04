#ifndef __PID_H
#define __PID_H

#include "sys.h"

int balanceX(float Angle);
int balanceY(float Angle);

int PID_Speed_Left_Front(float speed);
int PID_Speed_Left_Behind(float speed);
int PID_Speed_Right_Front(float speed);
int PID_Speed_Right_Behind(float speed);

#endif


