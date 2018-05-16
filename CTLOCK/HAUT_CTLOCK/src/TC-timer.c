/*
 * tc_timer.c
 *
 * Created: 2018/4/6 22:56:08
 *  Author: Huo
 */ 

#include <asf.h>


static void tc_callback_1s(struct tc_module *const module_inst )		
{
	//TODO
}



void configure_tc(void)
{
	struct tc_config config_tc;
	tc_get_config_defaults(&config_tc);

	config_tc.counter_size = TC_COUNTER_SIZE_16BIT;
	config_tc.clock_source = GCLK_GENERATOR_1;
	config_tc.wave_generation = TC_WAVE_GENERATION_MATCH_FREQ;
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV1024;
	config_tc.counter_16_bit.compare_capture_channel[0] = (0x0F42);

	tc_init(&tc_instance, CONF_TC_MODULE, &config_tc);

	tc_enable(&tc_instance);
	
	
}

void tc_1s_callbacks(void)
{
	tc_register_callback(&tc_instance, tc_callback_1s, TC_CALLBACK_CC_CHANNEL0);
	tc_enable_callback(&tc_instance, TC_CALLBACK_CC_CHANNEL0);
}