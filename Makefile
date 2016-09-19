All: mapInit.c
	gcc -Wall -g -O -c mapInit.c
	gcc -Wall -g -O -c binheap.c
	ar -cvq binheap.a binheap.o
	ar -cvq gameMap.a mapInit.o
	gcc -static -Wall -ggdb dungeonGame327.c -o ShaneDrafahl gameMap.a 
Clean: ShaneDrafahl gameMap.a mapInit.o
	bash cleanSlate.bash
