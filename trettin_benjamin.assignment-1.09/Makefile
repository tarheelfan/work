All: map.cpp
	g++ -Wall -g -O -c map.cpp -lncurses
	g++ -Wall -g -O -c heap.cpp -lncurses
	g++ -Wall -g -O -c monster.cpp -lncurses
	g++ -Wall -g -O -c pcio.cpp -lncurses
	g++ -Wall -g -O -c knowledgeMap.cpp 
	g++ -Wall -g -O -c npcParser.cpp
	g++ -Wall -g -O -c objectParser.cpp
	g++ -Wall -g -O -c dice.cpp
	g++ -Wall -g -O -c monsterFactory.cpp
	g++ -Wall -g -O -c objectManager.cpp	
	ar -cvq heap.a heap.o 
	ar -cvq gameMap.a map.o monster.o pcio.o knowledgeMap.o npcParser.o objectParser.o dice.o monsterFactory.o objectManager.o
	g++ -Wall -O0 -ggdb main.cpp -o run gameMap.a heap.a -lncurses 
Clean: run gameMap.a map.o
	bash cleanSlate.bash
