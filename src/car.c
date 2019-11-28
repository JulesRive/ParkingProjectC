#include "car.h"

int carNumber=0;
int maxCarNumber=0;
int spawnRate=15;
extern char tab[NBLIN][NBCOL];

void changeDirection(car* car, int direction);
void setColorCode();
car* spawnCar(int y, int x, int direction) {
// Creates and returns a new car
	
	activateBarrier(0,1);
	car* car=malloc(sizeof(struct car));
	changeDirection(car,direction);
	car->animationState=10;
	setColorCode(car);
	setState(car, 1);
	car->time=0;
	car->posx=x;
	car->posy=y;
	car->backwards=0;
	car->timeStopped=0;
	car->enteringState=-5;
	loadCarrosserie(car, 0);
	xorArrayCar(car);
	car->next=0;
	car->toDelete=0;
	carNumber++;
	return car;
}

void addCar(car* car, int y, int x, int direction) {
	
	if (car->next!=0) {
		addCar(car->next,y,x,direction); 
		return;
	}
	car->next=spawnCar(y,x,direction);
}

void deleteCarIfNeeded(car **carPP)
{
		if ((*carPP)->toDelete) {
			struct car *fille = (*carPP)->next;
			 free(*carPP);
			 carNumber--;
			 *carPP=fille;
		}
}

void hideCar(car* car) {
	int i=0, j=0;
	for (i=0;i<car->height;i++) {
		for (j=0;j<car->width;j++) {
			if (inTab(car->posy+i+car->animationState, car->posx)) {
				mvprintw(car->posy+i+car->animationState,car->posx+j," ");// Hides the car
			}
		}
	}
}

void xorArrayCar(car* car) {
// Acutalizes the car's position on the map
	int i=0,j=0;
	for (;i<car->height;i++) {
		for (j=0;j<car->width;j++) {
			tab[car->posy+i][car->posx+j]^=0xAA;
		}
	}
}

void setColorCode (car* car) {
	car->color_code=rand()%5+1;
}

void setState(car* car, int state) {
	car->state=state;
}

void loadCarrosserie(car* car, int direction) {
// Loads an array that will be used to display the car from textFiles
	if (direction==4) return;
	char c; int i=0;
	FILE* file;
	switch(direction) {
		case UP : file = fopen("txt/CarUp.txt", "r");
		 if (file==NULL) {
		 	printf("carUp.txt Error...\n");
		 	exit(-1);
		 }
		 break;
		case RIGHT : file = fopen("txt/CarRight.txt", "r"); 
		if (file==NULL) {
		 	printf("carRight.txt Error...\n");
		 	exit(-1);
		 }break;
		case DOWN : file = fopen("txt/CarDown.txt", "r"); 
		if (file==NULL) {
		 	printf("carDown.txt Error...\n");
		 	exit(-1);
		 }break;
		case LEFT : file = fopen("txt/CarLeft.txt", "r"); 
		if (file==NULL) {
		 	printf("carLeft.txt Error...\n");
		 	exit(-1);
		 }break;
	}
	while((c=fgetc(file)) !=EOF)
	{
		if (c!='\n') {
			car->carrosserie[direction][i]=c;
			i++;
		}
	}
	fclose(file);
	loadCarrosserie(car, direction+1);
}


int canMove(car* car) {
// Returns true if the car can move 1 step in it's current direction
	return (sweepFront(car->direction, car->posx, car->posy, car->state)==1);
}

int isParked(car* car) {
// Returns 1 if the car is on a parking spot
	return (sweepFront(car->direction, car->posx, car->posy, car->state)==2);
}

void changeDirection(car* car, int direction) {
	switch (car->direction) {
		case UP: if (direction==LEFT) car->posx-=3; 
		break;
		case RIGHT: if (direction==UP) {
			car->posx+=3;
			car->posy--;
		} if (direction==DOWN) car->posx+=3; 
		break;
		case DOWN: if (direction==RIGHT) car->posy++; 
			if (direction==LEFT) {
				car->posy++;
				car->posx-=3;
			}
		break;
		case LEFT: if (direction==UP) car->posy--;
		break;	
	}
	car->direction=direction;
	if (vertical(direction))	car-> width=car->height=4; 
	else {
		car->width=7; car->height=3;
	}
}

int moveCar(car* car) {
	if (canMove(car)) {
		switch (car->direction) {
			case UP : car->posy--; break;
			case RIGHT : car->posx++; break;
			case DOWN : car->posy++; break;
			case LEFT : car->posx--; break;
			default : printw("moveCar Error.\n"); exit(-1); break;
		}
		return 1;
	}
	return 0;
}

