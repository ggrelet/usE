#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *texte = NULL, *fond = NULL;
    SDL_Rect position;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    int continuer = 1;
    int var=1;
    char b[20]="";


    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ecran = SDL_SetVideoMode(1000, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Gestion du texte avec SDL_ttf", NULL);

    fond = IMG_Load("strudel.jpg");

    /* Chargement de la police */
    police = TTF_OpenFont("angelina.ttf", 65);
    /* �criture du texte dans la SDL_Surface texte en mode Blended (optimal) */



    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
           {
               case SDLK_DOWN:
                    var++;
             }

        }

        sprintf (b, "Score : %d", var);
        texte = TTF_RenderText_Blended(police, b, couleurNoire);

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(fond, NULL, ecran, &position); /* Blit du fond */

        position.x = 60;
        position.y = 370;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);

    }

    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);
    SDL_Quit();

    return EXIT_SUCCESS;

}
