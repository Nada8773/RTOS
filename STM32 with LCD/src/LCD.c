#include "STD_TYPES.h"
#include "GPIO.h"
#include "LCD.h"
#include "LCD_CFG.h"

#define GET_BIT(VAR, BIT_NUM)  ((VAR >> BIT_NUM) & 0x1)

GPIO_initStruct lcdControl;
GPIO_initStruct lcdData;

void LCD_init(void)
{
	volatile u32 i = 0;

	lcdControl.port = LCD_CONTROL_PORT;
	lcdControl.pin = LCD_RS_PIN | LCD_E_PIN;
	lcdControl.mode = GPIO_OUTPUT_GP_PP;
	lcdControl.speed = GPIO_OUTPUT_2MHZ;

	lcdData.port = LCD_DATA_PORT;
	lcdData.pin = LCD_D4_PIN | LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN;
	lcdData.mode = GPIO_OUTPUT_GP_PP;
	lcdData.speed = GPIO_OUTPUT_2MHZ;

	GPIO_init(&lcdControl);
	GPIO_init(&lcdData);

	for (i = 0; i < 5000; i++);
	LCD_writeCmd(0b00000010);
	LCD_writeCmd(0b00101000);
	LCD_writeCmd(0b00001100);
	LCD_writeCmd(0b00000001);
	for (i = 0; i < 500; i++);
}

void LCD_writeData(u8 data)
{
	volatile u32 i = 0;
	u8 dataPart = data & 0xF0;
	/* RS = 1 */
	GPIO_writePin(&lcdControl, GPIO_PIN_SET, GPIO_PIN_0);
	LCD_writePort(dataPart);

	GPIO_writePin(&lcdControl, GPIO_PIN_SET, GPIO_PIN_10);
	for (i = 0; i < 500; i++);

	GPIO_writePin(&lcdControl, GPIO_PIN_RESET, GPIO_PIN_10);
	for (i = 0; i < 500; i++);


	dataPart = (data & 0x0F) << 4;

	LCD_writePort(dataPart);

	GPIO_writePin(&lcdControl, GPIO_PIN_SET, GPIO_PIN_10);
	for (i = 0; i < 500; i++);

	GPIO_writePin(&lcdControl, GPIO_PIN_RESET, GPIO_PIN_10);
	for (i = 0; i < 500; i++);


}

void LCD_writeCmd(u8 cmd)
{

	volatile u32 i = 0;
	u8 dataPart = cmd & 0xF0;
	/* RS = 0 */
	GPIO_writePin(&lcdControl, GPIO_PIN_RESET, GPIO_PIN_0);
	LCD_writePort(dataPart);

	GPIO_writePin(&lcdControl, GPIO_PIN_SET, GPIO_PIN_10);
	for (i = 0; i < 500; i++);

	GPIO_writePin(&lcdControl, GPIO_PIN_RESET, GPIO_PIN_10);
	for (i = 0; i < 500; i++);


	dataPart = (cmd & 0x0F) << 4;

	LCD_writePort(dataPart);

	GPIO_writePin(&lcdControl, GPIO_PIN_SET, GPIO_PIN_10);
	for (i = 0; i < 500; i++);

	GPIO_writePin(&lcdControl, GPIO_PIN_RESET, GPIO_PIN_10);
	for (i = 0; i < 500; i++);

}

void LCD_writeStr(u8* str)
{
	u8 counter = 0;
	for(; str[counter] != '\0'; counter++)
	{
		LCD_writeData(str[counter]);
	}
}

void LCD_writePort(u8 data)
{
	u8 pinVal;

	pinVal = GET_BIT(data, 4);
	GPIO_writePin(&lcdData, pinVal, GPIO_PIN_0);

	pinVal = GET_BIT(data, 5);
	GPIO_writePin(&lcdData, pinVal, GPIO_PIN_1);

	pinVal = GET_BIT(data, 6);
	GPIO_writePin(&lcdData, pinVal, GPIO_PIN_2);

	pinVal = GET_BIT(data, 7);
	GPIO_writePin(&lcdData, pinVal, GPIO_PIN_3);
}
