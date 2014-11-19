/**	\author Linus König, Candale Elliot
*	\date 19/11/2014
*	\version 1.2.0
*	\file Battle_arena.c	\brief Initialisation du Battle Arena
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N 10
#define P 3

typedef enum {joueur1, joueur2, vide}t_camp;
typedef enum {nord, sud, est, ouest}t_position;
typedef struct {char nom[20]; int attack; int vie; t_position place; t_camp existe;}t_perso;

t_perso arena[N][N];

void affichage(){		/**
				/ \brief affiche les pieces en fonction des equipes 
				*/
     int i =0;
     int j =0;
            for(i=0;i<N;i++){
                printf("\n");
                for(j=0;j<N;j++)
                    switch (arena[i][j].existe){
                        case joueur1 : printf("1 ");
                                       break;
                        case joueur2 : printf("2 ");
                                       break;
                        default      : printf("- ");
                                       break;
                    }
            }
            printf("\n");
}
/**
*	\brief Fonction d'initialisation de l'arene et lecture des position des pièces des joueurs dans deux fichiers .txt
*/
void init(){
	int i;
	int j;
	int x;
	int y;
	int compteur;

	FILE*f1;
	FILE*f2;
	f1= fopen("joueur1.txt", "r");
	f2= fopen("joueur2.txt", "r");

	/**
	*	\brief Vidage de l'arène
	*/
	for(i=0; i<=N; i++){
		for(j=0; j<=N; j++){
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
		arena[x][y].place= nord;
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
		arena[x][y].place= sud;
		printf("Veuillez saisir un nom pour votre personnage\n");		
		scanf("%s", arena[x][y].nom);
	}
	fclose(f2);
}

/**
*	\brief	Gestion des PA avec en paramètre la position de la piece executant les actions
*/
void gestion_pa(int x, int y){
	int pa=3;		//PA= Points d'actions
	int choix=0;		//1 déplacement 2 attacker et 3 tourner
	int nb=0;		//combien de cases a bouger
	int dep=0;		//deplacement

    affichage();
	printf("%s %i points d'action\n Saisir 1 pour déplacement 2 pour attacker ou 3 pour tourner\n",arena[x][y].nom ,pa);
	scanf("%i", &choix);
	while(pa>0){
	    affichage();
		while((choix!=1)&&(choix!=2)&&(choix!=3)){
			printf("Votre choix est incorrect\n Saisir 1 pour déplacement 2 pour attacker ou 3 pour tourner\n");
			scanf("%i", &choix);
		}

		/**
		*	\brief Deplacement sans collision d'unité pour l'instant
		*/
		if(choix==1){
			printf("Veuillez saisir le nombre de case que vous souhaitez avancer (%i points d'action restants)\n",pa);
			scanf("%i",&nb);
			while(nb<pa){
				printf("il ne vous reste que %i points d'action cette action est donc impossible veuillez resaisir\n",pa);
				scanf("%i",&nb);
			}
			pa-=nb;

			/**
			*		\brief dep<=nb pour ne pas ignorer la colision unité
			*/
			if(arena[x][y].place==nord){
				while(dep<=nb){
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
				while(dep<=nb){
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
				while(dep<=nb){
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
				while(dep<=nb){
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
		}

		/**
		*	\brief Attaquer une autre pièce
		*	\bug Friendly Fire n'est pas encore désactiver ^^ et j'ai pas encore fais que de derrière ils prènnent leurs races genre vie-=attack*2 t'en pense quoi?
		*/
		if(choix==2){
			int range=1;	// préparation des classes avec plus de range
			if(arena[x][y].place==ouest){
				if(arena[x-range][y].existe!=vide){
					arena[x-range][y].vie-=arena[x][y].attack;
					printf("%s a pris %i dégats par %s, il lui reste alors %i points de vie",arena[x-range][y].nom ,arena[x][y].attack ,arena[x][y].nom ,arena[x-range][y].vie);
				}else{
					printf("L'attaque parts dans le vide\n");
				}
				pa--;
			}
			if(arena[x][y].place==est){
				if(arena[x+range][y].existe!=vide){
					arena[x+range][y].vie-=arena[x][y].attack;
					printf("%s a pris %i dégats par %s, il lui reste alors %i points de vie",arena[x+range][y].nom ,arena[x][y].attack ,arena[x][y].nom ,arena[x+range][y].vie);
				}else{
					printf("L'attaque parts dans le vide\n");
				}
				pa--;
			}
			if(arena[x][y].place==nord){
				if(arena[x][y-range].existe!=vide){
					arena[x][y-range].vie-=arena[x][y].attack;
					printf("%s a pris %i dégats par %s, il lui reste alors %i points de vie",arena[x][y-range].nom ,arena[x][y].attack ,arena[x][y].nom ,arena[x][y-range].vie);
				}else{
					printf("L'attaque parts dans le vide\n");
				}
				pa--;
			}
			if(arena[x][y].place==sud){
				if(arena[x][y+range].existe!=vide){
					arena[x][y+range].vie-=arena[x][y].attack;
					printf("%s a pris %i dégats par %s, il lui reste alors %i points de vie",arena[x][y+range].nom ,arena[x][y].attack ,arena[x][y].nom ,arena[x][y+range].vie);
				}else{
					printf("L'attaque parts dans le vide\n");
				}
				pa--;
			}
		}

		/**
		*	\brief j'essites encore si tourner 90° coutes autant que 180° bref pour l'instant c'est 1pa les deux on verras plus tard
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
		}
	}
}

int main(){
	int charger=0;
	printf("Continuer la partie sauvegarder ou recommencer une partie? 1=charger 2=new\n");
	scanf("%i",&charger);
	while((charger!=1)&&(charger!=2)){
		printf("Continuer la partie sauvegarder ou recommencer une partie? 1=charger 2=new\n");	// #laflemme pour le message personnaliser
		scanf("%i",&charger);
	}
	if(charger==1){
		FILE*fs;
		fs= fopen("sauvegarde.txt","w");
		/**
		*	\bug Ouais ici je galère entre les fscanfs et fprintf donc a voir ensemble
		*/
		fclose(fs);
	}
	if(charger==2){
		init();
	}

	/**
	*	\brief pour tester a partir d'ici docn pas a prendre en compte pour le cas commun
	*/
	gestion_pa(1,1);
	return EXIT_SUCCESS;
}
