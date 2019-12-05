src=src
dst=build

all : $(dst)/main.o $(dst)/car.o $(dst)/initialisation.o $(dst)/menu.o $(dst)/misc.o
	gcc -Wall $(dst)/main.o $(dst)/car.o $(dst)/initialisation.o  $(dst)/menu.o $(dst)/misc.o -o Exec -lncursesw -g

$(dst)/main.o : $(src)/main.c
	gcc -Wall -c $(src)/main.c -lncursesw -g -o $(dst)/main.o

$(dst)/car.o : $(src)/car.c $(src)/car.h 
	gcc -Wall -c $(src)/car.c -lncursesw -g -o $(dst)/car.o

$(dst)/initialisation.o : $(src)/initialisation.c $(src)/initialisation.h
	gcc -Wall -c $(src)/initialisation.c -lncurses -g -o $(dst)/initialisation.o
	
$(dst)/menu.o : $(src)/menu.c $(src)/menu.h
	gcc -Wall -c $(src)/menu.c -lncurses -g -o $(dst)/menu.o
	
$(dst)/misc.o : $(src)/misc.c $(src)/misc.h  
	gcc -Wall -c $(src)/misc.c -lncurses -g -o $(dst)/misc.o

.PHONY : clean
clean :
	-rm $(dst)/* Exec

