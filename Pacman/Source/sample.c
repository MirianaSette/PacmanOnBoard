/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: 
 *		to control led11 and led 10 through EINT buttons (similarly to project 03_)
 *		to control leds9 to led4 by the timer handler (1 second - circular cycling)
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 15/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/

                  
#include <stdio.h>
#include "LPC17xx.h"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "GLCD/GLCD.h" 
#include "pacman/pacman.h"

int rTime;


#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  init_RIT(0x2DC6C0);									/* RIT Initialization 30 msec       */
	enable_RIT();													/* enable RIT to count 30ms				 */
  BUTTON_init();												/* BUTTON Initialization              */
	joystick_init(); 
	LCD_Initialization(); 
	
	draw_board();
	
	
	LPC_SC -> PCONP |= (1 << 22);  // TURN ON TIMER 2
	LPC_SC -> PCONP |= (1 << 23);  // TURN ON TIMER 3	
	
	// your code here 
	// TIMERS AND RIT SHOULD BE INIT AND ENABLE
	init_timer(0, 0, 0, 3, 0x7A120);			// 15 ms 0x7A120
	enable_timer(0);
	
	init_timer(1, 0, 0, 3, 0x17D7840);
	enable_timer(1);
	
	srand(LPC_TIM0->TC ^ LPC_TIM1->TC);
	rTime = rand()%61;
	
	showPause();
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}
