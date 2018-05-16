/*
 * tc_timer.h
 *
 * Created: 2018/4/6 22:57:14
 *  Author: Huo
 */ 


#ifndef TC_TIMER_H_
#define TC_TIMER_H_

//[definition_tc]
#define CONF_TC_MODULE TC3
//[definition_tc]

//! [module_inst]
struct tc_module tc_instance;
//! [module_inst]

void configure_tc(void);
void tc_1s_callbacks(void);

#endif /* TC_TIMER_H_ */