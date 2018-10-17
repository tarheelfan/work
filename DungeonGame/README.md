# DungeonGame
Dungeon game written in C for COMS 327 at ISU

This program works by a main method that controls the entire program and then each part of the program will be split into separate
.a library files that will be compiled and run by the makefile.

The important command for this release is --nummon <numberOFMonsters> will randomly generate the number of monsters

The mapinit.c file and its respective header files is responsible for generating the map.

The cleanSlate.bash is a bash file that removes object files and compiled binaries.  

This program has two switches on it, one is --save and the other is --load , these functions will load or save a file from your home file in a directory called .rlg327 in a file called Dungeon
