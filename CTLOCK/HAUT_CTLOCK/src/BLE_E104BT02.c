/*
 * BLE_E104BT02.c
 *
 * Created: 2018/3/21 22:59:18
 *  Author: Huo
 */ 
#include <asf.h>
#include <stdio.h>



uint8_t ble_transmitbuff[20]= {
	0xAA,0x55,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00
};

static bool BLE_protocol_checksum(void);

//! [callback_funcs]
static void usart_read_callback(struct usart_module *const usart_module)
{
	uint8_t CommandId_high = ble_rx_buffer[2] & 0xF0;//修改类型
	uint8_t CommandId_low  = ble_rx_buffer[2] & 0x0F;
	uint8_t CheckSum;
	uint32_t i,data_length;
	switch(CommandId_high)
	{
		case BLE_ID_synClock:
		{
			data_length = 6;
			CheckSum = BLE_protocol_checksum(ble_rx_buffer, data_length); //时间年月日时分秒
			if (CheckSum == ble_rx_buffer[3])
			{
				//返回 接收成功
				ble_transmitbuff[2] = 0x10;//修改
				for(i=3;i<=data_length+3;i++)
				{
					ble_transmitbuff[i]=ble_rx_buffer[i];
				}
				//TODO
				usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
				//ToDO
				
			}
			else
			{
				//返回 校验和错
				ble_transmitbuff[3] = 0x18;
				//TODO
				usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
			}
			//TODO
			break;
		}
		case BLE_ID_CommunicationOut:
		{
			data_length = 0;
			CheckSum = BLE_protocol_checksum(ble_rx_buffer,data_length);
			if (CheckSum ==  ble_rx_buffer[3])
			{
				ble_transmitbuff[2] = 0x20;
				ble_transmitbuff[3] = CheckSum;
				usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
				//返回 接收成功
			}
			else
			{
				ble_transmitbuff[2] = 0x28;
				ble_transmitbuff[3] = CheckSum;
				//返回 校验和错
				usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
			}
			//TODO
			break;
		}
		case BLE_ID_FPRegister:
		{
			if(CommandId_low == 0x01)
			{
				data_length = 16;//智能锁UUID,锁原先要存储好自身的UUID,进行验证
				CheckSum = BLE_protocol_checksum(ble_rx_buffer,data_length);
				if (CheckSum == ble_rx_buffer[3])
				{
					ble_transmitbuff[2] = 0x51;//修改
					for(i=3;i<=data_length+3;i++)
					{
						ble_transmitbuff[i]=ble_rx_buffer[i];
					}
					//返回 接收成功
					//TODO
					usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
					//TODO
				}
				else
				{
					//返回 校验和错
					ble_transmitbuff[2] = 0x59;//修改
					//TODO
					usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
				}	
			}
			else if(CommandId_low == 0x07)
			{
				data_length = 14;//手机IMEI码(8B)和手机蓝牙MAC地址(6B)，还要锁内存里进行验证
				CheckSum = BLE_protocol_checksum(ble_rx_buffer,data_length);
				if(CheckSum == ble_rx_buffer[3])
				{
					ble_transmitbuff[2] = 0x57;
					for(i=3;i<=data_length+3;i++)
					{
						ble_transmitbuff[i]=ble_rx_buffer[i];
					}
					//进行指纹录入 
					usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
				}
				else
				{
					//返回 校验和错
					ble_transmitbuff[2] = 0x5F;
					usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
				}
			}
			
			//TODO
			break;
		}
		case BLE_ID_FPDelate:
		{
			if(CommandId_low == 0x01)
			{
				data_length = 16;//电子锁的UUID 进行验证
				CheckSum = 	BLE_protocol_checksum(ble_rx_buffer, data_length);
				if(CheckSum == ble_rx_buffer[3])
				{
					ble_transmitbuff[2] = 0xC1;
					for(i=3;i<=data_length+3;i++)
					{
						ble_transmitbuff[i]=ble_rx_buffer[i];
					}
					usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
				}
				else
				{
					//返回 校验和错
					ble_transmitbuff[3] = 0xC9;
					//TODO
					usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
					//TODO
				}
			}
			else if(CommandId_low == 0x02)
			{
				data_length = 14;//手机IMEI码(8B)和手机蓝牙MAC地址(6B)，还要锁内存里进行验证
				CheckSum = BLE_protocol_checksum(ble_rx_buffer,data_length);
				if(CheckSum == ble_rx_buffer[3])
				{
					ble_transmitbuff[2] = 0xC2;
					for(i=3;i<=data_length+3;i++)
					{
						ble_transmitbuff[i]=ble_rx_buffer[i];
					}
					usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
				}
				else
				{
					ble_transmitbuff[3] = 0xCA;
					//TODO
					usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
					//TODO
				}
			}
			else if(CommandId_low == 0x07)
			{
				data_length =1;//指纹编号
				CheckSum = BLE_protocol_checksum(ble_rx_buffer,data_length);
				if(CheckSum == ble_rx_buffer[3])
				{
					ble_transmitbuff[2] = 0xC7;
					for(i=3;i<=data_length+3;i++)
					{
						ble_transmitbuff[i]=ble_rx_buffer[i];
					}
					usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
				}
				else
				{
					ble_transmitbuff[3] = 0xCF;
					//TODO
					usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
					//TODO
				}
			}
			//MCU发个指纹验证结果没写
			
			
			
			break;
		}
		case BLE_ID_LockOpen:
		{
			if (CheckSum)
			{
				//返回 接收成功
				ble_transmitbuff[3] = 0x81;
				//TODO
				usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
				//TODO
				Motor_rotate();
			}
			else
			{
				//返回 校验和错
				ble_transmitbuff[3] = 0x89;
				//TODO
				usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
			}
			break;
		}
		default:
		break;
	}
	//port_pin_toggle_output_level(LED_PIN);
	//port_pin_set_output_level(LED_PIN, true);
	//delay_s(1);
	//usart_write_buffer_job(&usart_ble_instance, (uint8_t *)ble_transmitbuff, 20);
	
	//usart_write_buffer_job(&usart_ble_instance,
	//(uint8_t *)rx_buffer, MAX_RX_BUFFER_LENGTH);
}

