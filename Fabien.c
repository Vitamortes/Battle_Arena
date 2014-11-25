/**	\author Ciron Fabien
*	\date 25/11/2014
*	\version 0.1.0
*	\file Fabien.c	\brief Fonction de gestion de la position des personnages
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 10
#define P 3

typedef struct {int x, int y}t_lieu;
t_lieu joueur[P*2];

t_lieu personnage (t_perso arena[N][N]) {
	int i,j;
	int n = 0;
	for (i=0; i < N; i++) {
		for (j=0; j < N; j++) {
			if (arena[j][i].existe == joueur1) {
				joueur[n].x = j;
				joueur[n].y = i;
				n++;
			} else if (arena[j][i].existe == joueur2) {
				joueur[n+P].x = j;
				joueur[n+P].y = i;
				n++;
			}
		}
	}
	return joueur;
}
