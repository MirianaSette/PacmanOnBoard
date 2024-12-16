/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_board.c
** Descriptions:        Board management functions
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

 
#include "LPC17xx.h"
#include "pacman.h"

#define ROWS 30
#define COLUMNS 26
#define EC 0					// Empty cell
#define	SP 1					// Cell with standard pill
#define	PP 2					// Cell with power pill
#define	WC 3					// Wall cell
#define TL 4 					// Teleport left 
#define TR 5					// Teleport right 

volatile uint8_t board[ROWS][COLUMNS] = {
	WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC,
	WC, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, WC, WC, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, WC,
	WC, SP, WC, WC, WC, SP, WC, WC, WC, SP, WC, SP, WC, WC, SP, WC, SP, WC, WC, WC, SP, WC, WC, WC, SP, WC,
	WC, SP, WC, WC, WC, SP, WC, WC, WC, SP, WC, SP, WC, WC, SP, WC, SP, WC, WC, WC, SP, WC, WC, WC, SP, WC,
	WC, SP, SP, SP, SP, SP, SP, SP, SP, SP, WC, SP, SP, SP, SP, WC, SP, SP, SP, SP, SP, SP, SP, SP, SP, WC,
	WC, SP, WC, WC, WC, WC, WC, WC, WC, SP, WC, WC, WC, WC, WC, WC, SP, WC, WC, WC, WC, WC, WC, WC, SP, WC,
	WC, SP, WC, WC, WC, WC, WC, WC, WC, SP, WC, WC, WC, WC, WC, WC, SP, WC, WC, WC, WC, WC, WC, WC, SP, WC,
	WC, SP, SP, SP, SP, SP, SP, WC, WC, SP, SP, SP, SP, SP, SP, SP, SP, WC, WC, SP, SP, SP, SP, SP, SP, WC, 
	WC, WC, WC, WC, WC, WC, SP, WC, WC, SP, WC, WC, WC, WC, WC, WC, SP, WC, WC, SP, WC, WC, WC, WC, WC, WC, 
	EC, EC, EC, EC, EC, WC, SP, WC, WC, SP, WC, WC, WC, WC, WC, WC, SP, WC, WC, SP, WC, EC, EC, EC, EC, EC,
	EC, EC, EC, EC, EC, WC, SP, SP, SP, SP, SP, EC, EC, EC, EC, SP, SP, SP, SP, SP, WC, EC, EC, EC, EC, EC,
	EC, EC, EC, EC, EC, WC, SP, WC, WC, WC, SP, WC, WC, WC, WC, SP, WC, WC, WC, SP, WC, EC, EC, EC, EC, EC,
	EC, EC, EC, EC, EC, WC, SP, WC, WC, WC, SP, WC, WC, WC, WC, SP, WC, WC, WC, SP, WC, EC, EC, EC, EC, EC,
	WC, WC, WC, WC, WC, WC, SP, WC, WC, WC, SP, WC, WC, WC, WC, SP, WC, WC, WC, SP, WC, WC, WC, WC, WC, WC, 
	TL, EC, EC, EC, EC, EC, EC, SP, SP, SP, SP, WC, WC, WC, WC, SP, SP, SP, SP, EC, EC, EC, EC, EC, EC, TR, 
	WC, WC, WC, WC, WC, WC, SP, WC, WC, WC, SP, WC, WC, WC, WC, SP, WC, WC, WC, SP, WC, WC, WC, WC, WC, WC, 
	EC, EC, EC, EC, EC, WC, SP, WC, WC, WC, SP, WC, WC, WC, WC, SP, WC, WC, WC, SP, WC, EC, EC, EC, EC, EC,
	EC, EC, EC, EC, EC, WC, SP, WC, WC, WC, SP, WC, WC, WC, WC, SP, WC, WC, WC, SP, WC, EC, EC, EC, EC, EC,
	EC, EC, EC, EC, EC, WC, SP, WC, WC, WC, SP, EC, EC, EC, EC, SP, WC, WC, WC, SP, WC, EC, EC, EC, EC, EC,
	EC, EC, EC, EC, EC, WC, SP, WC, WC, WC, SP, WC, WC, WC, WC, SP, WC, WC, WC, SP, WC, EC, EC, EC, EC, EC,
	WC, WC, WC, WC, WC, WC, SP, WC, WC, WC, SP, WC, WC, WC, WC, SP, WC, WC, WC, SP, WC, WC, WC, WC, WC, WC, 
	WC, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, WC, WC, WC, WC, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, WC, 
	WC, SP, WC, WC, SP, WC, WC, SP, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, SP, WC, WC, SP, WC, WC, SP, WC, 
	WC, SP, WC, WC, SP, WC, WC, SP, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, SP, WC, WC, SP, WC, WC, SP, WC, 
	WC, SP, WC, WC, SP, WC, WC, SP, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, SP, WC, WC, SP, WC, WC, SP, WC, 
	WC, SP, WC, WC, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, WC, WC, SP, WC, 
	WC, SP, WC, WC, WC, WC, WC, WC, SP, WC, WC, WC, WC, WC, WC, WC, WC, SP, WC, WC, WC, WC, WC, WC, SP, WC, 
	WC, SP, WC, WC, WC, WC, WC, WC, SP, WC, WC, WC, WC, WC, WC, WC, WC, SP, WC, WC, WC, WC, WC, WC, SP, WC,
	WC, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, WC, 
	WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC, WC
};




