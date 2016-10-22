# DungeonGame
Dungeon game written in C for COMS 327 at ISU

This program works by a main method that controls the entire program and then each part of the program will be split into separate
.a library files that will be compiled and run by the makefile.

The important command for this release is --nummon <numberOFMonsters> will randomly generate the number of monsters

The mapinit.c file and its respective header files is responsible for generating the map.

The cleanSlate.bash is a bash file that removes object files and compiled binaries.  

The control scheme for this is 8 is up,9 is top right, 6 is right, 3 is bottom right, 5 is wait, 2 is down,1 is bottom left,4 is left,7 it topleft

