#include "deca_device_api.h"
#include "lcd.h"

//Credit to https://microcontrollerslab.com/16x2-lcd-interfacing-with-tm4c123-tiva-launchpad-keil-uvision/

void initLCD(void) {
    GPIO_setAsOutputPin(LCD_CMD_PORT,
                        LCD_EN_PIN +
                        LCD_RS_PIN +
                        LCD_RW_PIN);

    GPIO_setAsOutputPin(LCD_WRITE_PORT, 
                        LCD_D4_PIN + 
                        LCD_D5_PIN +
                        LCD_D6_PIN +
                        LCD_D7_PIN);
    deca_sleep(2);
    writeCmdLCD(CLR);
    writeCmdLCD(SET_5X7_FONT);       /* select 5x7 font size and 2 rows of LCD */
    writeCmdLCD(SET_4BIT_MODE);      /* Select 4-bit Mode of LCD */
    writeCmdLCD(MOVE_RIGHT);   						/* shift cursor right */
    writeCmdLCD(CLR);     /* clear whatever is written on display */
    writeCmdLCD(BLINK_CURSOR);       /* Enable Display and cursor blinking */
	displayLCD("Initialization", "Complete!");
}

void writeCmdLCD(unsigned char command) {
    writeNibbleLCD(command & 0xF0, 0); //Write upper nibble to data register
    writeNibbleLCD(command << 4, 0); //Write lower nibble to data register

    deca_sleep(2);
}

void displayLCD(char *line1, char *line2) {
    writeCmdLCD(BLINK_CURSOR);
    writeCmdLCD(FIRST_ROW); //First Row
    writeCmdLCD(CLR); //Clear Display
    writeStrLCD(line1);

    writeCmdLCD(SECOND_ROW); //Second Row
    writeStrLCD(line2);
    writeCmdLCD(CURSOR_OFF); //Turn Cursor off.
    deca_sleep(500);
}

void writeNibbleLCD(unsigned char data, unsigned char isData) {
    data &= 0xF0;
    isData &= 0x0F;

    GPIO_setOutputLowOnPin(LCD_WRITE_PORT, ~(data | isData));
    GPIO_setOutputHighOnPin(LCD_WRITE_PORT, (data | isData));

    GPIO_setOutputLowOnPin(LCD_WRITE_PORT, ~(data | isData));
    GPIO_setOutputHighOnPin(LCD_WRITE_PORT, (data | isData | LCD_EN_PIN));

    deca_sleep(0);
    GPIO_setOutputLowOnPin(LCD_WRITE_PORT, ~(data));
    GPIO_setOutputHighOnPin(LCD_WRITE_PORT, data);

    GPIO_setOutputLowOnPin(LCD_WRITE_PORT, 0xFF);
}

void writeCharLCD(unsigned char data) {
    writeNibbleLCD(data & 0xF0, 1); //Write upper nibble to data register
    writeNibbleLCD(data << 4, 1); //Write lower nibble to data register

    deca_sleep(1);
}

void writeStrLCD(char *str) {
    int i;
    for(i = 0; str[i] != 0; i++) {
        writeCharLCD(str[i]);
    }
}

void lcd_display_str(char *str) {
    writeCmdLCD(BLINK_CURSOR);
    writeCmdLCD(FIRST_ROW); //First Row
    writeCmdLCD(CLR); //Clear Display
    int i;
    for(i = 0; str[i] != 0 && i < 16; i++) {
        writeCharLCD(str[i]);
    }
    writeCmdLCD(SECOND_ROW); //Second Row
    for(; str[i] != 0; i++) {
        writeCharLCD(str[i]);
    }
    writeCmdLCD(CURSOR_OFF); //Turn Cursor off.
    deca_sleep(500);
}


