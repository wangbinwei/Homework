/*
 * Finger.c
 *
 * Created: 2018/4/15 21:19:40
 *  Author: Huo
 */ 
#include <asf.h>

bool FPaction_Register_FLAG = false;
static uint8_t FPaction_Register_REG_IDX = 0x01;
uint16_t FP_ID = 0 ;

uint8_t finger_transmitbuff[40] = {18,
	0xF1,0x1F,0xE2,0x2E,0xB6,0x6B,0xA8,0x8A,  //帧头
	0x00,0x07,								  //Dala Len
	0x86,									  //帧头校验
	0x00,0x00,0x00,0x00,					  //校验密码
	0x01,0x21,								  //CMD1&CMD2
	0xDE,
	0x00,
	0xa5,0xa6,0xa7,0xa8,
	0xb5,0xb6,0xb7,0xb8,
};
static uint8_t FP_protocol_checksum(uint8_t *data,uint32_t length)
{
	uint32_t i = 0;
	uint8_t sum = 0;
	for(i=0;i<length;i++)
	sum+=data[i];
	return (uint8_t)((~sum)+1);
}
uint8_t FPaction_Flag =0 ;

void  FPaction(void)
{
	switch(FPaction_Flag){
		case FPaction_Register:
		{
			finger_transmitbuff[10] = 0x08;
			finger_transmitbuff[11] = FP_protocol_checksum(finger_transmitbuff+1,10);
			finger_transmitbuff[16] = 0x01;
			finger_transmitbuff[17] = 0x11;
			finger_transmitbuff[18] = FPaction_Register_REG_IDX;
			finger_transmitbuff[19] = FP_protocol_checksum(finger_transmitbuff+12,7);
			finger_transmitbuff[0] = 19;
			usart_write_buffer_job(&usart_finger_instance, finger_transmitbuff+1, finger_transmitbuff[0]);
			break;
		}
		case FPaction_CheckRegister:
		{
			finger_transmitbuff[10] = 0x07;
			finger_transmitbuff[11] = FP_protocol_checksum(finger_transmitbuff+1,10);
			finger_transmitbuff[16] = 0x01;
			finger_transmitbuff[17] = 0x12;
			finger_transmitbuff[18] = FP_protocol_checksum(finger_transmitbuff+12,6);
			finger_transmitbuff[0] = 18;
			usart_write_buffer_job(&usart_finger_instance, finger_transmitbuff+1, finger_transmitbuff[0]);
			break;
		}
		case FPaction_CancelRegister:
		{
			finger_transmitbuff[10] = 0x07;
			finger_transmitbuff[11] = FP_protocol_checksum(finger_transmitbuff+1,10);
			finger_transmitbuff[16] = 0x01;
			finger_transmitbuff[17] = 0x15;
			finger_transmitbuff[18] = FP_protocol_checksum(finger_transmitbuff+12,6);
			finger_transmitbuff[0] = 18;
			usart_write_buffer_job(&usart_finger_instance, finger_transmitbuff+1, finger_transmitbuff[0]);
			break;
		}
		case FPaction_SaveRegister:
		{
			finger_transmitbuff[10] = 0x09;
			finger_transmitbuff[11] = FP_protocol_checksum(finger_transmitbuff+1,10);
			finger_transmitbuff[16] = 0x01;
			finger_transmitbuff[17] = 0x13;
			finger_transmitbuff[18] = (FP_ID >> 8) & 0xFF;
			finger_transmitbuff[19] = FP_ID & 0xFF;
			finger_transmitbuff[20] = FP_protocol_checksum(finger_transmitbuff+12,6);
			finger_transmitbuff[0] = 20; //修改长度
			usart_write_buffer_job(&usart_finger_instance, finger_transmitbuff+1, finger_transmitbuff[0]);
			break;
		}
		case FPaction_CheckSaveRegister:
		{
			finger_transmitbuff[10] = 0x07;
			finger_transmitbuff[11] = FP_protocol_checksum(finger_transmitbuff+1,10);
			finger_transmitbuff[16] = 0x01;
			finger_transmitbuff[17] = 0x14;
			finger_transmitbuff[18] = FP_protocol_checksum(finger_transmitbuff+12,6);
			finger_transmitbuff[0] = 18;
			usart_write_buffer_job(&usart_finger_instance, finger_transmitbuff+1, finger_transmitbuff[0]);
			break;
		}
		case FPaction_CheckMatch:
		{
			finger_transmitbuff[10] = 0x07;
			finger_transmitbuff[11] = FP_protocol_checksum(finger_transmitbuff+1,10);
			finger_transmitbuff[16] = 0x01;
			finger_transmitbuff[17] = 0x21;
			finger_transmitbuff[18] = FP_protocol_checksum(finger_transmitbuff+12,6);
			finger_transmitbuff[0] = 18;
			usart_write_buffer_job(&usart_finger_instance, finger_transmitbuff+1, finger_transmitbuff[0]);
			break;
		}
		case FPaction_CheckMatchResult:
		{
			finger_transmitbuff[10] = 0x07;
			finger_transmitbuff[11] = FP_protocol_checksum(finger_transmitbuff+1,10);
			finger_transmitbuff[16] = 0x01;
			finger_transmitbuff[17] = 0x22;
			finger_transmitbuff[18] = FP_protocol_checksum(finger_transmitbuff+12,6);
			finger_transmitbuff[0] = 18;
			usart_write_buffer_job(&usart_finger_instance, finger_transmitbuff+1, finger_transmitbuff[0]);
			break;
		}
		case FPaction_Delate:
		{
			finger_transmitbuff[10] = 0x0A;
			finger_transmitbuff[11] = FP_protocol_checksum(finger_transmitbuff+1,10);
			finger_transmitbuff[16] = 0x01;
			finger_transmitbuff[17] = 0x31;
			finger_transmitbuff[18] = 0x00;		//清除单个指纹
			finger_transmitbuff[19] = (FP_ID >> 8) & 0xFF;
			finger_transmitbuff[20] = FP_ID & 0xFF;
			finger_transmitbuff[21] = FP_protocol_checksum(finger_transmitbuff+12,6);
			finger_transmitbuff[0] = 21;
			usart_write_buffer_job(&usart_finger_instance, finger_transmitbuff+1, finger_transmitbuff[0]);
			
			break;
		}
		case FPaction_CheckDelate:
		{
			finger_transmitbuff[10] = 0x07;
			finger_transmitbuff[11] = FP_protocol_checksum(finger_transmitbuff+1,10);
			finger_transmitbuff[16] = 0x01;
			finger_transmitbuff[17] = 0x32;
			finger_transmitbuff[18] = FP_protocol_checksum(finger_transmitbuff+12,6);
			finger_transmitbuff[0] = 18;
			usart_write_buffer_job(&usart_finger_instance, finger_transmitbuff+1, finger_transmitbuff[0]);
			break;
		}
		default:
			break;
	}
	//FPaction_Flag = FPaction_No;
}

