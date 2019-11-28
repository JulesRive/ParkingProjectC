#ifndef CAR_H
#define CAR_H

#include "initialisation.h"


car* spawnCar(int y, int x, int direction);
void addCar(car* car, int y, int x, int direction);
void loadCarrosserie(car* car, int direction);
void xorArrayCar(car* car);
void setState(car* car, int state);
void setColorCode(car* car);
void changeDirection(car* car, int direction);
void hideCar(car* car);
void displayCar(car* car);

void deleteCarIfNeeded(car **carPP);

int isParked(car* car);

int countPossibleMoves(car* car, int direction);
int canTurn(car* car, int direction);
int canMove(car* car);
int moveCar(car* car);

void barrierManagement(car* car);
void getTowardsSpot(car* car);
void getTowardsExit (car* car);
void updateGame(car* car);
void colorParkingSpot(car* car, int mode);

#endif
