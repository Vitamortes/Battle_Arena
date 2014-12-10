/**	\author Linus König
*	\date 10/12/2014
*	\version 2.0.0
*	\file Battle_arena.c	\brief Main du Battle Arena avec quelque fonctions
*/
#include "fonctions.h"
t_perso arena[N][N];

//------------------------------------------------------------------------------------------FONCTION-AFFICHER---------------------------------------------------------
void affichage(){		/**
				/ \brief affiche les pieces en fonction des equipes
				*/
     int i =0;
     int j =0;
            for(i=0;i<N;i++){
                printf("\n"); 
                for(j=0;j<N;j++)
                    switch (arena[j][i].existe){
                        case joueur1 : 	printf(" _____ ");
					printf(" | 1 | ");
					printf(" _____ ");
                                       break;
                        case joueur2 :	printf(" _____ "); 
					printf(" | 2 | ");
					printf(" _____ ");
                                       break;
                        default      : 	printf(" _____ ");
					printf(" |   | ");
					printf(" ____ ");
                                       break;
                    }
            }
            printf("\n");
}


//--------------------------------------------------------------------------------------INITIALISATION-DE-L-ARENE-----------------------------------------------------
/**
*	\brief Fonction d'initialisation de l'arene et lecture des position des pièces des joueurs dans deux fichiers .txt
*/
void init(){
	int i;
	int j;
	int x;
	int y;
	int compteur;

	FILE*f1= fopen("joueur1.txt", "r");
	FILE*f2= fopen("joueur2.txt", "r");

	/**
	*	\brief Vidage de l'arène
	*/
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			arena[i][j].existe= vide;
		}
	}

	/**
	*	\brief Personnages du joueur1
	*/
	for(compteur=0; compteur<P; compteur++){
		printf("Positionnement des personnages du joueur1\n");
		fscanf(f1, "%i", &x);
		fscanf(f1, "%i", &y);
		arena[x][y].existe= joueur1;
		arena[x][y].attack= rand()%4;
		arena[x][y].vie= rand()%4;
		arena[x][y].place= sud;
		printf("Veuillez saisir un nom pour votre personnage\n");	/**
										*	\brief Permet de "personaliser" ses personnages
										*/
		scanf("%s", arena[x][y].nom);
	}
	fclose(f1);

	/**
	*	\brief Personnages du Joueur2
	*/
	for(compteur=0; compteur<P; compteur++){
		printf("Positionnement des personnages du joueur2\n");
		fscanf(f2, "%i", &x);
		fscanf(f2, "%i", &y);
		arena[x][y].existe= joueur2;
		arena[x][y].attack= rand()%4;
		arena[x][y].vie= rand()%4;
		arena[x][y].place= nord;
		printf("Veuillez saisir un nom pour votre personnage\n");
		scanf("%s", arena[x][y].nom);
	}
	fclose(f2);
}





