#include "initialisation.h"
#include "car.h"

int L,C;
extern int maxCarNumber;
extern int carNumber;
extern int spawnRate;
char tab[NBLIN][NBCOL];

/**Pour récupérer les coordonnées (x,y) du clic de la souris**/
int click_souris()
{
  MEVENT event ;
  int ch;
  while((ch = getch()) != KEY_F(1)) {
    switch(ch) {
      case KEY_F(2): /*Pour quitter la boucle*/
				return 1;
      case KEY_MOUSE:
        if(getmouse(&event) == OK) {
					C = event.x;
					L = event.y;
					if(event.bstate & BUTTON1_CLICKED) return 0;
				}
    }
  }
  return 0;
}

//**Initialisation de ncurses**/
void ncurses_initialiser() {
  initscr();	        /* Démarre le mode ncurses */
  cbreak();	        /* Pour les saisies clavier (desac. mise en buffer) */
  noecho();             /* Désactive l'affichage des caractères saisis */
  keypad(stdscr, TRUE);	/* Active les touches spécifiques */
  refresh();            /* Met a jour l'affichage */
  curs_set(FALSE);      /* Masque le curseur */
}


/**Initialisation des couleurs**/
void ncurses_couleurs() {
  /* Vérification du support de la couleur */
  if(has_colors() == FALSE) {
    endwin();
    fprintf(stderr, "Le terminal ne supporte pas les couleurs.\n");
    exit(EXIT_FAILURE);
  }

  /* Activation des couleurs */
  start_color();
  //init_color(COLOR_BLACK, 1000, 1000, 1000);
  init_pair(1, COLOR_WHITE, COLOR_BLACK);//Classic
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);//Yellow
  init_pair(3, COLOR_GREEN, COLOR_BLACK);//Green
  init_pair(4, COLOR_RED, COLOR_BLACK);//Red
  init_pair(5, COLOR_CYAN, COLOR_BLACK);//Cyan
  init_pair(6, COLOR_GREEN, COLOR_GREEN);//Green parking spot
  init_pair(7, COLOR_RED, COLOR_RED);//Red parking spot
  clear();

}

/**Initialisation de la souris**/
void ncurses_souris() {
  if(!mousemask(ALL_MOUSE_EVENTS, NULL)) {
    endwin();
    fprintf(stderr, "Erreur lors de l'initialisation de la souris.\n");
    exit(EXIT_FAILURE);
  }

  if(has_mouse() != TRUE) {
    endwin();
    fprintf(stderr, "Aucune souris n'est détectée.\n");
    exit(EXIT_FAILURE);
  }
}

void loadMap(FILE *f) {
	char c; int i=0; int j=0;
	
	while((c=fgetc(f)) !=EOF)
	{
		tab[i][j]=c;
		j++;
		if (j==NBCOL) {
			j=0;
			i++;
		}
	}
}



void displayTab() 
{	
	int i=0; int j=0;
	
	for(i=0;i<NBLIN;i++) {
		for(j=0;j<NBCOL;j++) {
			interpretChar(tab[i][j]);
		}
		usleep(7500);
		refresh();
	}
	mvaddstr(3,NBCOL+5,"  ┌────────────────┐\n");  
	mvaddstr(4,NBCOL+5,"  │  q : Quit      │\n");
  mvaddstr(5,NBCOL+5,"  └────────────────┘\n");
  mvaddstr(7,NBCOL+5,"  ┌────────────────┐\n");   
	mvaddstr(8,NBCOL+5,"  │ s : Slow down  │\n");
  mvaddstr(9,NBCOL+5,"  └────────────────┘\n");
  mvaddstr(11,NBCOL+5,"  ┌────────────────┐\n");
	mvaddstr(12,NBCOL+5,"  │ f : Faster     │\n");
  mvaddstr(13,NBCOL+5,"  └────────────────┘\n");
  mvaddstr(15,NBCOL+5,"  ┌────────────────┐\n");
	mvaddstr(16,NBCOL+5,"  │ p : Pause      │\n");
  mvaddstr(17,NBCOL+5,"  └────────────────┘\n");
  mvaddstr(19,NBCOL+5,"  ┌────────────────┐\n");
	mvaddstr(20,NBCOL+5,"  │ r : Resume     │\n");
  mvaddstr(21,NBCOL+5,"  └────────────────┘\n");
  mvaddstr(23,NBCOL+5,"  ┌──────────────────────┐\n");
	mvprintw(24,NBCOL+5,"  │ Cars in game : %3d   │\n", carNumber);
  mvaddstr(25,NBCOL+5,"  └──────────────────────┘\n");
  mvaddstr(27,NBCOL+5,"  ┌───────────────────────────┐\n");
	mvprintw(28,NBCOL+5,"  │ Max Number of Cars : %3d  │\n", maxCarNumber);
	mvprintw(29,NBCOL+5,"  │      (+/-) to modify      │\n");
  mvaddstr(30,NBCOL+5,"  └───────────────────────────┘\n");
  mvaddstr(32,NBCOL+5,"  ┌──────────────────────┐\n");
	mvprintw(33,NBCOL+5,"  │ Spawn rate : 1/%3d   │\n", spawnRate);
	mvprintw(34,NBCOL+5,"  │    (</>) to modify   │\n");
  mvaddstr(35,NBCOL+5,"  └──────────────────────┘\n");
}

