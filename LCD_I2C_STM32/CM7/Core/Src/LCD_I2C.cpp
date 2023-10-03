/*
 * LCD_I2C.cpp
 *
 *  Created on: Oct 2, 2023
 *      Author: Flooki
 */

#include "LCD_I2C.h"
#include "stdint.h"
#include "main.h"



extern I2C_HandleTypeDef hi2c1;


LCD_I2C_STATE LCD_I2C::LCD_I2C_INIT ( void )
{
	HAL_Delay(50);  // wait for >40ms
	LCD_I2C::LCD_I2C_SEND_CMD (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	LCD_I2C::LCD_I2C_SEND_CMD (0x30);
	HAL_Delay(1);  // wait for >100us
	LCD_I2C::LCD_I2C_SEND_CMD (0x30);
	HAL_Delay(10);
	LCD_I2C::LCD_I2C_SEND_CMD (0x20);  // 4bit mode
	HAL_Delay(10);

	// dislay initialisation
	LCD_I2C::LCD_I2C_SEND_CMD (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	LCD_I2C::LCD_I2C_SEND_CMD (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	LCD_I2C::LCD_I2C_SEND_CMD (0x01);  // clear display
	HAL_Delay(1);
	LCD_I2C::LCD_I2C_SEND_CMD (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	LCD_I2C::LCD_I2C_SEND_CMD (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}


/*
 * We Are sending a command to the screen, The screen takes on 4 bits data each time
 * We are sending command so RS Bit must be set to 0
 * Each time we are sending four bits we need to alter EN bit between 1 and 0
 */

LCD_I2C_STATE LCD_I2C::LCD_I2C_SEND_CMD (char Command )
{
	char command_low , command_high ;
	uint8_t data [ 4 ] ;
	command_high = ( ( Command >> 4 ) & (0b11110000) ) ;
	command_low =  ( Command & 0b11110000 ) ;

	data [ 0 ] = ( command_high | LCD_I2C_SEND_CMD_EN_HIGH  ) ;
	data [ 1 ] = ( command_high | LCD_I2C_SEND_CMD_EN_LOW   ) ;
	data [ 2 ] = ( command_low  | LCD_I2C_SEND_CMD_EN_HIGH  ) ;
	data [ 3 ] = ( command_low  | LCD_I2C_SEND_CMD_EN_LOW   ) ;

	HAL_StatusTypeDef Outcome = HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, data, 4, 100) ;
	if (Outcome == HAL_OK ){ return ( LCD_I2C_OKAY ) ; }
	else {return ( LCD_I2C_FAIL) ; }
}


LCD_I2C_STATE LCD_I2C::LCD_I2C_SEND_DATA (char Command )
{
	char command_low , command_high ;
		uint8_t data [ 4 ] ;
		command_high = ( ( Command >> 4 ) & (0b11110000) ) ;
		command_low =  ( Command & 0b11110000 ) ;

		data [ 0 ] = ( command_high | LCD_I2C_SEND_DATA_EN_HIGH  ) ;
		data [ 1 ] = ( command_high | LCD_I2C_SEND_DATA_EN_LOW   ) ;
		data [ 2 ] = ( command_low  | LCD_I2C_SEND_DATA_EN_HIGH  ) ;
		data [ 3 ] = ( command_low  | LCD_I2C_SEND_DATA_EN_LOW   ) ;

		return ( LCD_I2C_OKAY ) ;
}
