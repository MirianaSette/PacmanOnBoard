/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_board.c
** Descriptions:        Board management functions
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

 
#include "LPC17xx.h"
#include "pacman.h"
#include "GLCD/GLCD.h" 
#include <stdbool.h>

#define DIM_CELL 9
#define ROWS 30
#define COLUMNS 26
#define IN 40
#define EC 0					// Empty cell
#define	SP 1					// Cell with standard pill
#define	PP 2					// Cell with power pill
#define	WC 3					// Wall cell
#define TL 4 					// Teleport left 
#define TR 5					// Teleport right 
#define PC 6

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
	EC, EC, EC, EC, EC, WC, SP, SP, SP, SP, SP, PC, EC, EC, EC, SP, SP, SP, SP, SP, WC, EC, EC, EC, EC, EC,
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

void draw_wall(int i, int j){ 
	
	// UP 
	if(i > 0 && board[i-1][j] == WC ){
		LCD_DrawLine((j*DIM_CELL),(i*DIM_CELL)+ IN, ((j*DIM_CELL)+DIM_CELL), (i*DIM_CELL) + IN, Black);
	} else {
		LCD_DrawLine((j*DIM_CELL),(i*DIM_CELL) + IN, ((j*DIM_CELL)+DIM_CELL), (i*DIM_CELL) + IN, Blue);
	}
	
	// RIGHT 
	LCD_DrawLine(((j*DIM_CELL)+DIM_CELL), ((i*DIM_CELL)+ IN), ((j*DIM_CELL)+DIM_CELL), ((i*DIM_CELL)+DIM_CELL)+ IN, Blue);
	
	
	// DOWN
	LCD_DrawLine((j*DIM_CELL), ((i*DIM_CELL)+DIM_CELL)+ IN, ((j*DIM_CELL)+DIM_CELL), ((i*DIM_CELL)+DIM_CELL)+ IN, Blue);
	
	
	// LEFT 
	if(j > 0 && board[i][j-1] == WC){
		LCD_DrawLine((j*DIM_CELL), (i*DIM_CELL)+ IN, (j*DIM_CELL), ((i*DIM_CELL)+DIM_CELL)+ IN, Black);
	}	else{
		LCD_DrawLine((j*DIM_CELL), (i*DIM_CELL)+ IN, (j*DIM_CELL), ((i*DIM_CELL)+DIM_CELL)+ IN, Blue);
	}
}

static void draw(int x0, int y0, int r, uint16_t color){
	int x, y;
	for (y = -r; y <= r; y++) {
		for (x = -r; x <= r; x++) {
			if (x*x + y*y <= r*r) {
				LCD_SetPoint(x0+x, y0+y, color); 
			}
		}
	}
}

void drawPacman(int i, int j, bool clean) {
	if (clean) {
		draw((j*DIM_CELL)+5, (i*DIM_CELL)+5 + IN, 4,  Black);
	} else {
		draw((j*DIM_CELL)+5, (i*DIM_CELL)+5 + IN, 4 ,  Yellow);
	}
}

void drawSPill(int i, int j, bool clean) {
	if (clean) {
		draw((j*DIM_CELL)+5, (i*DIM_CELL)+5 + IN, 1,  Black);
	} else {
		draw((j*DIM_CELL)+5, (i*DIM_CELL)+5 + IN, 1,  Magenta);
	}
	
}

void drawPPill(int i, int j, bool clean) {
	if (clean) {
		draw((j*DIM_CELL)+5, (i*DIM_CELL)+5 + IN, 2,  Black);
	} else {
		draw((j*DIM_CELL)+5, (i*DIM_CELL)+5 + IN, 2,  Magenta);
	}
}

void draw_board(){
	int i, j;
	LCD_Clear(Black);
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLUMNS; j++){
			switch(board[i][j]){
				case SP:
					drawSPill(i, j, false);
					break;
				case PC:
					drawPacman(i, j, false);
					break;
				case WC:
					draw_wall(i, j);
					break;
				default:
					break;
			}
		}
	}
}