//! [callback_funcs]
static void usart_read_callback(struct usart_module *const usart_module)
{
	//port_pin_toggle_output_level(LED_PIN);
	switch(FPaction_Flag)
	{
		case FPaction_Register:
		{
			if ( finger_rx_buffer[20]==0 )
			{
				FPaction_Flag = FPaction_CheckRegister;
				FPaction();
			}
			break;
		}
		case FPaction_CheckRegister:
		{
			if (finger_rx_buffer[0]==0xF1 && finger_rx_buffer[1]==0x1F )
			{
				if (finger_rx_buffer[20]==0)
				{
					usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,4);
				}
				else if(finger_rx_buffer[20]==4) //添加
				{
					usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,1);
					delay_ms(200);
					FPaction_Flag = FPaction_CheckRegister;
					FPaction();
				}
				else
				{
					usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,1);
				}	
			}
			else
			{
				if (finger_rx_buffer[1]!=0x1F)
				{
					if (finger_rx_buffer[2]>=0x64)
					{
						FPaction_Register_REG_IDX = 1;//添加
						FP_ID = (finger_rx_buffer[0] << 8)|(finger_rx_buffer[1] & 0xFF); //修改 
						FPaction_Flag = FPaction_SaveRegister;
						FPaction();
					}
					else
					{
						if (FPaction_Register_REG_IDX == 6)
						{
							FPaction_Register_REG_IDX = 1;//添加
							FPaction_Flag = FPaction_CancelRegister;
							//TODO 指纹注册6次，进度没有到100，取消指纹注册并通知蓝牙注册失败
							//usart_write_buffer_job(&usart_ble_instance, finger_rx_buffer, 22);//注册失败，通知蓝牙  //此时rx_buffer只有4位
							FPaction();
						} 
						else
						{
							FPaction_Flag = FPaction_Register;
							FPaction_Register_REG_IDX += 1;
							FPaction();//添加
						}						
					}
				} 
				else
				{
					//TODO
				}
			}
			break;
		}
		case FPaction_SaveRegister:
		{	
			if(finger_rx_buffer[20]==0) //添加
			{
				FPaction_Flag = FPaction_CheckSaveRegister;
				FPaction();	
			}
			break;
		}
		case FPaction_CheckSaveRegister: //已修改
		{
			if (finger_rx_buffer[20]==0)// 修改 21为20
			{
				//TODO 
				//将保存成功的指纹ID_H和ID_L写入将要发送蓝牙的指令包
				usart_write_buffer_job(&usart_ble_instance, finger_rx_buffer, 24); //保存指纹成功，通知蓝牙
			} 
			else if(finger_rx_buffer[20]==0x0F) //指纹重复ID
			{
				usart_write_buffer_job(&usart_ble_instance, finger_rx_buffer, 24); //保存指纹失败，通知蓝牙
			}
			else if(finger_rx_buffer[20]==0x04) //未保存成功
			{
				delay_ms(200);
				FPaction_Flag = FPaction_CheckSaveRegister;
			}
			break;
		}
		case FPaction_CancelRegister:
		{
			usart_write_buffer_job(&usart_ble_instance,finger_rx_buffer,22);//添加 注册失败，通知蓝牙
			break;
		}
		case FPaction_CheckMatch:
		{ 
			FPaction_Flag = FPaction_CheckMatchResult;
			FPaction();
			break;
		}
		case FPaction_CheckMatchResult:
		{
			if (finger_rx_buffer[0]==0xF1 && finger_rx_buffer[1]==0x1F)
			{
				if(finger_rx_buffer[21]  == 0)
				{
					usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,7);
				}
				else if(finger_rx_buffer[21]  == 0x0A)
				{
					usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,7);
				}
				else if(finger_rx_buffer[21]  == 0x04) //修改
				{
					usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,1);
					delay_ms(200);
					FPaction_Flag = FPaction_CheckMatchResult;
					FPaction();
				}
				else
				{
					usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,1);
				}
			} 
			else
			{
				if(finger_rx_buffer[0]!=0xF1)
				{
					if(finger_rx_buffer[1])
					{
						//匹配成功，将匹配的指纹ID号发给WiFi模块，并且打开门
						//TODO
						usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,7);
					}
					
				}
			}
			break;
		}
		case FPaction_Delate:
		{
			if (finger_rx_buffer[0]==0xF1 && finger_rx_buffer[1]==0x1F)
			{
				if(finger_rx_buffer[20] ==0)
				{
					FPaction_Flag = FPaction_CheckDelate;
					FPaction();
				}
			}
			break;
		}
		case FPaction_CheckDelate:
		{
			if (finger_rx_buffer[0]==0xF1 && finger_rx_buffer[1]==0x1F)
			{
				if(finger_rx_buffer[20] ==0)
				{
					//TODO
					//指纹清除成功，通知蓝牙
					usart_write_buffer_job(&usart_ble_instance,finger_rx_buffer,22);
				}
			}
			break;
		}
		default:
			break;
	}
	
	
}

