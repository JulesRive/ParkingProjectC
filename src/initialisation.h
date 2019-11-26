#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "menu.h"

int click_souris();
void ncurses_initialiser();
void ncurses_couleurs();
void ncurses_souris();
void displayTab(int nbLin, int nbCol, char tab[nbLin][nbCol]);
void loadMap(FILE* file, int nbLin, int nbCol, char tab[nbLin][nbCol]);
char key_pressed();
void initialize();
void launch();
void run(int nbLin, int nbCol, char tab[nbLin][nbCol], int mode);

#endif
