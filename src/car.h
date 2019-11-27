#ifndef CAR_H
#define CAR_H

#include "initialisation.h"


car* spawnCar(int y, int x, int direction, int nbLin, int nbCol, char tab[nbLin][nbCol]);
void addCar(car* car, int y, int x, int direction, int nbLin, int nbCol, char tab[nbLin][nbCol]);
void loadCarrosserie(car* car, int direction);
void xorArrayCar(car* car, int nbLin, int nbCol, char tab [nbLin][nbCol]);
void setState(car* car, int state);
void setColorCode(car* car);
void changeDirection(car* car, int direction);
void hideCar(car* car);
void displayCar(car* car);

void deleteCarIfNeeded(car **carPP);

int isParked(car* car, int nbLin, int nbCol, char tab[nbLin][nbCol]);

int countPossibleMoves(car* car, int nbLin, int nbCol, char tab[nbLin][nbCol], int direction);
int canTurn(car* car, int nbLin, int nbCol, char tab[nbLin][nbCol], int direction);
int canMove(car* car, int nbLin, int nbCol, char tab[nbLin][nbCol]);
int moveCar(car* car, int nbLin, int nbCol, char tab[nbLin][nbCol]);

void barrierManagement(car* car, int nbLin, int nbCol, char tab[nbLin][nbCol]);
void getTowardsSpot(car* car, int nbLin, int nbCol, char tab[nbLin][nbCol]);
void getTowardsExit (car* car, int nbLin, int nbCol, char tab[nbLin][nbCol]);
void updateGame(car* car, int nbLin, int nbCol, char tab[nbLin][nbCol]);
void colorParkingSpot(car* car, int mode);

#endif
