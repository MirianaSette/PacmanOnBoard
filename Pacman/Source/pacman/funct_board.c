/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_board.c
** Descriptions:        Board management functions
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

 

#include "pacman.h"
#include "GLCD/GLCD.h" 
	

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
	
int coord[480];   	// array with standard pills coordinate
int time = 60; 

extern int score; 
extern int pill;


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

void drawPacman(int i, int j, bool clean){
	if (clean) {
		draw((j*DIM_CELL)+5, (i*DIM_CELL)+5 + IN, 3,  Black);
	} else {
		draw((j*DIM_CELL)+5, (i*DIM_CELL)+5 + IN, 3 ,  Yellow);
	}
}

void drawSPill(int i, int j, bool clean){
	if (clean) {
		draw((j*DIM_CELL)+5, (i*DIM_CELL)+5 + IN, 1,  Black);
	} else {
		draw((j*DIM_CELL)+5, (i*DIM_CELL)+5 + IN, 1,  Magenta);
	}
	
}

void drawPPill(int i, int j, bool clean){
	if (clean) {
		draw((j*DIM_CELL)+5, (i*DIM_CELL)+5 + IN, 2,  Black);
	} else {
		draw((j*DIM_CELL)+5, (i*DIM_CELL)+5 + IN, 2,  Magenta);
	}
}

void replacePills(){
	int y, x;
	int i = 0;
	int ncoord;									// n remaining coord
	int r;
	
	for(y = 0; y < ROWS; y++){
		for(x = 0; x < COLUMNS; x++){
			if(board[y][x] == SP){
				coord[i] = y;
				coord[i+1] = x;
				i+=2;
			}
		}
	}
	ncoord = (240 - pill) * 2;
	for(i = 0; i < 6; i++){
		r = rand() % ncoord;
		if(r % 2 == 1){
			x = coord[r];
			y = coord[r-1];
		}else{
			x = coord[r+1];
			y = coord[r];
		}
		drawPPill(y, x, false);
		board[y][x] = PP;
	}
}


void draw_board(){
	int i, j;
	LCD_Clear(Black);
	GUI_Text(40, 2, (uint8_t*)"SCORE", White, Black); // y [2, 18]
	GUI_Text(110, 2, (uint8_t*)"COUNTDOWN", White, Black); 
	GUI_Text(130, 20, (uint8_t*)"60", White, Black); 
	
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLUMNS; j++){
			switch(board[i][j]){
				case SP:
					drawSPill(i, j, false);
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

/*  */ 
void showScore(){
	char s[5]; 
	sprintf(s, "%d", score); 
	GUI_Text(40, 20, (uint8_t *)s, White, Black); 
}

void showTime(){
	char s[2]; 
	sprintf(s, "%d", time); 
	if (time < 10)
		s[1] = s[0]; 
	GUI_Text(130, 20, (uint8_t *)s, White, Black); 
}

void freezeGame(){
	disable_timer(0);
	disable_timer(1);
}


void enable(){
	enable_timer(0);
	enable_timer(1);

}

void showGameOver(){
	if(time == 0){
		freezeGame();
		LCD_Clear(Black);
		GUI_Text(80, 152, (uint8_t *)"GAME OVER", White, Black);
	}
}

void showVictory(){
	if(pill == 240){
		freezeGame();
		LCD_Clear(Black);
		GUI_Text(88, 152, (uint8_t *)"VICTORY", White, Black);
	}
}

void showPause(){
	freezeGame();
	GUI_Text(180, 22, (uint8_t *)"PAUSE", White, Black);
}

void disablePause(){
	GUI_Text(180, 22, (uint8_t *)"PAUSE", Black, Black);
	enable();
}
