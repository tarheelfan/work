All: map.cpp
	g++ -Wall -g -O -c map.cpp -lncurses
	g++ -Wall -g -O -c heap.cpp -lncurses
	g++ -Wall -g -O -c monster.cpp -lncurses
	g++ -Wall -g -O -c pcio.cpp -lncurses
	g++ -Wall -g -O -c mons.cpp
	g++ -Wall -g -O -c knowledgeMap.cpp
	ar -cvq heap.a heap.o
	ar -cvq gameMap.a mons.o map.o monster.o pcio.o knowledgeMap.o
	g++ -Wall -O0 -ggdb main.cpp -o run gameMap.a heap.a -lncurses
Clean: run gameMap.a map.o
	bash cleanSlate.bash
