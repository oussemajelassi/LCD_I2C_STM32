/*
 * LCD_I2C.h
 *
 *  Created on: Oct 2, 2023
 *      Author: Flooki
 */

#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_


#define LCD_I2C_SEND_CMD_EN_HIGH  0x0C
#define LCD_I2C_SEND_CMD_EN_LOW   0x08
#define LCD_I2C_SEND_DATA_EN_HIGH 0x0D
#define LCD_I2C_SEND_DATA_EN_LOW  0x09


#define SLAVE_ADDRESS_LCD 0x4E
typedef enum
{
	LCD_I2C_OKAY,
	LCD_I2C_FAIL
}LCD_I2C_STATE;




class LCD_I2C
{
public :
	char * LCD_I2C_FIRST_LINE  ;
	char * LCD_I2C_SECOND_LINE ;
	char * LCD_I2C_THIRD_LINE  ;
	char * LCD_I2C_FOURTH_LINE ;
public :
	LCD_I2C_STATE LCD_I2C_SEND_STRING (char * str) ;
	LCD_I2C_STATE LCD_I2C_SEND_CMD  (char Command ) ;
	LCD_I2C_STATE LCD_I2C_SEND_DATA (char Command ) ;
	LCD_I2C_STATE LCD_I2C_INIT (void ) ;
	void LCD_I2C_SET_FIRST_LINE (void) ;
	void LCD_I2C_SET_SECOND_LINE (void) ;
	void LCD_I2C_SET_THIRD_LINE (void) ;
	void LCD_I2C_SET_FOURTH_LINE (void) ;


};



#endif /* INC_LCD_I2C_H_ */
