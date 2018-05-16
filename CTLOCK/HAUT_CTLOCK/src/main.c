/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>


int main (void)
{
	system_init();
	LedInit();
	delay_init();
	delay_ms(300);
	configure_FP();
	configureBLE_usart();
	configure_wifi_usart();
	
	MotorInit();
	Motor_rotate();
	
	while(1)
	{
		//port_pin_toggle_output_level(LED_PIN);
		//FPaction_Flag = FPaction_CheckRegister;
		//FPaction();
		//delay_s(2);
		
	}

	/* Insert application code here, after the board has been initialized. */
}
