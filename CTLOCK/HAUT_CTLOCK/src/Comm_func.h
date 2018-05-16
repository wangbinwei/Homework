/*
 * Comm_func.h
 *
 * Created: 2018/5/13 0:51:50
 *  Author: Huo
 */ 


#ifndef COMM_FUNC_H_
#define COMM_FUNC_H_

typedef enum{
	MotorStatus_coast,
	MotorStatus_rotate,
	MotorStatus_reverse,
	MotorStatus_brake,
}MotorStatus_t;

void LedInit(void);
void MotorInit(void);
void Motor_coast(void);
void Motor_reverse(void);
void Motor_rotate(void);
void Motor_brake(void);


#endif /* COMM_FUNC_H_ */