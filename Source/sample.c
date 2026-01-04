/***************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "timer/timer.h"
#include <time.h>
#include "RIT/RIT.h"


#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

#define SECOND 0x17D7840 //one second with a 25MHz clock
#define FIFTYMS 0x4C4B40 //50ms with a 100MHz clock

#define EMULATOR_SECOND 22
#define GAME_SECOND SECOND / EMULATOR_SECOND  
#define TPS 6 // game ticks per second

int main(void){
	SystemInit();  												/* System Initialization (i.e., PLL)  */
	BUTTON_init();
	joystick_init();
	init_RIT(FIFTYMS / 22); ///* RIT Initialization 50 msec       */
	enable_RIT();	
	init_timer(0, 0xFFFFFFFF); // for seeding PRNG
	init_timer(1, GAME_SECOND / TPS);  // for game advancement 
	NVIC_SetPriority(TIMER1_IRQn, 1);
	enable_timer(0);
	enable_timer(1);
  	LCD_Initialization();
	LCD_Clear(Black);
	field_init();
	GUI_Text(180, 100, (uint8_t*) "swag", Grey, Black); 
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
	while (1){
		__ASM("wfi");
	}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
