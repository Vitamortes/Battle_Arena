#include "fonctions.h"	

//------------------------------------------------------------------------------------------FONCTION-AFFICHER---------------------------------------------------------
void affichage(){		/**
				/ \brief affiche les pieces en fonction des equipes
				*/
     	int i =0;
     	int j =0;
	int compt=0;
            for(i=0;i<N;i++){
                for(compt=0;compt<N;compt++){
			printf("___");
		}
		printf("\n");
                for(j=0;j<N;j++){
                	switch (arena[j][i].existe){

                       		case joueur1 :	if(j==N-1){
							printf(" | 1 | ");
						}else{ 	
							printf(" | 1  ");
						}
                                       		break;
                        	case joueur2 :	if(j==N-1){
							printf(" | 2 | ");
						}else{ 	
							printf(" | 2  ");
						}
                                       		break;
                        	default      : 	if(j==N-1){
							printf(" |   | ");
						}else{ 	
							printf(" |    ");
						}
                                       		break;
             		}
			for(compt=0;compt<N;compt++){
				printf("___");
			}
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
	int pc=3;		//points de compétances
	int placer;	//pour placer le pc

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
	for(compteur=P; compteur>0; compteur--){
		printf("Positionnement des personnages du joueur1\n");
		fscanf(f1, "%i", &x);
		fscanf(f1, "%i", &y);
		arena[x][y].existe= joueur1;
		arena[x][y].attack= 1;
		arena[x][y].vie= 1;
		arena[x][y].range=1;
		printf("votre personnage a %i points de vie %i points d'attack et %i de range \n il vous reste %i points de compétance a placer \n 1: Attack 2:Vie 3:Range\n", arena[x][y].vie, arena[x][y].attack, arena[x][y].range, pc);
		
		while(pc>0){
			scanf("%i",&placer);
			if(placer==1){
				arena[x][y].attack++;
				pc--;
				printf("Point attribué\n");
			}
	
			if(placer==2){
				arena[x][y].vie++;
				pc--;
				printf("Point attribué\n");
			}

			if(placer==3){
				arena[x][y].range++;
				pc--;
				printf("Point attribué\n");
			}					
		}
		arena[x][y].place= sud;
		printf("Ce personnage as donc %i attack %i vie %i range\n",arena[x][y].attack ,arena[x][y].vie ,arena[x][y].range);
		printf("Veuillez saisir un nom pour le personnage que vous venez de crée\n");	
		scanf("%s", arena[x][y].nom);
		pc=3;
		printf("\n\n\n\n\n");
		
	}
	fclose(f1);

	/**
	*	\brief Personnages du Joueur2
	*/
	for(compteur=P; compteur>0; compteur--){
		printf("Positionnement des personnages du joueur2\n");
		fscanf(f2, "%i", &x);
		fscanf(f2, "%i", &y);
		arena[x][y].existe= joueur2;
		arena[x][y].attack= 1;
		arena[x][y].vie= 1;
		arena[x][y].range=1;
		printf("votre personnage a %i points de vie %i points d'attack et %i de range \n il vous reste %i points de compétance a placer \n 1: Attack 2:Vie 3:Range\n", arena[x][y].vie, arena[x][y].attack, arena[x][y].range, pc);
		
		while(pc>0){
			scanf("%i",&placer);
			if(placer==1){
				arena[x][y].attack++;
				pc--;
				printf("Point attribué\n");
			}
	
			if(placer==2){
				arena[x][y].vie++;
				pc--;
				printf("Point attribué\n");
			}

			if(placer==3){
				arena[x][y].range++;
				pc--;
				printf("Point attribué\n");
			}					
		}
		arena[x][y].place= nord;
		printf("Ce personnage as donc %i attack %i vie %i range\n",arena[x][y].attack ,arena[x][y].vie ,arena[x][y].range);
		printf("Veuillez saisir un nom pour le personnage que vous venez de crée\n");	
		scanf("%s", arena[x][y].nom);
		pc=3;
		printf("\n\n\n\n\n");
	}
	fclose(f2);
	printf("fin!");

}





//------------------------------------------------------------------------------------------GESTION-DES-POINTS-D-ACTION-----------------------------------------------
/**
*	\brief	Gestion des PA avec en paramètre la position de la piece executant les actions et le nombre de pieves vivantes par equipe
*/
void gestion_pa(int x, int y, int* j1, int* j2){
	int pa=3;		//PA= Points d'actions
	int choix=0;		//1 déplacement 2 attacker et 3 tourner
	int nb=0;		//combien de cases a bouger
	int dep=0;		//deplacement
	int ff=0;		//friendly fire
	int range =0;

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
					arena[x][y-1].range= arena[x][y].range;

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
					arena[x][y+1].range= arena[x][y].range;

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
					arena[x+1][y].range= arena[x][y].range;

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
					arena[x-1][y].range= arena[x][y].range;

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
			range=arena[x][y].range;	//gestion de la distance necassaire pour attaquer
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

		
	/**
				/ \brief chargement de la partie
				*/
void load_game(){
    FILE* fic =fopen("sauvegarde.txt","r");
    int i,j,val;
    char car[20];
    for(i=0;i < N;i++){
        for(j=0;j< N; j++){
            fscanf(fic,"%i", &val);
            if(val==8)
                arena[j][i].existe=vide;
            if(val==1)
                arena[j][i].existe= joueur1;
            else
                arena[j][i].existe=joueur2;
            fscanf(fic, "%i", &val);
                arena[j][i].attack=val;
            fscanf(fic, "%i", &val);
                arena[j][i].vie=val;
            fscanf(fic, "%i", &val);
            switch(val){
                    case 0: arena[j][i].place=nord;break;
                    case 1: arena[j][i].place=sud;break;
                    case 2: arena[j][i].place=est;break;
                    case 3: arena[j][i].place=ouest;break;
            }
            fscanf(fic,"%s", car);
            strcpy(arena[j][i].nom, car);
	    fscanf(fic,"%i", &tour);
        }
    }
    fclose(fic);
}

				/**
				/ \brief sauvegarde de la partie
				*/
void save_game(){
    FILE* fic =fopen("sauvegarde.txt","w");
    int i,j;
    for(i=0;i < N;i++){
        for(j=0;j< N; j++){
                            switch(arena[j][i].existe){
                                case vide : fprintf(fic,"8 ");break;
                                default :
                                           if(arena[j][i].existe==joueur1){
                                                        fprintf(fic,"1 ");
                                                    }
                                                    else{
                                                        fprintf(fic,"2 ");
                                                    }
                                            fprintf(fic,"%i ", arena[j][i].attack);
                                            fprintf(fic," %i", arena[j][i].vie);
                                            switch(arena[j][i].place){
                                                    case nord:  fprintf(fic,"0");break;
                                                    case sud:   fprintf(fic, "1");break;
                                                    case est:   fprintf(fic, "2");break;
                                                    case ouest: fprintf(fic, "3");break;
                                            }
                                            fprintf(fic,"%s ", arena[j][i].nom);
					    fprintf(fic,"%i", tour);

                                            break;
                            }
        }
    }
    fclose(fic);
}

void init_gest(t_actu *tabj1, t_actu *tabj2,int *pj1,int *pj2){
	int i,j;
	int j1=0;
	int j2=0;
	
	for(i=0;i<N;i++)
		for(j=0;j<N;j++){
			if(arena[j][i].existe==joueur1){
				tabj1[j1]. x=i;
				tabj1[j1]. y=j;
				*pj1+=1;
			}
			else if(arena[j][i].existe==joueur2){
				tabj2[j2]. x=i;
				tabj2[j2]. y=j;
				*pj2+=1;
			}
		}

}

/** \brief on fini et on commente après */
void gest_pers() {
	int j1 =0;
	int j2 =0;
	int j1act=0;
	int j2act=0;

	t_actu tabj1[P];
	t_actu tabj2[P];	
	
	init_gest(tabj1, tabj2, &j1, &j2);
	while((j1act!=j1)&&(j2act!=j2)){
		if((tour==1)&&(j1act<j1)){
			gestion_pa(tabj1[j1act].x,tabj1[j1act].y, &j1, &j2);
			j1act++;
			tour=2;
		}
		if((tour==2)&&(j2act<j2)){
			gestion_pa(tabj2[j2act].x,tabj2[j2act].y, &j1, &j2);
			j2act++;
			tour=1;
		}
		j1act=0;
		j2act=0;
	}
	
}
