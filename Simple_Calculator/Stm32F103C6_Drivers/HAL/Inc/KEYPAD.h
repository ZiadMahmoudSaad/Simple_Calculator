/*
 * KEYPAD.h
 *
 *  Created on: Sep 22, 2023
 *      Author: Ziad Mahmoud Saad
 */

#ifndef KEYPAD_DRIVER_KEYPAD_H_
#define KEYPAD_DRIVER_KEYPAD_H_

#include "Stm32F103x6.h"
#include "Stm32F103C6_GPIO_Driver.h"

#define KEYPAD_PORT	GPIOB


#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4
#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8

GPIO_PIN_Config PINConf ;

void Keypad_init(void);
char Keypad_getkey(void);

#endif /* KEYPAD_DRIVER_KEYPAD_H_ */
