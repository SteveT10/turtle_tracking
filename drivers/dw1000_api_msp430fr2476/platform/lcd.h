#ifndef _LCD_H_
#define _LCD_H_
#include "driverlib.h"

#define LCD_RS_PIN GPIO_PIN0
#define LCD_RW_PIN GPIO_PIN1
#define LCD_EN_PIN GPIO_PIN2

#define LCD_CMD_PORT GPIO_PORT_P2

#define LCD_D4_PIN GPIO_PIN4
#define LCD_D5_PIN GPIO_PIN5
#define LCD_D6_PIN GPIO_PIN6
#define LCD_D7_PIN GPIO_PIN7
#define LCD_DATA_PINS (LCD_D7_PIN + LCD_D6_PIN + LCD_D5_PIN + LCD_D4_PIN)

#define LCD_WRITE_PORT GPIO_PORT_P2

//CMD Commands
#define CLR 0x01
#define MOVE_HOME 0x02
#define MOVE_RIGHT 0x06
#define MOVE_LEFT 0x08
#define BLINK_CURSOR 0x0F
#define SET_4BIT_MODE 0x28
#define SET_5X7_FONT 0x20
#define FIRST_ROW 0x80
#define SECOND_ROW 0xC0

#define SHIFT_RIGHT 0x1C
#define SHIFT_LEFT 0x18

#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E

#define ENTRY_MODE 0x06
void initLCD(void);

/**
 * Writes a CMD command to the LCD.
 */
void writeCmdLCD(unsigned char command);

/**
 * Prints two input strings on on the two rows of the LCD
 * @param line1 is the string to appear on top row.
 * @param line2 is the string to appear on the bottom row.
 */
void displayLCD(char *line1, char *line2);

/**
 * 
 */
void writeNibbleLCD(unsigned char nibble, unsigned char isData);

/**
 * Writes a character to the LCD data register
 * @param data is the character to write.
 */
void writeCharLCD(unsigned char data);

/**
 * Writes a string to the LCD data register.
 * Row must be set before calling this function.
 *
 * @param str is the string to write.
 */
void writeStrLCD(char *str);

/**
 * Writes a string to the LCD.
 * Max of 32 characters, upon writing 16 characters to first row,
 * move to second row and continue writing.
 *
 * @param str is the string to display.
 */
void lcd_display_str(char *str);

#endif

