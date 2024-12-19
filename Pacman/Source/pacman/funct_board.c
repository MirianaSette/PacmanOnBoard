/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_board.c
** Descriptions:        Board management functions
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

 
#include "LPC17xx.h"
#include "pacman.h"
#include "GLCD/GLCD.h" 


#define DIM_CELL 9
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

void draw_wall(int i, int j){
	uint16_t color; 
	
	// UP 
	color = LCD_GetPoint(i*DIM_CELL+5, j*DIM_CELL); 
	if(color == Blue) {
		LCD_DrawLine((i*DIM_CELL), (j*DIM_CELL), ((i*DIM_CELL)+DIM_CELL), ((j*DIM_CELL)),Black);
	} else {
		LCD_DrawLine((i*DIM_CELL), (j*DIM_CELL), ((i*DIM_CELL)+DIM_CELL), ((j*DIM_CELL)),Blue);
	}
	
	// RIGHT 
	color = LCD_GetPoint((i*DIM_CELL)+DIM_CELL, (j*DIM_CELL)+5); 
	if(color == Blue) {
		LCD_DrawLine(((i*DIM_CELL)+DIM_CELL), ((j*DIM_CELL)), ((i*DIM_CELL)+DIM_CELL), ((j*DIM_CELL)+DIM_CELL),Black);
	} else {
		LCD_DrawLine(((i*DIM_CELL)+DIM_CELL), ((j*DIM_CELL)), ((i*DIM_CELL)+DIM_CELL), ((j*DIM_CELL)+DIM_CELL),Blue);
	}
	
	
	// DOWN
	color = LCD_GetPoint((i*DIM_CELL)+5, (j*DIM_CELL)+ DIM_CELL); 
	if(color == Blue){
		LCD_DrawLine((i*DIM_CELL), ((j*DIM_CELL)+DIM_CELL), ((i*DIM_CELL)+DIM_CELL), ((j*DIM_CELL)+DIM_CELL),Black);
	}	else{
		LCD_DrawLine((i*DIM_CELL), ((j*DIM_CELL)+DIM_CELL), ((i*DIM_CELL)+DIM_CELL), ((j*DIM_CELL)+DIM_CELL),Blue);
	}
	
	
	// LEFT 
	color = LCD_GetPoint((i*DIM_CELL), (j*DIM_CELL)+5);
	if(color == Blue){
		LCD_DrawLine((i*DIM_CELL), (j*DIM_CELL), (i*DIM_CELL), ((j*DIM_CELL)+DIM_CELL),Black
		);
	}	else{
		LCD_DrawLine((i*DIM_CELL), (j*DIM_CELL), (i*DIM_CELL), ((j*DIM_CELL)+DIM_CELL),Blue);
	}
}

void drawPill(int x0, int y0, int r, uint16_t color){
	int x, y;
	for (y = -r; y <= r; y++) {
		for (x = -r; x <= r; x++) {
			if (x*x + y*y <= r*r) {
				LCD_SetPoint(x0+x, y0+y, color); 
			}
		}
	}
}

void draw_board(){
	int i, j;
	LCD_Clear(Black);
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLUMNS; j++){
			switch(board[i][j]){
			case SP:
					drawPill((j*DIM_CELL)+5, (i*DIM_CELL)+5, 2, Magenta);
					break;
			case WC:
					draw_wall(j, i);
					break;
			default:
					
					break;
			}
		}
	}
}







