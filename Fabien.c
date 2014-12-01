/**	\author Ciron Fabien
*	\date 25/11/2014
*	\version 0.1.0
*	\file Fabien.c	\brief Fonction de gestion de la position des personnages
*/

#include <stdio.h>
#include <stdlib.h>


#define N 10
#define P 3


typedef struct {int x; int y;}t_lieu;
t_lieu pos_perso[P*2]; /** \brief le tableau contient d'abord les P personnages du joueur  puis les P personnages du joueur 
*/

/** \brief fonction de stockage des positions des personnages qui retourne le tableau ainsi obtenu */
void personnage () {
	int i,j;
	int n = 0;
	int m = 0;
	for (i=0; i < N; i++) {
		for (j=0; j < N; j++) {
			if (arena[j][i].existe == joueur1) {
				pos_perso[n].x = j;
				pos_perso[n].y = i;
				n++;
			} else if (arena[j][i].existe == joueur2) {
				pos_perso[m+P].x = j;
				pos_perso[m+P].y = i;
				m++;
			}

		}
	}
}
