All: map.c
	gcc -Wall -g -O -c map.c -lncurses
	gcc -Wall -g -O -c heap.c -lncurses
	gcc -Wall -g -O -c monster.c -lncurses
	gcc -Wall -g -O -c pcio.c -lncurses
	ar -cvq heap.a heap.o 
	ar -cvq gameMap.a map.o monster.o pcio.o
	gcc -Wall -O0 -ggdb main.c -o run gameMap.a heap.a -lncurses
Clean: run gameMap.a map.o
	bash cleanSlate.bash
