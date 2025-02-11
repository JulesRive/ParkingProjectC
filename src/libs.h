#ifndef LIBS_H
#define LIBS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>
#include <ncurses.h>
#include <locale.h>


typedef struct car car;
struct car
{
	int direction; /* ClockWise, 0 = up*/

	int posy;
	int posx;  
	int width;
	int height; 
	int speed;
	char type; /*'v'=> voiture, 'c' => camion, etc.*/
	char carrosserie [4][30]; 
	int color_code;
	int state; /*'1' : Looking for a spot. '2' : Parked.  '3' : Leaving.*/
	unsigned long int time; /*pour stocker le temps passé dans le parking*/
	int timeStopped; /*Will help to decide when to start going reverse*/
	int animationState;//Shows the state of the entering/exiting animation
	int enteringState;
	int backwards;//Will say if the car is going backwards;
	struct car *next; 
	int toDelete;
};

typedef struct Coord Coord;
struct Coord
{
	int y;
	int x;
};

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define NBLIN 48
#define NBCOL 125
#define SPAWNX 81
#define SPAWNY 43
#define TURNLEFT -1
#define TURNSTRAIGHT 0
#define TURNRIGHT 1
#endif