static void usart_write_callback(struct usart_module *const usart_module)
{
	//port_pin_toggle_output_level(LED_PIN);
	switch(FPaction_Flag)
	{
		delay_ms(2);
		case FPaction_Register:
		{	
			usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,22);
			break;
		}
		case FPaction_CheckRegister:
		{
			usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,21);
			break;
		}
		case FPaction_CancelRegister:
		{
			usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,18); //修改长度
			break;
		}
		case FPaction_SaveRegister:
		{
			usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,22); //修改长度
			break;
		}
		case FPaction_CheckSaveRegister:
		{
			usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,24);
			break;
		}
		case FPaction_CheckMatch:
		{
			usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,22);
			break;
		}
		case FPaction_CheckMatchResult:
		{
			usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,21);
			break;
		}
		case FPaction_Delate:
		{
			usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,22);
			break;
		}		
		case FPaction_CheckDelate:
		{
			usart_read_buffer_job(&usart_finger_instance,finger_rx_buffer,22);
			break;
		}
		default:
			break;
	}
	
}
static void extint_detection_callback(void)
{
	port_pin_toggle_output_level(LED_PIN);
	if(FPaction_Register_FLAG)
	{
		FPaction_Flag = FPaction_Register;
		//(FPaction_Register_REG_IDX > 6)?0:FPaction_Register_REG_IDX;
		FPaction();
	}
	else
	{
		FPaction_Flag = FPaction_CheckMatch;
		FPaction();
	}


	
}

