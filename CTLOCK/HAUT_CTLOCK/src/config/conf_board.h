/**
 * \file
 *
 * \brief User board configuration template
 *
 * Copyright (C) 2012-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

/** @def
 * BlueTooth Mode Pin
 */
#define BLE_VDD_PIN			PIN_PB22
#define	BLE_SLEEP_PIN		PIN_PB23
#define BLE_TX_PIN			PIN_PA24
#define BLE_RX_PIN			PIN_PA25
#define BLE_DATATI_PIN		PIN_PA23
#define BLE_STATUE_PIN		PIN_PA22
#define BLE_RST_PIN			PIN_PA21 
/** @def
 * Wi-Fi Mode Pin
 */
#define WIFI_VDD_PIN		PIN_PB10
#define WIFI_SLEEPOUT_PIN	PIN_PA11
#define WIFI_RST_PIN		PIN_PA10
#define WIFI_RX_PIN			PIN_PA09
#define WIFI_TX_PIN			PIN_PA08

/** @def
 * Button Mode Pin
 */
#define BUTTON_start_PIN		PIN_PB00
#define BUTTON_start_EIC_PIN	PIN_PB00A_EIC_EXTINT0
#define BUTTON_start_EIC_MUX    MUX_PB00A_EIC_EXTINT0
#define BUTTON_start_EIC_LINE	0

#define BUTTON_enter_PIN		PIN_PA07

#define BUTTON_0_PIN			PIN_PB09
#define BUTTON_1_PIN			PIN_PB03
#define BUTTON_2_PIN			PIN_PB06
#define BUTTON_3_PIN			PIN_PA04
#define BUTTON_4_PIN			PIN_PB02
#define BUTTON_5_PIN			PIN_PB07
#define BUTTON_6_PIN			PIN_PA05
#define BUTTON_7_PIN			PIN_PB01
#define BUTTON_8_PIN			PIN_PB08
#define BUTTON_9_PIN			PIN_PA06
/** @def
 * Buzzer Mode Pin
 */
#define BUZZER_PIN			PIN_PA20
/** @def
 * LED Mode Pin
 */
#define LED_PIN				PIN_PB11
/** @def
 * Finger Mode Pin
 */
#define FP_INT_PIN				 PIN_PA16
#define FP_EIC_PIN               PIN_PA16A_EIC_EXTINT0
#define FP_EIC_MUX               MUX_PA16A_EIC_EXTINT0
#define FP_EIC_PINMUX            PINMUX_PA16A_EIC_EXTINT0
#define FP_EIC_LINE              0

#define FP_RST_PIN		PIN_PA17
#define FP_RXD_PIN		PIN_PA18
#define FP_TXD_PIN		PIN_PA19
/** @def
 * Motor Mode Pin
 */
#define MOTOR_nSLEEP_PIN	PIN_PA13
#define MOTOR_IN1_PIN		PIN_PA14
#define MOTOR_IN2_PIN		PIN_PA15
/** @def
 * Horn Mode Pin
 */
#define HORN_SDA_PIN		PIN_PB16
#define HORN_SCL_PIN		PIN_PB17
/** @def
 * security Mode Pin
 */
#define SCR_SDA_PIN			PIN_PB04
#define SCR_SCL_PIN			PIN_PB05
/** @def
 * DoorSensor Lock Key Mode Pin
 */
#define DOORSENSOR_PIN		PIN_PA12
#define LOCK_PIN			PIN_PA15
#define KEY_PIN				PIN_PA14
/** @def
 * BatteryCheck Mode Pin
 */
#define BATTERYCHECK_PIN	PIN_PA02

#endif // CONF_BOARD_H

