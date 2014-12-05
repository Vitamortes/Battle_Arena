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
typedef struct {char nom[20]; int attack; int vie; t_position place; t_camp existe;}t_perso;
typedef struct {int x; int y;}t_lieu;
extern t_perso arena[N][N];
t_lieu pos_perso[P*2]; /** \brief le tableau contient d'abord les P personnages du joueur  puis les P personnages du joueur 
*/


