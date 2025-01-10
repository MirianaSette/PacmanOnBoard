/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_board.c
** Descriptions:        Board management functions
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

 
#include "LPC17xx.h"
#include "pacman.h"


#define NEWXR 25
#define NEWXL 0
#define Y 30


int direction = LEFT;
int x = 11;
int y =	12;
int xl = 0;
int pill = 0;
int score = 0;
int nextMile = 1000;
int life = 0;
extern volatile uint8_t board[ROWS][COLUMNS];

void setDirection (int d);
void moveP(void);


void setDirection(int d){
	direction = d;
}

void upscore(){
	if(board[y][x] == SP){
		score += 10;
		board[y][x] = EC;
		pill++;
	}else if(board[y][x] == PP){
		score += 50;
		board[y][x] = EC;
		pill++;
	}
	showScore();
}

void upLife(){
	if (score == nextMile) {
    drawPacman(Y, xl, false);
		life ++;
		xl ++;
    nextMile += 1000; // Aggiorna il prossimo obiettivo
  }
}
	

void moveP(void){
	switch(direction){
		case UP:
			if(y > 0 && board[y-1][x] != WC){
				drawPacman(y, x, true);
				y--;
				drawPacman(y, x, false);
			}
			break;
		case DOWN:
			if(y > 0 && board[y+1][x] != WC){
				drawPacman(y, x, true);
				y++;
				drawPacman(y, x, false);
			}
			break;
		case LEFT:	
			if(x > 0 && board[y][x-1] != WC){
				drawPacman(y, x, true);
				x--;
				drawPacman(y, x, false);
			} else if (board[y][x] == TL){
				drawPacman(y, x, true);
				x = NEWXR;
				drawPacman(y, x, false);
			}
			break;
		case RIGHT:
			if(x >= 0 && board[y][x+1] != WC){
				drawPacman(y, x, true);
				x++;
				drawPacman(y, x, false);
			}else if (board[y][x] == TR){
				drawPacman(y, x, true);
				x = NEWXL;
				drawPacman(y, x, false);
			}
			break;
		default:
			break;
	}
	upscore(); // up score
	upLife();
	showGameOver();
	showVictory();
}