/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "Stm32F103x6.h"
#include "Stm32F103C6_GPIO_Driver.h"
#include "LCD.h"
#include "KEYPAD.h"

void clock_init();
void GPIO_init();

void wait(uint32_t time);

int main(void)
{
	clock_init();
	LCD_init();
	Keypad_init();
	LCD_clear_screen();
	int32_t num1 = 0 , num2 = 0 , sum = 0;
	char pressed='A',oper;
	uint16_t num1_flag = 0 , num2_flag = 0 ,oper_flag = 0;

	//EXTI_GPIO_Init(EXTIPB9, EXTI_Trigger_RISING, EXTI_IRQ_ENABLE, EXTI9_callback);
	//EXTI_flag=1;
    while (1)
    {
    	pressed=Keypad_getkey();
    	switch(pressed)
    	{
    	case 'A':
    		break;
    	case '?':
    		LCD_clear_screen();
    		num1 = 0 ;
    		num2 = 0 ;
    		num1_flag = 0 ;
    		num2_flag = 0 ;
    		oper_flag = 0 ;
    		break;
    	case '+':
    	case '-':
    	case '*':
    	case '/':
    		if(oper_flag==0 && num1_flag==1)
    		{
    			LCD_WRITE_CHAR(pressed);
    			oper_flag = 1;
    			oper = pressed ;
    		}
    		break;
    	case '=':
    		if(oper_flag==1 && num1_flag && num2_flag)
    		{
    			switch(oper)
    			{
    			case '+':
    				sum=num1+num2 ;
    				break;
    			case '-':
    				sum=num1-num2 ;
    				break;
    			case '*':
    				sum=num1*num2 ;
    				break;
    			case '/':
    				sum=num1/num2 ;
    				break;
    			}
    			LCD_WRITE_CHAR('=');
    			LCD_WRITE_NUMBER(sum);
    			num1=sum ;
    			num2 = 0 ;
    			oper_flag = 0 ;
    			num2_flag = 0 ;
    		}
    		break;
		default://numbers
			if(oper_flag==0)//num1
			{
				num1 = ( num1*10 ) + pressed - 48;
				num1_flag = 1 ;
			}
			else//num2
			{
				num2 = ( num2*10 ) + pressed - 48 ;
				num2_flag = 1 ;
			}
			LCD_WRITE_CHAR(pressed) ;
			break;
    	}
    	wait(50);
    }

}

void clock_init()
{
	RCC_GPIOA_CLK_EN() 	;
	RCC_GPIOB_CLK_EN() 	;

}


void wait(uint32_t time)
{
	uint32_t i,j;
	for(i=0;i<time;i++)
		for(j=0;j<255;j++);
}



