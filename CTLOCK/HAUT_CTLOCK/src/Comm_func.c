/*
 * comm_func.c
 *
 * Created: 2018/5/13 0:51:33
 *  Author: Huo
 */ 
#include <asf.h>

uint8_t Motor_status = 0;

void LedInit(void)
{
	struct port_config pin_config;
	port_get_config_defaults(&pin_config);
	
	pin_config.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_PIN,&pin_config);
	port_pin_set_output_level(LED_PIN,false);
}

void MotorInit(void)		//初始化电机、滑行状态,加锁舌和门磁,钥匙
{
	struct port_config pin_config;
	port_get_config_defaults(&pin_config);
	
	pin_config.direction = PORT_PIN_DIR_INPUT;
	port_pin_set_config(DOORSENSOR_PIN,&pin_config);
	port_pin_set_config(LOCK_PIN,&pin_config);
	port_pin_set_config(KEY_PIN,&pin_config);
	
	pin_config.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(MOTOR_nSLEEP_PIN,&pin_config);
	port_pin_set_config(MOTOR_IN1_PIN,&pin_config);
	port_pin_set_config(MOTOR_IN2_PIN,&pin_config);

	port_pin_set_output_level(MOTOR_nSLEEP_PIN,true);
	Motor_coast();
}

void Motor_coast(void)
{
	Motor_status = MotorStatus_coast;
	port_pin_set_output_level(MOTOR_IN1_PIN,false);
	port_pin_set_output_level(MOTOR_IN2_PIN,false);
}

void Motor_reverse(void)
{
	Motor_status = MotorStatus_reverse;
	port_pin_set_output_level(MOTOR_IN1_PIN,true);
	port_pin_set_output_level(MOTOR_IN2_PIN,false);
}

void Motor_rotate(void)
{
	Motor_status = MotorStatus_rotate;
	port_pin_set_output_level(MOTOR_IN1_PIN,false);
	port_pin_set_output_level(MOTOR_IN2_PIN,true);
}
void Motor_brake(void)
{
	Motor_status = MotorStatus_brake;
	port_pin_set_output_level(MOTOR_IN1_PIN,true);
	port_pin_set_output_level(MOTOR_IN2_PIN,true);
}
bool Door_key(void)
{
	if(port_pin_get_input_level(KEY_PIN))
	{
		return true;
	}
	else
		return false;
}
bool Door_lock(void)
{
	if(port_pin_get_input_level(LOCK_PIN))
	{
		return true;
	}
	else
	    return false;
}
bool Door_sensor(void)
{
	if(port_pin_get_input_level(DOORSENSOR_PIN))
	{
		return true;
	}
	else
		return false;
}