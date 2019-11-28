#ifndef MISC_H
#define MISC_H

#include "libs.h"

int inTab(int y, int x);
int vertical(int direction);
int isFree(char c);
int sweepFront(int direction, int x, int y, int state);
void activateBarrier(int openClose, int barrierNb);
void colorBarrier(int greenOrRed, int barrierNb);
void interpretChar(char c);
int bestDirection(int left, int straight, int right);

#endif
