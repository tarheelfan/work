All: mapInit.c
	gcc -g -O -c mapInit.c
	ar -cvq gameMap.a mapInit.o
	gcc -static -Wall -ggdb dungeonGame327.c -g -o ShaneDrafahl ./gameMap.a -L.
 
 
 
