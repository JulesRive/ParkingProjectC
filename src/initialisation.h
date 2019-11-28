#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "menu.h"

int click_souris();
void ncurses_initialiser();
void ncurses_couleurs();
void ncurses_souris();
void displayTab();
void loadMap(FILE* file);
char key_pressed();
void initialize();
void launch();
void run(int mode);

#endif