void configure_FP(void)
{
	/**FP model EIC INT init**/
	struct extint_chan_conf config_extint_FPINT;
	extint_chan_get_config_defaults(&config_extint_FPINT);
	config_extint_FPINT.gpio_pin           = PIN_PA16A_EIC_EXTINT0;
	config_extint_FPINT.gpio_pin_mux       = MUX_PA16A_EIC_EXTINT0;
	config_extint_FPINT.gpio_pin_pull      = EXTINT_PULL_UP;
	config_extint_FPINT.detection_criteria = EXTINT_DETECT_FALLING;
	extint_chan_set_config(FP_EIC_LINE, &config_extint_FPINT);
		
	/**FP model EIC INT callback**/
	extint_register_callback(extint_detection_callback,	FP_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(FP_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
		
	/**FP model usart init**/
	struct usart_config finger_configure_usart;
	usart_get_config_defaults(&finger_configure_usart);

	finger_configure_usart.baudrate    = 115200;
	finger_configure_usart.mux_setting = USART_RX_3_TX_2_XCK_3;
	finger_configure_usart.pinmux_pad0 = PINMUX_UNUSED;
	finger_configure_usart.pinmux_pad1 = PINMUX_UNUSED;
	finger_configure_usart.pinmux_pad2 = PINMUX_PA18C_SERCOM1_PAD2;//PINMUX_PA18C_SERCOM1_PAD2
	finger_configure_usart.pinmux_pad3 = PINMUX_PA19C_SERCOM1_PAD3;//PINMUX_PA19C_SERCOM1_PAD3

	while (usart_init(&usart_finger_instance,SERCOM1, &finger_configure_usart) != STATUS_OK) {}
	usart_enable(&usart_finger_instance);
	
	/**FP model usart callback**/
	usart_register_callback(&usart_finger_instance,usart_write_callback, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_register_callback(&usart_finger_instance,usart_read_callback, USART_CALLBACK_BUFFER_RECEIVED);

	usart_enable_callback(&usart_finger_instance, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable_callback(&usart_finger_instance, USART_CALLBACK_BUFFER_RECEIVED);
		
	/**FP model other pin init **/
	struct port_config pin_config;
	port_get_config_defaults(&pin_config);
	
	pin_config.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(FP_RST_PIN,&pin_config);
	finger_reset(false);
	
	//pin_config.direction = PORT_PIN_DIR_INPUT;
	//port_pin_set_config(FP_INT_PIN, &pin_config);
}


void finger_reset(bool mode)
{
	if(mode)
	port_pin_set_output_level(FP_RST_PIN, false);
	else
	port_pin_set_output_level(FP_RST_PIN, true);
}
