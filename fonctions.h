#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



#define N 10
#define P 3

void load_game();
void save_game();


typedef enum {joueur1, joueur2, vide}t_camp;
typedef enum {nord, sud, est, ouest}t_position;
<<<<<<< HEAD
typedef struct {char nom[20]; int attack; int vie; t_position place; t_camp existe; int range}t_perso;
typedef struct {int x; int y; int indice;}t_actu;
=======
typedef struct {char nom[20]; int attack; int vie; t_position place; t_camp existe;}t_perso;
typedef struct {int x; int y;}t_actu;
>>>>>>> 2dbcfb9b540be6df292b05fe9b636cb9019b58dd
extern t_perso arena[N][N];
int tour;


