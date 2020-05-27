#ifndef LCD_H
#define LCD_H

void LCD_init(void);
void LCD_writeData(u8 data);
void LCD_writeCmd(u8 cmd);
void LCD_writeStr(u8* str);
void LCD_writePort(u8 data);

#endif
