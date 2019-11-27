#ifndef MISC_H
#define MISC_H

#include "libs.h"

int inTab(int y, int x);
int vertical(int direction);
int isFree(char c);
int sweepFront(int direction, int x, int y, int nbLin, int nbCol, char tab[nbLin][nbCol], int state);
void activateBarrier(int nbLin, int nbCol, char tab[nbLin][nbCol], int openClose, int barrierNb);
void colorBarrier(int nbLin,int nbCol,char tab[nbLin][nbCol],int greenOrRed0, int barrierNb);
void interpretChar(char c);
int bestDirection(int left, int straight, int right);

#endif