static void usart_write_callback(struct usart_module *const usart_module)
{
	//port_pin_toggle_output_level(LED_PIN);
	//port_pin_set_output_level(LED_PIN, false);
}
//! [callback_funcs]


void configureBLE_usart(void)
{
	struct usart_config ble_configure_usart;
	usart_get_config_defaults(&ble_configure_usart);
	
	ble_configure_usart.baudrate    = 19200;
	ble_configure_usart.mux_setting = USART_RX_3_TX_2_XCK_3;
	ble_configure_usart.pinmux_pad0 = PINMUX_UNUSED;
	ble_configure_usart.pinmux_pad1 = PINMUX_UNUSED;
	ble_configure_usart.pinmux_pad2 = PINMUX_PA24C_SERCOM3_PAD2;
	ble_configure_usart.pinmux_pad3 = PINMUX_PA25C_SERCOM3_PAD3;

	while (usart_init(&usart_ble_instance,SERCOM3, &ble_configure_usart) != STATUS_OK) {}

	usart_enable(&usart_ble_instance);
	
	//! [setup_register_callbacks]
	usart_register_callback(&usart_ble_instance,usart_write_callback, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_register_callback(&usart_ble_instance,usart_read_callback, USART_CALLBACK_BUFFER_RECEIVED);

	usart_enable_callback(&usart_ble_instance, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable_callback(&usart_ble_instance, USART_CALLBACK_BUFFER_RECEIVED);
	//! [setup_enable_callbacks]
	
	//!other_pin_init
	struct port_config pin_config;
	port_get_config_defaults(&pin_config);
	
	pin_config.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(BLE_VDD_PIN,&pin_config);
	ble_power(true);
	delay_ms(200);
	port_pin_set_config(BLE_SLEEP_PIN,&pin_config);
	ble_sleep(false);
	delay_ms(30);
	port_pin_set_config(BLE_RST_PIN,&pin_config);
	ble_reset(false);
		
	pin_config.direction = PORT_PIN_DIR_INPUT;
	port_pin_set_config(BLE_DATATI_PIN,&pin_config);
	port_pin_set_config(BLE_STATUE_PIN,&pin_config);
	
}


//PIN_PB22
void ble_power(bool mode)
{
	if (mode)
		port_pin_set_output_level(BLE_VDD_PIN, true);
	else
		port_pin_set_output_level(BLE_VDD_PIN, false);
}

void ble_sleep(bool mode)
{
	if (mode)
		port_pin_set_output_level(BLE_SLEEP_PIN, true);
	else
		port_pin_set_output_level(BLE_SLEEP_PIN, false);
}

void ble_reset(bool mode)
{
	if(mode)
		port_pin_set_output_level(BLE_RST_PIN, true);
	else
		port_pin_set_output_level(BLE_RST_PIN, false);
}
	
bool ble_is_data_transmission(void)
{
	if (port_pin_get_input_level(BLE_DATATI_PIN))
	{
		return false;
	} 
	else
	{
		return true;
	}
}

bool ble_con_state(void)
{
	if (port_pin_get_input_level(BLE_STATUE_PIN))
	{
		return false;
	}
	else
	{
		return true;
	}
}
static uint8_t BLE_protocol_checksum(uint8_t *data, uint32_t length)
{
	uint32_t i = 0;
	uint8_t sum = 0x55 + 0xAA + data[2];
	for(i=4;i<=3+length;i++)
	sum+=data[i];
	return (uint8_t)((~sum)+1);
}