int canTurn(car* car, int direction) {
// Returns true if the car can turn in the direction 'direction'
	int i=0,j=0;
	switch(car->direction) {
		case UP:
			if (direction==LEFT) {// Going up and turning left
				for (i=0;i<3;i++) {
					for (j=0;j<3;j++) {
						if (!isFree(tab[car->posy+i][car->posx-j-1])) return 0;
					}
				}
			}
			if (direction==RIGHT) {// Going up and turning right
				for (i=0;i<3;i++) {
					for (j=0;j<3;j++) {
						if (!isFree(tab[car->posy+i][car->posx+4+j])) return 0;
					}
				}			
			}
		break;
		
		case RIGHT:
			if (direction==UP) {// Going right and turning up
				for (i=0;i<4;i++) {
					if (!isFree(tab[car->posy-1][car->posx+3+i])) return 0;
				}
			}
			if (direction==DOWN) {// Going right and turning down
				for (i=0;i<4;i++) {
					if (!isFree(tab[car->posy+3][car->posx+3+i])) return 0;
				}			
			}
		break;
		
		case DOWN:
			if (direction==LEFT) {// Going down and turning left
				for (i=0;i<3;i++) {
					for (j=0;j<3;j++) {
						if (!isFree(tab[car->posy+1+i][car->posx-j-1])) return 0;
					}
				}
			}
			if (direction==RIGHT) {// Going down and turning right
				for (i=0;i<3;i++) {
					for (j=0;j<3;j++) {
						if (!isFree(tab[car->posy+1+i][car->posx+4+j])) return 0;
					}
				}			
			}
		break;
		
		case LEFT:
			if (direction==UP) {// Going left and turning up
				for (i=0;i<4;i++) {
						if (!isFree(tab[car->posy-1][car->posx+i])) return 0;
				}
			}
			if (direction==DOWN) {// Going left and turning down
				for (i=0;i<4;i++) {
					if (!isFree(tab[car->posy+3][car->posx+i])) return 0;
				}			
			}
		break;	
	}
	return 1;
}

int countPossibleMoves(car* car, int direction) {
// Counts the number of straight moves possible after a turn. Will be positive if there is a parking spot,
// negative therwise
	if (canTurn(car, direction)==1) {
		int i=0, x=car->posx, y=car->posy;
		int saveDirection=car->direction;
		changeDirection(car,direction);
		while (sweepFront(direction, car->posx, car->posy, car->state)==1) {
			switch (direction) {
				case UP: car->posy--; break;
				case RIGHT: car->posx++; break;
				case DOWN: car->posy++; break;
				case LEFT: car->posx--; break;
				
				default: printw("counting moves Error\n"); exit(-1);
			} 
			i++;
		}
		int result=sweepFront(direction, car->posx, car->posy, car->state);
		changeDirection(car,saveDirection);
		car->posx=x; car->posy=y;
		if (result==2) return i;
		return -i;
	} return 0;
}

void getTowardsSpot(car* car) {
// This code will make the car go towards a Parking Spot
	
	int countStraight=0,countLeft=0,countRight=0;
	hideCar(car);
	xorArrayCar(car);
	if (car->timeStopped>=10) {
		car->backwards=1;
		changeDirection(car, (car->direction+2)%4);
		car->timeStopped=0;
	}
	countStraight=countPossibleMoves(car,car->direction);
	countLeft=countPossibleMoves(car,(car->direction+3)%4);
	countRight=countPossibleMoves(car,(car->direction+1)%4);		
	int chanceOfTurning= (car->time>200)?1:(car->time>150)?2:(car->time>100)?3:4;
		
		if (rand()%chanceOfTurning==0) {
			int turningDirection=(bestDirection(countLeft,countStraight,countRight)+4)%4;
			if (canTurn(car, (car->direction + turningDirection+4)%4)) {
				if (car->backwards && turningDirection!=0) car->backwards=0;
				changeDirection(car, (car->direction + turningDirection+4)%4);
			}		
		} 
	
	if (moveCar(car)==0) car->timeStopped++;
	xorArrayCar(car);
	displayCar(car);
	
}

void getTowardsExit (car* car) {
// This code will make the car go towards the exit
	hideCar(car);
	xorArrayCar(car);
	if (car->timeStopped>=10) {
		car->backwards=1;
		changeDirection(car, (car->direction+2)%4);
		car->timeStopped=0;
	} else if (car->posx<93) {
		if (canTurn(car, RIGHT)) {
			changeDirection(car, RIGHT); 
			if (car->backwards) car->backwards=0;
		} else if (canTurn(car, UP)) {
			changeDirection(car, UP); 
			if (car->backwards) car->backwards=0;
		} else if (canTurn(car, DOWN)) {
			changeDirection(car, DOWN); 
			if (car->backwards) car->backwards=0;
		}
	}
	else if (car->posx>93) {
		if (canTurn(car, LEFT)) {
			changeDirection(car, LEFT); 
			if (car->backwards) car->backwards=0;
		} else if (canTurn(car, UP)) {
				changeDirection(car, UP); 
				if (car->backwards) car->backwards=0;
			}
	}
	else if (car->posx==93 && canTurn(car, UP)) {
		changeDirection(car, UP); 
		if (car->backwards) car->backwards=0;
	}
	else {
		
	}
	if (moveCar(car)==0) car->timeStopped++;
	xorArrayCar(car);
	displayCar(car);
	
	
}

