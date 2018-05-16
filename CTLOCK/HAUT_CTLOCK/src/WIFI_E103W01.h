/*
 * WIFI_E103W01.h
 *
 * Created: 2018/4/4 22:34:10
 *  Author: Huo
 */ 


#ifndef WIFI_E103W01_H_
#define WIFI_E103W01_H_

struct usart_module usart_wifi_instance;

extern uint8_t wifi_transmitbuff[22]; 
#define MAX_RX_BUFFER_LENGTH   20
volatile uint8_t wifi_rx_buffer[MAX_RX_BUFFER_LENGTH];
//! [rx_buffer_var]


void configure_wifi_usart(void);
void configure_wifi_callbacks(void);
void WiFi_StartWorking(bool mode);
void wifi_power(bool mode);
void wifi_sleepout(bool mode);
void wifi_reset(bool mode);



#endif /* WIFI_E103W01_H_ */