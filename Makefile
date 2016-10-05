All: mapInit.c
	gcc -Wall -g -O -c mapInit.c
	gcc -Wall -g -O -c heap.c
	gcc -Wall -g -O -c monster.c
	ar -cvq heap.a heap.o
	ar -cvq gameMap.a mapInit.o monster.o
	gcc -static -Wall -O0 -ggdb dungeonGame327.c -o ShaneDrafahl gameMap.a heap.a 
Clean: ShaneDrafahl gameMap.a mapInit.o
	bash cleanSlate.bash
