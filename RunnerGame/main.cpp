//
//  main.cpp
//  RunnerGame
//
//  Created by Etcheverry Mayalen on 02/06/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//


#include "Scene.h"

 struct wii_pos pos;

 wiimote_t** wiimotes;
 pthread_mutex_t lock;

bool continuer = true;

using namespace std;


/* thread function */
void* my_func(void* arg) {

	while(continuer) {
		int x, y;

    if(wiiuse_poll(wiimotes,1)) //Si on detecte un event sur l'une des Wiimote
            {
      x=wiimotes[0]->ir.dot[0].x;
      y=wiimotes[0]->ir.dot[0].y;
      }

		pthread_mutex_lock(&lock);
		pos.x = x;
		pos.y = y;
		pthread_mutex_unlock(&lock);
	}
	return 0;
}

int main( int argc, char* argv[] )
{


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

  Scene scene(programName,WIDTH,HEIGHT);

    pthread_t tid;

    pthread_mutex_init(&lock, 0);
	pthread_create(&tid, 0, my_func, 0);

	scene.executer();

	pthread_join(tid, 0);



    return 0;
}


