#include "fonctions.h"			
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
			if(arena[j][i].existe=joueur1){
				*tabj1[j1]=arena[j][i];
				*pj1+=1;
			}
			else if(arena[j][i].existe=joueur2){
				*tabj2[j2]=arena[j][i];
				*pj2+=1;
			}
		}

}

/** \brief on fini et on commente après */
void gest_pers() {
	int tabj1[2];
	int tabj2[2];
	int j1 =0;
	int j2 =0;
	int j1act=0;
	int j2act=0;

	t_perso tabj1[P];
	t_perso tabj2[P];	
	
	t_perso* tabj1;
	t_perso* tabj2;
	
	if(tour==0){
		init_gest(tabj1, tabj2, &j1, &j2);
	}
	else
		while((j1act!=j1)&&(j2act!=j2)){
			if((tour==1))&&(j1act<j1)){
				gestion_pa(tabj1[j1act].x,tabj1[j1act].y, &j1, &j2);
				j1act++;
				tour=2;
			}
			if((tour==2))&&(j2act<j2)){
				gestion_pa(tabj2[j2act].x,tabj2[j2act].y, &j1, &j2);
				j2act++;
				tour=1;
			}
			j1act=0;
			j2act=0;
		}
}
