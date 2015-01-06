#include "fonctionsgrph.h"	

void maingrph(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	SDL_SetVideoMode( 800, 600, 32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Battle Arena",NULL);
	SDL_Surface *ecran=SDL_SetVideoMode( 800, 600, 32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	imagedeFond=SDL_LoadBMP("titre.bmp");
	Wait(5000);
	SDL_Flip(ecran);	
	SDL_Quit();
}
