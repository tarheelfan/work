All: mapInit.c
	gcc -Wall -g -O -c mapInit.c
	gcc -Wall -g -O -c heap.c
	ar -cvq heap.a heap.o
	ar -cvq gameMap.a mapInit.o
	gcc -static -Wall -ggdb dungeonGame327.c -o ShaneDrafahl gameMap.a heap.a 
Clean: ShaneDrafahl gameMap.a mapInit.o
	bash cleanSlate.bash
