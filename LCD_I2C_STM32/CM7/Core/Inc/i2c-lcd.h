
#include "stm32h7xx_hal.h"
#define SLAVE_ADDRESS_LCD 0x4E // change this according to ur setup

void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_clear (void);  
