CC = gcc -Wall -lSDLmain -lSDL
OBJ = Battle_arena.o	fonctions.o	fonctionsgrph.o

prog :	$(OBJ)
	$(CC) $(OBJ) -o	prog

fonctionsgrph.o : fonctionsgrph.c
	$(CC) -c fonctionsgrph.c

fonctions.o : fonctions.c fonctions.h
	$(CC) -c fonctions.c

Battle_Arena.o : Battle_Arena.c
	$(CC) -c Battle_Arena.c

turlututu
