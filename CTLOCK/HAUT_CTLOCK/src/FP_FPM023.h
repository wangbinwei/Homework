/*
 * Finger.h
 *
 * Created: 2018/4/15 21:19:55
 *  Author: Huo
 */ 


#ifndef FP_FPM023_H_
#define FP_FPM023_H_
#include <asf.h>

extern uint8_t finger_transmitbuff[40];
uint8_t finger_rx_buffer[26];

struct usart_module usart_finger_instance;

typedef enum{
	FPaction_No = 0,
	FPaction_Register,
	FPaction_CheckRegister,
	FPaction_CancelRegister,
	FPaction_SaveRegister,
	FPaction_CheckSaveRegister,
	FPaction_UpdateStorage,
	FPaction_CheckUpdateStorage,
	FPaction_Match,
	FPaction_CheckMatch,
	FPaction_CheckMatchResult,
	FPaction_Delate,
	FPaction_CheckDelate,
	}FPaction_list; 

void  FPaction(void);

void configure_FP(void);
void finger_reset(bool mode);

#endif /* FINGER_H_ */