/**	\author Linus König
*	\date 12/12/2014
*	\version 2.0.1
*	\file Battle_arena.c	\brief Main du Battle Arena avec quelque fonctions
*/
#include "fonctions.h"
t_perso arena[N][N];


//----------------------------------------------------------------------------------------------LE-MAIN---------------------------------------------------------------
int main(){
	int charger=0;
	int p1=P;
	int p2=P;
	int tour=2;
	printf("Continuer la partie sauvegarder ou recommencer une partie? 1=charger 2=new\n");
	scanf("%i",&charger);
	while((charger!=1)&&(charger!=2)){
		printf("Continuer la partie sauvegarder ou recommencer une partie? 1=charger 2=new\n");	// #laflemme pour le message personnaliser
		scanf("%i",&charger);
	}
	if(charger==1){
		load_game();
	}
	if(charger==2){
		init();
		while((p1!=0)&&(p2!=0)){
			if(tour==2)
				tour=1;
			else 
				tour=2;
					
			
		}		
	}
	return EXIT_SUCCESS;
}
