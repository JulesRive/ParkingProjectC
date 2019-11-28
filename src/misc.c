#include "misc.h"
extern char tab[NBLIN][NBCOL];

int inTab(int y, int x) {
	return ((y>=0 && y<NBLIN)&&(x>=0 && x <NBCOL));
}

int vertical(int direction) {//Tells whether or not the car is in a vertical position
	return (direction==UP||direction==DOWN);
}

int isFree(char c) {
	return (c==' ' || c=='.' || (c>'A' && c<'Z') || c==('b'^'b'));//Will return 1 if c is a free space.
}

int sweepFront(int direction, int x, int y, int state) {
// 0 if the front spot isn't free, 1 if it is, 2 if car parked.
// If the car is exiting, will avoid parking spots
	int i=0, width=0, height=0;
	if (vertical(direction)) height=width=4;
	else {
		height=3; width=7;
	}
	switch (direction) {
		case UP:
			if ((tab[y-1][x]=='@' || tab[y-1][x]=='.') && state==3) return 0;
			if (tab[y-1][x]=='@') return 2;
			for (i=0;i<width;i++) {
				if (!isFree(tab[y-1][x+i]))return 0;
			} break;
		case RIGHT: 
			if ((tab[y][x+width]=='@' || tab[y][x+width]=='.') && state==3) return 0;
			if (tab[y][x+width]=='@') return 2;
				for (i=0;i<height;i++) {
					if (!isFree(tab[y+i][x+width]))return 0;
				} break;
		case DOWN:
			if ((tab[y+height][x]=='@' || tab[y+height][x]=='.') && state==3) return 0;
			if (tab[y+height][x]=='@') return 2;
				for (i=0;i<width;i++) {
					if (!isFree(tab[y+height][x+i]))return 0;
				} break;
		case LEFT:
			if ((tab[y][x-1]=='@' || tab[y][x-1]=='.') && state==3) return 0;
			if (tab[y][x-1]=='@') return 2;
				for (i=0;i<height;i++) {
					if (!isFree(tab[y+i][x-1]))return 0;
				} break;	
		default: printw("Direction set as %d : SweepFront Error.\n", direction); return (-1);
	}
	return 1;
}

void interpretChar(char c) {
	switch (c) {
		case '[' : printw("╔"); break;
		case ']' : printw("╗"); break;
		case '-' : printw("═"); break;
		case 't' : printw("╦");	break;
		case '(' : printw("╚");	break;
		case '|' : printw("║");	break;
		case ')' : printw("╝");	break;
		case '{' : printw("╣");	break;
		case '}' : printw("╠");	break;
		case '+' : printw("╬");	break;
		case 'h' : printw("╩"); break;
		case '/' : printw("|");	break;
		case '_' : printw("-");	break;
		case '.' : printw(" ");	break;
		case ' ' : printw(" ");	break;
		case 'b' : attron(COLOR_PAIR(4)); printw("-"); attroff(COLOR_PAIR(4));//Barrier
		break;
		case '@' : attron(COLOR_PAIR(6)); printw(" "); attroff(COLOR_PAIR(6));//Free parking Spot
		break;
		default : printw("%c",c); break;
	}
}

int bestDirection(int left, int straight, int right) {//-1 ==> left; 0 ==> straight; 1 ==> right
	const int ignoreDistanceBeyond=10;
	if ((left==straight)&&(left==right)) return 0;//Not turning if every direction evaluates the same
	
	if ((left>0) || (straight>0) || (right>0)) {
		if ((straight>left) && (straight>right)) return 0;
		if ((left>straight) && (left>right)) return -1;
		if ((right>left) && (right>straight)) return 1;
		
		if (left==straight) {
			if (rand()%2==0) return -1;
			return 0;
		}
		
		if (left==right) {
			if (rand()%2==0) return -1;
			return 1;
		} 
		
		if (straight==right) {
			if (rand()%2==0) return 0;
			return 1;
		}
	}	
	if (-left>ignoreDistanceBeyond && -straight>ignoreDistanceBeyond && -right>ignoreDistanceBeyond) return (rand()%3 -1);
	if (-left>ignoreDistanceBeyond && -straight>ignoreDistanceBeyond) return (rand()%2 -1);
	if (-straight>ignoreDistanceBeyond && -right>ignoreDistanceBeyond) return (rand()%2);
	if (-left>ignoreDistanceBeyond && -right>ignoreDistanceBeyond) return ((rand()%2==0)?-1:1);
	if (-left>ignoreDistanceBeyond) return (-1);
	if (-straight>ignoreDistanceBeyond) return 0;
	if (-right>ignoreDistanceBeyond) return 1;
	return bestDirection(-left,-straight,-right);
}

void activateBarrier(int openClose, int barrierNb) {
	int posy=0,posx=0;int sizeCmpt=0;
	switch (barrierNb) {
		case 1: posy=47; posx=SPAWNX; break;//1st barrier of the entering sas.
		case 2: posy=SPAWNY-1; posx=SPAWNX; break;//2nd barrier of the entering sas
		case 3: posy=5; posx=93; break;//1st barrier of the exit sas
		case 4: posy=0; posx=93; break;//2nd barrier of the exit sas
	}
	for (;sizeCmpt<4;sizeCmpt++) {
		tab[posy][posx+sizeCmpt]^='b';
	}
	colorBarrier(openClose,barrierNb);
}

void colorBarrier(int greenOrRed, int barrierNb) {
	int posy=0,posx=0;int sizeCmpt=0;
	if (greenOrRed==0) attron(COLOR_PAIR(3));
	if (greenOrRed==1) attron(COLOR_PAIR(4));
	switch (barrierNb) {
		case 1: posy=47; posx=SPAWNX; break;//1st barrier of the entering sas.
		case 2: posy=SPAWNY-1; posx=SPAWNX; break;//2nd barrier of the entering sas
		case 3: posy=5; posx=93; break;//1st barrier of the exit sas
		case 4: posy=0; posx=93; break;//2nd barrier of the exit sas
	}
	for (;sizeCmpt<4;sizeCmpt++) {
		mvprintw(posy,posx+sizeCmpt,"-");
	}
	attron(COLOR_PAIR(1));
}






