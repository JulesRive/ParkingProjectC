#include "initialisation.h"
#include "car.h"

int L,C;

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

void loadMap(FILE *f, int nbLin, int nbCol, char tab[nbLin][nbCol]) {
	char c; int i=0; int j=0;
	
	while((c=fgetc(f)) !=EOF)
	{
		tab[i][j]=c;
		j++;
		if (j==nbCol) {
			j=0;
			i++;
		}
	}
}



void displayTab(int nbLin, int nbCol, char tab[nbLin][nbCol]) 
{	
	int i=0; int j=0;
	for(i=0;i<nbLin;i++) {
		for(j=0;j<nbCol;j++) {
			interpretChar(tab[i][j]);
		}
		usleep(7500);
		refresh();
	}
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

void run(int nbLin, int nbCol, char tab[nbLin][nbCol], int mode) {
	char c;
	int i=0; int gameSleep=20;
	clear();
	displayTab(nbLin,nbCol,tab);
	refresh(); usleep(500000);
	car* car=spawnCar(SPAWNY, SPAWNX, UP, nbLin, nbCol, tab);
	refresh(); usleep(500000);
	while (car) {
		updateCar(car, nbLin, nbCol, tab);
		if (car->toDelete) {
			struct car *fille = car->next;
			 free(car);
			 car=fille;
		}

		refresh();
		for (i=0;i<gameSleep;i++) {
			usleep(1000);
			c=key_pressed();
			if (c=='f' && gameSleep>5) gameSleep--;
			if (c=='s' && gameSleep<50) gameSleep++;
		}
	}
}

void launch() {
	setlocale(LC_ALL, "");
	char tab[NBLIN][NBCOL];
	FILE* file = fopen("./txt/map.txt", "r");
	if(file == NULL){
	printf("Can't open the map.txt file\n");
	} 	
	loadMap(file,NBLIN,NBCOL,tab);
	fseek(file, 0, SEEK_SET);
	fclose(file);
	initialize();
	run(NBLIN,NBCOL,tab,menu());
	
	endwin();
}





