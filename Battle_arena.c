/**	\author Linus König
*	\date 12/12/2014
*	\version 2.0.1
*	\file Battle_arena.c	\brief Main du Battle Arena avec quelque fonctions
*/
#include "fonctions.h"
#include "fonctionsgrph.h"
t_perso arena[N][N];
int tour;

//----------------------------------------------------------------------------------------------LE-MAIN---------------------------------------------------------------
int main(){
	int charger=0;
	int winner=0;

	printf("Choix du mode d'affichage: \n 1 = mode graphique\n 2 = mode terminal\n\nVotre choix?\n");
	while((charger<1)&&(charger>2))
		scanf("%i",&charger);
	if(charger==1)
		maingrph();
	else{
		charger=0;
		printf("Continuer la partie sauvegarder ou recommencer une partie? 1=new 2=charger\n");
		scanf("%i",&charger);
		while((charger!=1)&&(charger!=2)){
			printf("Continuer la partie sauvegarder ou recommencer une partie? 1=new 2=charger\n");	// #laflemme pour le message personnaliser
			scanf("%i",&charger);
		}
		if(charger==2){
			load_game();
		}
		else
			init();
	
		gest_pers();
	}
	return EXIT_SUCCESS;
}
