All: mapInit.c
	gcc -Wall -g -O -c mapInit.c -lncurses
	gcc -Wall -g -O -c heap.c -lncurses
	gcc -Wall -g -O -c monster.c -lncurses
	gcc -Wall -g -O -c pcio.c -lncurses
	ar -cvq heap.a heap.o 
	ar -cvq gameMap.a mapInit.o monster.o pcio.o
	gcc -Wall -O0 -ggdb dungeonGame327.c -o ShaneDrafahl gameMap.a heap.a -lncurses
Clean: ShaneDrafahl gameMap.a mapInit.o
	bash cleanSlate.bash
