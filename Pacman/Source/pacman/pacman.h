																		 /*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           pacman.h
** Descriptions:        Prototypes of functions included in funct_board.c file
** Correlated files:    funct_board.c, ..
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include <stdio.h>
#include "LPC17xx.h"
#include <stdbool.h>
#include "timer/timer.h"
#include "RIT/RIT.h"

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

#define UP		1
#define DOWN	2
#define LEFT	3
#define RIGHT 4
#define DIM_CELL 9

void draw_wall(int, int);
void drawPacman(int, int, bool);
void drawSPill(int, int, bool);
void drawPPill(int, int, bool);
void draw_board();
void showScore();
void showTime();
void showGameOver();
void showVictory();
void showPause();
void disablePause();
void moveP();