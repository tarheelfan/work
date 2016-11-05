All: mapInit.cpp
	g++ -Wall -g -O -c mapInit.cpp -lncurses
	g++ -Wall -g -O -c heap.cpp -lncurses
	g++ -Wall -g -O -c monster.cpp -lncurses
	g++ -Wall -g -O -c pcio.cpp -lncurses
	g++ -Wall -g -O -c knowledgeMap.cpp 
	g++ -Wall -g -O -c npcParser.cpp
	g++ -Wall -g -O -c objectParser.cpp
	ar -cvq heap.a heap.o 
	ar -cvq gameMap.a mapInit.o monster.o pcio.o knowledgeMap.o npcParser.o objectParser.o
	g++ -Wall -O0 -ggdb dungeonGame327.cpp -o ShaneDrafahl gameMap.a heap.a -lncurses 
Clean: ShaneDrafahl gameMap.a mapInit.o
	bash cleanSlate.bash
