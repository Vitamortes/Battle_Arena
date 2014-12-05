CC = gcc -Wall
OBJ = Battle_arena.o	fonctions.o

prog :	$(OBJ)
	$(CC) $(OBJ) -o	prog

fonctions.o : fonctions.c fonctions.h
	$(CC) -c fonctions.c

Battle_Arena.o : Battle_Arena.c
	$(CC) -c Battle_Arena.c