char key_pressed()
{
	struct termios oldterm, newterm;
	int oldfd; char c, result = 0; 
	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm); 
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar(); 
	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm); 
	fcntl( STDIN_FILENO, F_SETFL, oldfd);
	if(c != EOF)
	{
		ungetc(c ,stdin);
		result = getchar();
	}
	return result;
}

void initialize() {
	srand(time(NULL));
	initscr();
	ncurses_initialiser();
	ncurses_couleurs();
	ncurses_souris();
}

void run( int mode) {
//Game loop, handles buttons
	if (mode=='q') return;
	if (mode==1) maxCarNumber=66;
	if (mode==2) maxCarNumber=110;
	char c, pauseC;
	int i=0, pauseCmpt=0, gameSleep=20;
	clear();
	displayTab(tab);
	refresh(); usleep(500000);
	car* car=spawnCar(SPAWNY, SPAWNX, UP, tab);
	refresh(); usleep(500000);
	while (car) {
		updateGame(car,tab);
		deleteCarIfNeeded(&car);
		mvprintw(24,NBCOL+24,"%3d", carNumber);
		mvprintw(28,NBCOL+30,"%3d", maxCarNumber);
		mvprintw(33,NBCOL+24,"%3d", spawnRate);
		refresh();
		for (i=0;i<gameSleep;i++) {// Handles buttons
			usleep(1000);
			c=key_pressed();
			if (c=='f' && gameSleep>5) gameSleep--;
			if (c=='s' && gameSleep<100) gameSleep++;
			if (c=='q') return;
			if (c=='+'&& maxCarNumber<150) maxCarNumber++;
			if (c=='-'&& maxCarNumber>1) maxCarNumber--;
			if (c=='>'&& spawnRate>1) spawnRate--;
			if (c=='<'&& spawnRate<200) spawnRate++;
			if (c=='p') {
				int flagPause=1;
				while (flagPause) {// Looping so we can use options while on pause
					for (pauseCmpt=0;pauseCmpt<10;pauseCmpt++) {
						usleep(1000);
						pauseC=key_pressed();
						if (pauseC=='f' && gameSleep>5) gameSleep--;
						if (pauseC=='s' && gameSleep<100) gameSleep++;
						if (pauseC=='q') return;
						if (pauseC=='+'&& maxCarNumber<150) {
							maxCarNumber++;
							mvprintw(28,NBCOL+30,"%3d", maxCarNumber); 
							refresh();
						}
						if (pauseC=='-'&& maxCarNumber>1) {
							maxCarNumber--;
							mvprintw(28,NBCOL+30,"%3d", maxCarNumber); 
							refresh();
						}
						if (pauseC=='>'&& spawnRate>1) {
							spawnRate--;
							mvprintw(33,NBCOL+24,"%3d", spawnRate);
							refresh();
						}
						if (pauseC=='<'&& spawnRate<200) {
							spawnRate++;
							mvprintw(33,NBCOL+24,"%3d", spawnRate);
							refresh();
						}
						if (pauseC=='r') {
							flagPause=0; 
							break;
						}
					}
				}
			}
		}
	}
}

void launch() {
	setlocale(LC_ALL, "");
	;
	FILE* file = fopen("./txt/map.txt", "r");
	if(file == NULL){
	printf("Can't open the map.txt file\n");
	} 	
	loadMap(file);
	fseek(file, 0, SEEK_SET);
	fclose(file);
	initialize();
	run(menu());
	
	endwin();
}





