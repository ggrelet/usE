//
//  main.cpp
//  RunnerGame
//
//  Created by Etcheverry Mayalen on 02/06/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//


#include "Scene.h"



bool continuer = true;
int niveau = 0;
bool newNiveau = false; 

struct wii_pos pos;

using namespace std;
#ifndef __APPLE__

wiimote_t** wiimotes;
pthread_mutex_t lock;



void* my_func(void* arg) {

	while(continuer) {
		int x1, x2, x, y1 , y2, y, z1;


    if(wiiuse_poll(wiimotes,1)) //Si on detecte un event sur l'une des Wiimote
            {
      x1 = wiimotes[0]->ir.dot[0].x;
      x2 = wiimotes[0]->ir.dot[1].x;
      y1 = wiimotes[0]->ir.dot[0].y;
      y2 = wiimotes[0]->ir.dot[1].y;
      x=(x1+x2)/2;
      y=(y1+y2)/2;
      z1 = wiimotes[0]->ir.z;
      }

		pthread_mutex_lock(&lock);
		pos.x = x;
		pos.y = y;
    pos.z1 = z1;
		pthread_mutex_unlock(&lock);
	}
	return 0;
}

#endif

int main( int argc, char* argv[] )
{

#ifndef __APPLE__
  int found, connected;


  wiimotes=wiiuse_init(MAX_WIIMOTE); //On initialise la premiere Wiimote
  found = wiiuse_find(wiimotes, MAX_WIIMOTE,5);//On essaie de la trouver
  if (!found){
      fprintf(stderr,"Aucune Wiimote trouvee\n");

  }
  connected = wiiuse_connect(wiimotes, MAX_WIIMOTE);
  if(connected) {
        printf("connected to wiimote \n");
  } else {
   printf("Failed to connect to any wiimote\n");

  }

  wiiuse_set_leds(wiimotes[0],WIIMOTE_LED_1); //On fixe sa DEL a la position 1
  wiiuse_rumble(wiimotes[0],1); //On la fait vibrer pendant 400 ms
  SDL_Delay(200);
  wiiuse_rumble(wiimotes[0],0);
  wiiuse_set_ir(wiimotes[0],1); //On active l'infrarouge pour la premiere Wiimote
  wiiuse_set_ir_vres(wiimotes[0],1024,768); //On définit l'espace infrarouge a (0->1024 ; 0->768)*/
#endif


  Scene scene(programName,WIDTH,HEIGHT);

#ifndef __APPLE__

    pthread_t tid;

    pthread_mutex_init(&lock, 0);
    pthread_create(&tid, 0, my_func, 0);

	scene.executer();

	pthread_join(tid, 0);
#endif

#ifdef __APPLE__

    scene.executer();

#endif




    return 0;
}