//------------------------------------------------------------------------------------------GESTION-DES-POINTS-D-ACTION-----------------------------------------------
/**
*	\brief	Gestion des PA avec en paramètre la position de la piece executant les actions et le nombre de pieves vivantes par equipe
*/
t_actu gestion_pa(int x, int y, int* j1, int* j2){
	int pa=3;		//PA= Points d'actions
	int choix=0;		//1 déplacement 2 attacker et 3 tourner
	int nb=0;		//combien de cases a bouger
	int dep=0;		//deplacement
	int ff=0;		//friendly fire
	t_actu actuel;		//situation actuelle

    	affichage();
	printf("%s %i points d'action\n Saisir 1 pour déplacement 2 pour attacker ou 3 pour tourner\n",arena[x][y].nom ,pa);
	scanf("%i", &choix);
	while(pa>0){
	    affichage();
		if (choix==0){
			printf("%s %i points d'action\n Saisir 1 pour déplacement 2 pour attacker ou 3 pour tourner\n",arena[x][y].nom ,pa);
			scanf("%i", &choix);	
		}
		while((choix!=1)&&(choix!=2)&&(choix!=3)){
			printf("Votre choix est incorrect\n Saisir 1 pour déplacement 2 pour attacker ou 3 pour tourner\n");
			scanf("%i", &choix);
		}


//-----------------------------------------------------------------------------------------------DEPLACER-------------------------------------------------------------
		/**
		*	\brief Déplacement des personnages
		*/
		if(choix==1){
			printf("Veuillez saisir le nombre de case que vous souhaitez avancer (%i points d'action restants)\n",pa);
			scanf("%i",&nb);
			while(nb>pa){
				printf("il ne vous reste que %i points d'action cette action est donc impossible veuillez ressaisir\n",pa);
				scanf("%i",&nb);
			}
			pa-=nb;

			/**
			*		\brief dep<=nb pour ne pas ignorer la colision unité
			*/
			if(arena[x][y].place==nord){
				while(dep<nb){
					if(arena[x][y-1].existe!=vide){
						printf("Unité sur l'emplacement spécifié\n");
						break;
					}
					strcpy(arena[x][y-1].nom, arena[x][y].nom);
					arena[x][y-1].attack= arena[x][y].attack;
					arena[x][y-1].vie= arena[x][y].vie;
					arena[x][y-1].place= arena[x][y].place;
					arena[x][y-1].existe= arena[x][y].existe;

					arena[x][y].existe= vide;
					y--;
					dep++;
				}
			}
			dep=0;
			if(arena[x][y].place==sud){
				while(dep<nb){
					if(arena[x][y+1].existe!=vide){
						printf("Unité sur l'emplacement spécifié\n");
						break;
					}
					strcpy(arena[x][y+1].nom, arena[x][y].nom);
					arena[x][y+1].attack= arena[x][y].attack;
					arena[x][y+1].vie= arena[x][y].vie;
					arena[x][y+1].place= arena[x][y].place;
					arena[x][y+1].existe= arena[x][y].existe;

					arena[x][y].existe= vide;
					y++;
					dep++;
				}
			}
			dep=0;
			if(arena[x][y].place==est){
				while(dep<nb){
					if(arena[x+1][y].existe!=vide){
						printf("Unité sur l'emplacement spécifié\n");
						break;
					}
					strcpy(arena[x+1][y].nom, arena[x][y].nom);
					arena[x+1][y].attack= arena[x][y].attack;
					arena[x+1][y].vie= arena[x][y].vie;
					arena[x+1][y].place= arena[x][y].place;
					arena[x+1][y].existe= arena[x][y].existe;

					arena[x][y].existe= vide;
					x++;
					dep++;
				}
			}
			dep=0;
			if(arena[x][y].place==ouest){
				while(dep<nb){
					if(arena[x-1][y].existe!=vide){
						printf("Unité sur l'emplacement spécifié\n");
						break;
					}
					strcpy(arena[x-1][y].nom, arena[x][y].nom);
					arena[x-1][y].attack= arena[x][y].attack;
					arena[x-1][y].vie= arena[x][y].vie;
					arena[x-1][y].place= arena[x][y].place;
					arena[x-1][y].existe= arena[x][y].existe;

					arena[x][y].existe= vide;
					x--;
					dep++;
				}
			}
		choix=0;
		}



//---------------------------------------------------------------------------------ATTAQUER---------------------------------------------------------------------------
		/**
		*	\brief Attaquer une autre piece
		*/
		if(choix==2){
			int range=1;	// préparation des classes avec plus de range
			if(arena[x][y].place==ouest){
				if((arena[x][y].existe==joueur1)&&(arena[x-range][y].existe==joueur1)){
					printf("on n'attaques pas les amis!!! 1 points d'action perdu pour pénalité\n");
					ff=1;
				}
				if((arena[x][y].existe==joueur2)&&(arena[x-range][y].existe==joueur2)){
					printf("on n'attaques pas les amis!!! 1 points d'action perdu pour pénalité\n");
					ff=1;
				}
				if((arena[x-range][y].existe!=vide)&&(ff!=1)){
					if(arena[x][y].place==arena[x-range][y].place){
						arena[x-range][y].vie-=2*arena[x][y].attack;
					printf("%s a pris %i dégats critiques par %s, il lui reste alors %i points de vie\n",arena[x-range][y].nom ,arena[x][y].attack ,arena[x][y].nom ,arena[x-range][y].vie);
					}else{
						arena[x-range][y].vie-=arena[x][y].attack;
						printf("%s a pris %i dégats par %s, il lui reste alors %i points de vie\n",arena[x-range][y].nom ,arena[x][y].attack ,arena[x][y].nom ,arena[x-range][y].vie);
					}
					if(arena[x-range][y].vie<=0){ /*gestion des personnages on envois xy et on sait qui est mort le tableau de la fonction personnage est imédiatement mis à jour, chacunes de ses cases représente un personnage*/
						arena[x-range][y].existe=vide;
						if(arena[x-range][y].existe==joueur1){
							j1--;
						}
						if(arena[x-range][y].existe==joueur2){
							j2--;
						}
					}
				}else{
					printf("L'attaque parts dans le vide\n");
				}
				pa--;
				ff=0;
			}
			if(arena[x][y].place==est){
				if((arena[x][y].existe==joueur1)&&(arena[x+range][y].existe==joueur1)){
					printf("on n'attaques pas les amis!!! 1 points d'action perdu pour pénalité\n");
					ff=1;
				}
				if((arena[x][y].existe==joueur2)&&(arena[x+range][y].existe==joueur2)){
					printf("on n'attaques pas les amis!!! 1 points d'action perdu pour pénalité\n");
					ff=1;
				}
				if((arena[x+range][y].existe!=vide)&&(ff!=0)){
					if(arena[x][y].place==arena[x+range][y].place){
						arena[x+range][y].vie-=2*arena[x][y].attack;
						printf("%s a pris %i dégats critiques par %s, il lui reste alors %i points de vie\n",arena[x+range][y].nom ,arena[x][y].attack ,arena[x][y].nom ,arena[x-range][y].vie);
					}else{
						arena[x+range][y].vie-=arena[x][y].attack;
						printf("%s a pris %i dégats par %s, il lui reste alors %i points de vie\n",arena[x+range][y].nom ,arena[x][y].attack ,arena[x][y].nom ,arena[x+range][y].vie);
					}
					if(arena[x+range][y].vie<=0){
						arena[x+range][y].existe=vide;
						if(arena[x+range][y].existe==joueur1){
							j1--;
						}
						if(arena[x+range][y].existe==joueur2){
							j2--;
						}
					}
				}else{
					printf("L'attaque parts dans le vide\n");
				}
				pa--;
				ff=0;
			}
			if(arena[x][y].place==nord){
				if((arena[x][y].existe==joueur1)&&(arena[x][y-range].existe==joueur1)){
					printf("on n'attaques pas les amis!!! 1 points d'action perdu pour pénalité\n");
					ff=1;
				}
				if((arena[x][y].existe==joueur2)&&(arena[x][y-range].existe==joueur2)){
					printf("on n'attaques pas les amis!!! 1 points d'action perdu pour pénalité\n");
					ff=1;
				}
				if((arena[x][y-range].existe!=vide)&&(ff!=0)){
					if(arena[x][y].place==arena[x][y-range].place){
						arena[x][y-range].vie-=2*arena[x][y].attack;
						printf("%s a pris %i dégats critiques par %s, il lui reste alors %i points de vie\n",arena[x][y-range].nom ,arena[x][y].attack ,arena[x][y].nom ,arena[x][y-range].vie);
					}else{
						arena[x][y-range].vie-=arena[x][y].attack;
						printf("%s a pris %i dégats par %s, il lui reste alors %i points de vie\n",arena[x][y-range].nom ,arena[x][y].attack ,arena[x][y].nom ,arena[x][y-range].vie);
					}
					if(arena[x][y-range].vie<=0){
						arena[x][y-range].existe=vide;
						if(arena[x][y-range].existe==joueur1){
							j1--;
						}
						if(arena[x][y-range].existe==joueur2){
							j2--;
						}
					}
				}else{
					printf("L'attaque parts dans le vide\n");
				}
				pa--;
				ff=0;
			}
			if(arena[x][y].place==sud){
				if((arena[x][y].existe==joueur1)&&(arena[x][y+range].existe==joueur1)){
					printf("on n'attaques pas les amis!!! 1 points d'action perdu pour pénalité\n");
					ff=1;
				}
				if((arena[x][y].existe==joueur2)&&(arena[x][y+range].existe==joueur2)){
					printf("on n'attaques pas les amis!!! 1 points d'action perdu pour pénalité\n");
					ff=1;
				}
				if((arena[x][y+range].existe!=vide)&&(ff!=0)){
					if(arena[x][y].place==arena[x][y+range].place){
						arena[x][y+range].vie-=2*arena[x][y].attack;
						printf("%s a pris %i dégats critiques par %s, il lui reste alors %i points de vie\n",arena[x][y+range].nom ,arena[x][y].attack ,arena[x][y].nom ,arena[x][y-range].vie);
					}else{
						arena[x][y+range].vie-=arena[x][y].attack;
						printf("%s a pris %i dégats par %s, il lui reste alors %i points de vie",arena[x][y+range].nom ,arena[x][y].attack ,arena[x][y].nom ,arena[x][y+range].vie);
					}
					if(arena[x][y+range].vie<=0){
						arena[x][y+range].existe=vide;
						if(arena[x][y+range].existe==joueur1){
							j1--;
						}
						if(arena[x][y+range].existe==joueur2){
							j2--;
						}
					}
				}else{
					printf("L'attaque parts dans le vide\n");
				}
				pa--;
				ff=0;
			}
		choix=0;
		}


//------------------------------------------------------------------------------------------------TOURNER-------------------------------------------------------------
		/**
		*	\brief tourner 90° coute 1pa comme 180°
		*/
		if(choix==3){
			int posi=0;
			printf("Veuillez choisir comment orienter votre pièce 1=nord 2=sud 3=est 4=ouest\n");
			scanf("%i",&posi);
			while((posi!=1)&&(posi!=2)&&(posi!=3)&&(posi!=4)){
				scanf("%i",&posi);
			}
			if(posi==1){
				arena[x][y].place=nord;
			}
			if(posi==2){
				arena[x][y].place=sud;
			}
			if(posi==3){
				arena[x][y].place=est;
			}
			if(posi==4){
				arena[x][y].place=ouest;
			}
			pa--;
			choix=0;
		}
	}
}


//----------------------------------------------------------------------------------------------LE-MAIN---------------------------------------------------------------
int main(){
	int charger=0;
	int p1=P;
	int p2=P;
	int tour=2;
	int numjoueur=0;
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
