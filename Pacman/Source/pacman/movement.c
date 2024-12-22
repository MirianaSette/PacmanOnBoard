/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_board.c
** Descriptions:        Board management functions
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

 
#include "LPC17xx.h"
#include "pacman.h"
#include <stdbool.h>

int direction = LEFT;
int x = 11;
int y =	12;

void setDirection (int d);
void moveP (int x, int y);


void setDirection(int d){
	direction = d;
}

void moveP(int x, int y){
	switch(direction){
				case UP:
					draw_pacman(y, x, true);
					y--;
					draw_pacman(y, x, false);
					break;
				case DOWN:
					draw_pacman(y, x, true);
					y++;
					draw_pacman(y, x, false);
					break;
				case LEFT:
					draw_pacman(y, x, true);
					x--;
					draw_pacman(y, x, false);
					break;
				case RIGHT:
					draw_pacman(y, x, true);
					x++;
					draw_pacman(y, x, false);
					break;
				default:
					break;
			}
	
	
}