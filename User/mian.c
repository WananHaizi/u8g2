#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "u8g2.h"

uint8_t u8g2_gpio_and_delay_stm32(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr)
{
	switch(msg)
	{
			case U8X8_MSG_DELAY_MILLI://Function which implements a delay, arg_int contains the amount of ms
				Delay_ms(arg_int);
			break;
			
			case U8X8_MSG_DELAY_10MICRO://Function which delays 10us
				Delay_us(10);
			break;
			
			case U8X8_MSG_DELAY_100NANO://Function which delays 100ns
				__NOP();
			break;

			case U8X8_MSG_GPIO_I2C_CLOCK:
				if (arg_int) OLED_W_SCL(1);
				else OLED_W_SCL(0);
			break;
			
			case U8X8_MSG_GPIO_I2C_DATA:
				if (arg_int)OLED_W_SDA(1);
				else OLED_W_SDA(0);
			break;
			default:
				return 0; //A message was received which is not implemented, return 0 to indicate an error
	}

	return 1; // command processed successfully.
}

int main(void)
{
	u8g2_t u8g2;
	OLED_Init();
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_sw_i2c, u8g2_gpio_and_delay_stm32);
	u8g2_InitDisplay(&u8g2); 
	u8g2_SetPowerSave(&u8g2, 0);
	u8g2_ClearBuffer(&u8g2);

	u8g2_DrawLine(&u8g2, 0,0,127,63);
	u8g2_DrawLine(&u8g2, 127,0,0,63);
	u8g2_SendBuffer(&u8g2);	

	while(1)
	{
		
	}
}