void barrierManagement(car* car) {
// Activates barriers according to the current car's differents entering/exiting states

	if (car->animationState>0) {	
		displayCar(car);
		if (car->animationState==0) {
			displayCar(car);
			car->enteringState=10;
			colorBarrier(0,1);	
		}
	}
	if (car->enteringState==7) {
		activateBarrier(1,1);	
		activateBarrier(0,2);
	}
	if (car->enteringState>0) {
		if (--car->enteringState==0) {
			activateBarrier(1, 2);
		}
	}
	if (car->state == 3 && car->animationState==0) {
		if (car->posx==93 && car->posy==6) {
			activateBarrier(0,3);
		}
		if (car->posx==93 && car->posy==1) {
			car->animationState=1;
			colorBarrier(0,4);
			activateBarrier(1,3);
		}
	}
	if (car->state==3 && car->animationState>=5) {
			xorArrayCar(car);
			car->toDelete=1;
			colorBarrier(1,4);
	}
}

void updateGame(car* car) {
// This function will go through the car linkedList and update each car's position/state and display 
// it on the board, will also handle spawning/deleting and barriers activation.
	car->time++;
	if (isParked(car)&&(car->state==1)) {
		setState(car,2);
		colorParkingSpot(car, 1);
	}
	if (car->next==0 && rand()%spawnRate==0 && car->posy!=SPAWNY && car->enteringState==0 && carNumber<maxCarNumber) {
	// Tests for adding a new car
		addCar(car,SPAWNY,SPAWNX,UP);
	}
	/*if (car->state==2 && rand()%40==0) {
	// Exiting the parking spot
		car->backwards=1;
		car->state=3;
		colorParkingSpot(car, 0);
		changeDirection(car, (car->direction+2)%4);
	}*/

// Moving towards the exit =============================================================================
	
	if (car->state==3 && car->animationState==0 ) {
		getTowardsExit(car);
	}
	
// Moving towards a spot  =============================================================================
	
	if (car->state==1 && car->animationState==0) {
		getTowardsSpot(car);
	}
	
// Barrier management =================================================================================
	
	if (car->state!=2) {	
		barrierManagement(car);		
	}
		
// Recursion ==========================================================================================

	if (car->next!=0) {
		updateGame(car->next);
		deleteCarIfNeeded(&car->next);
	}  
}

void displayCar(car* car) {
	int i=0, j=0;
	attron(COLOR_PAIR(car->color_code));
	if (car->state==1) {
		if (car->animationState%2==0) {	
			for (i=0;i<car->height;i++) {
				move(car->posy+i+(car->animationState/2),car->posx);
				for (j=0;j<car->width;j++) { 
					if (inTab(car->posy+i+(car->animationState/2), car->posx)) {
						if (car->backwards) {
							interpretChar(car->carrosserie[(car->direction+2)%4][i*(car->width)+j]);
						} else interpretChar(car->carrosserie[car->direction][i*(car->width)+j]);
					}
				}
			}
		}
	} 
	if (car->state==3) {
		for (i=0;i<car->height;i++) {
			//if (inTab(car->posy+i-car->animationState, car->posx)) {
			move(car->posy+i,car->posx);
			int carLin=i+car->animationState;
				for (j=0;j<car->width;j++) {
					if (carLin>=4) {
						printw(" ");
					} else if (car->backwards) {
						interpretChar(car->carrosserie[(car->direction+2)%4][carLin*(car->width)+j]);
					} else interpretChar(car->carrosserie[car->direction][carLin*(car->width)+j]);
				}
			//}
		}
	}
	
	attroff(COLOR_PAIR(car->color_code));
	if (car->animationState>0 && car->state==1) car->animationState--;
	if (car->animationState>0 && car->state==3) car->animationState++;
}

void colorParkingSpot(car* car, int mode) {
	int i, spotSize;
	if (mode==0) attron(COLOR_PAIR(6));
	if (mode==1) attron(COLOR_PAIR(7));
	if (vertical(car->direction)) spotSize=4;
	else spotSize=3;
	for (i=0;i<spotSize;i++) {
		switch (car->direction) {
			case 0: 
				mvprintw(car->posy-1,car->posx+i," ");
			break;
			case 1:
				mvprintw(car->posy+i,car->posx+car->width," ");
			break;
			case 2: 
				mvprintw(car->posy+car->height,car->posx+i," ");
			break;
			case 3: 
				mvprintw(car->posy+i,car->posx-1," ");
			break;
		}
	}
	attron(COLOR_PAIR(1));
}

