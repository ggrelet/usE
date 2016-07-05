#include <cstdio>
#include <cstdlib>

#include <SDL/SDL.h>

#include <wiiuse.h>
#define MAX_WIIMOTE 1

int main(int argc,char **argv)
{
    SDL_Surface *ecran=NULL,*sur1=NULL, *sur2=NULL;
    SDL_Event event;
    SDL_Rect pos1={0,0};
    SDL_Rect pos2={20,20};
    bool continuer=true;
    int tempsPrecedent = 0, tempsActuel = 0;

    wiimote_t** wiimotes;
    int found, connected;

    SDL_Init(SDL_INIT_VIDEO); //On initialise la SDL

    wiimotes=wiiuse_init(MAX_WIIMOTE); //On initialise la premiere Wiimote
    found = wiiuse_find(wiimotes, MAX_WIIMOTE,5);//On essaie de la trouver
    if (!found){
        fprintf(stderr,"Aucune Wiimote trouvee\n");
        return 0;
    }
    connected = wiiuse_connect(wiimotes, MAX_WIIMOTE);
    if(connected) {
          printf("connected to wiimote \n");
} else {
     printf("Failed to connect to any wiimote\n");
return 0;
}

    wiiuse_set_leds(wiimotes[0],WIIMOTE_LED_1); //On fixe sa DEL a la position 1
    wiiuse_rumble(wiimotes[0],1); //On la fait vibrer pendant 400 ms
    SDL_Delay(200);
    wiiuse_rumble(wiimotes[0],0);
    wiiuse_set_ir(wiimotes[0],1); //On active l'infrarouge pour la premiere Wiimote
    wiiuse_set_ir_vres(wiimotes[0],1024,768); //On définit l'espace infrarouge a (0->640 ; 0->480)

    ecran=SDL_SetVideoMode(1024,768,32,SDL_HWSURFACE);


    sur1=SDL_CreateRGBSurface(SDL_HWSURFACE,10,10,32,0,0,0,0); //Notre carre 10*10 (rouge)
    SDL_FillRect(sur1,NULL,SDL_MapRGB(sur1->format,255,0,0));
    //sur2=SDL_CreateRGBSurface(SDL_HWSURFACE,10,10,32,0,0,0,0);
    //SDL_FillRect(sur2,NULL,SDL_MapRGB(sur2->format,0,255,0));

    while(continuer)
    {

        SDL_PollEvent(&event); //PollEvent pour ne pas bloquer, car les events Wiimote sont independents de "event"
        if(event.type==SDL_QUIT) //Si on appuie sur la croix on quitte
            continuer=false;
        if(wiiuse_poll(wiimotes,1)) //Si on detecte un event sur l'une des Wiimote
        {

            pos1.x=wiimotes[0]->ir.dot[0].x-sur1->w/2; //On modifie les coordonnees du carre en fonction de l'infrarouge
            pos1.y=wiimotes[0]->ir.dot[0].y-sur1->h/2;

        if(IS_HELD(wiimotes[0],WIIMOTE_BUTTON_HOME)) //Si on appuie sur HOME on quitte
          continuer=false;

        }

        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        SDL_BlitSurface(sur1,NULL,ecran,&pos1);
	      SDL_BlitSurface(sur2,NULL,ecran,&pos2);
        SDL_Flip(ecran);
        SDL_Delay(10);

        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 30)
        {
        printf("IR z distance: %f\n", wiimotes[0]->ir.z);
        tempsPrecedent=tempsActuel;
        }

}

    SDL_FreeSurface(ecran);
    SDL_FreeSurface(sur1);
    SDL_FreeSurface(sur2);
    SDL_Quit();


    wiiuse_disconnect(wiimotes[0]); //On deconnecte la premiere Wiimote

    return EXIT_SUCCESS;
}
