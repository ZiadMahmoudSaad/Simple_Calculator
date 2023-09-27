/*
 * LCD.c
 *
 *  Created on: Sep 22, 2023
 *      Author: Ziad Mahmoud Saad
 */

#include "LCD.h"
#define READ_BIT(reg, bitNum)           ((reg >> bitNum)& 1U)
void wait_ms(uint32_t time) {
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}

void LCD_clear_screen(void)
{
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN)	;
}

void LCD_kick()
{
	GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_SET) ;
	wait_ms(5);
	GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET) ;

}


void LCD_GPIO_init()
{
	//EN_switch Output
	PINConf.pin_mode = GPIO_MODE_Output_PUSH_PULL ;
	PINConf.pin_number = EN_SWITCH ;
	PINConf.pin_speed = GPIO_SPEED_10MHz ;
	GPIO_Init_ConFig(LCD_CTRL, &PINConf) ;
	//RW_switch Output
	PINConf.pin_mode = GPIO_MODE_Output_PUSH_PULL ;
	PINConf.pin_number = RW_SWITCH ;
	PINConf.pin_speed = GPIO_SPEED_10MHz ;
	GPIO_Init_ConFig(LCD_CTRL, &PINConf) ;
	//RS_switch Output
	PINConf.pin_mode = GPIO_MODE_Output_PUSH_PULL ;
	PINConf.pin_number = RS_SWITCH ;
	PINConf.pin_speed = GPIO_SPEED_10MHz ;
	GPIO_Init_ConFig(LCD_CTRL, &PINConf) ;


	GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET) ;
	GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET) ;
	GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET) ;


	//DATA_PINS are Output
	PINConf.pin_mode = GPIO_MODE_Output_PUSH_PULL ;
	PINConf.pin_number = GPIO_PIN_0 ;
	PINConf.pin_speed = GPIO_SPEED_10MHz ;
	GPIO_Init_ConFig(LCD_PORT, &PINConf) ;

	PINConf.pin_mode = GPIO_MODE_Output_PUSH_PULL ;
	PINConf.pin_number = GPIO_PIN_1 ;
	PINConf.pin_speed = GPIO_SPEED_10MHz ;
	GPIO_Init_ConFig(LCD_PORT, &PINConf) ;

	PINConf.pin_mode = GPIO_MODE_Output_PUSH_PULL ;
	PINConf.pin_number = GPIO_PIN_2 ;
	PINConf.pin_speed = GPIO_SPEED_10MHz ;
	GPIO_Init_ConFig(LCD_PORT, &PINConf) ;

	PINConf.pin_mode = GPIO_MODE_Output_PUSH_PULL ;
	PINConf.pin_number = GPIO_PIN_3 ;
	PINConf.pin_speed = GPIO_SPEED_10MHz ;
	GPIO_Init_ConFig(LCD_PORT, &PINConf) ;


	PINConf.pin_mode = GPIO_MODE_Output_PUSH_PULL ;
	PINConf.pin_number = GPIO_PIN_4 ;
	PINConf.pin_speed = GPIO_SPEED_10MHz ;
	GPIO_Init_ConFig(LCD_PORT, &PINConf) ;

	PINConf.pin_mode = GPIO_MODE_Output_PUSH_PULL ;
	PINConf.pin_number = GPIO_PIN_5 ;
	PINConf.pin_speed = GPIO_SPEED_10MHz ;
	GPIO_Init_ConFig(LCD_PORT, &PINConf) ;

	PINConf.pin_mode = GPIO_MODE_Output_PUSH_PULL ;
	PINConf.pin_number = GPIO_PIN_6 ;
	PINConf.pin_speed = GPIO_SPEED_10MHz ;
	GPIO_Init_ConFig(LCD_PORT, &PINConf) ;

	PINConf.pin_mode = GPIO_MODE_Output_PUSH_PULL ;
	PINConf.pin_number = GPIO_PIN_7 ;
	PINConf.pin_speed = GPIO_SPEED_10MHz ;
	GPIO_Init_ConFig(LCD_PORT, &PINConf) ;
}

void LCD_init()
{
	wait_ms(20);

	LCD_GPIO_init();
	wait_ms(20);
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);

	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	wait_ms(5);
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_WRITE_COMMAND(unsigned char command)
{
	GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);

	GPIO_WritePin(LCD_PORT, GPIO_PIN_0, READ_BIT(command, 0));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_1, READ_BIT(command, 1));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_2, READ_BIT(command, 2));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_3, READ_BIT(command, 3));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_4, READ_BIT(command, 4));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_5, READ_BIT(command, 5));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_6, READ_BIT(command, 6));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_7, READ_BIT(command, 7));

	wait_ms(1);
	LCD_kick();
}

void LCD_WRITE_CHAR(unsigned char character)
{
	GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);

	GPIO_WritePin(LCD_PORT, GPIO_PIN_0, READ_BIT(character, 0));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_1, READ_BIT(character, 1));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_2, READ_BIT(character, 2));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_3, READ_BIT(character, 3));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_4, READ_BIT(character, 4));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_5, READ_BIT(character, 5));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_6, READ_BIT(character, 6));
	GPIO_WritePin(LCD_PORT, GPIO_PIN_7, READ_BIT(character, 7));
	wait_ms(1);
	LCD_kick();


}

void LCD_GOTO_XY(unsigned char line, unsigned char position)
{
	if(line==1 && position>=0 && position<16)
	{
		LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
	}else if(line==2)
	{
		LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
	}
}

void LCD_WRITE_STRING(char* string)
{
	int count=0;
	while(*string!=0)
	{
		count++;
		LCD_WRITE_CHAR(*string++);
		if (count == 16)
		{
			LCD_GOTO_XY(2,0);
		}else if (count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count=0;
		}
	}
}


void LCD_WRITE_NUMBER(int32_t num)
{
	int count=0,count2,max=0,temp,number[16]={0};

	while(num!=0)
	{
		count2 = 0 ;
		temp = num ;

		while(temp >= 10)
		{
			temp = temp/10 ;
			count2++;

		}
		number[count2] = temp ;
		if(max<count2)
			max = count2 ;

		while(count2)
		{
			temp = temp*10;
			count2--;
		}
		num=num-temp;


	}
	for(int i = max; i>=0 ;i--)
	{
		count++;
		LCD_WRITE_CHAR((number[i])+48);
		if (count == 16)
		{
			LCD_GOTO_XY(2,0);
		}else if (count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count=0;
		}
	}
}
