// C++ Headers
#include <string>
#include <iostream>

#include "Moteur.h"
#include "Objet.h"
#include "Rand.h"

#include "Define.h"


// SDL2 Headers
#include <SDL2/SDL.h>

//
double y = 0.0;
double y2 = 0.0;
wiimote_t** wiimotes;



//namespace
using namespace std;

//Variables globales
Moteur *moteur = new Moteur();

std::string programName = "Jeu Pong usE";

// Our SDL_Window ( just like with SDL2 wihout OpenGL)
SDL_Window *mainWindow;

// Our opengl context handle = structure that keeps track of all of our resources (every thing we want to put on the screen) and connected to the mainWindox
SDL_GLContext mainContext; 

bool SetOpenGLAttributes();
void PrintSDL_GL_Attributes();
void CheckSDLError(int line);
void Idle();
void RunGame();
void Cleanup();



bool Init()
{
    
    int found, connected;
    
    
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to init SDL\n";
        return false;
    }
    
    // Create our window centered at WIDTHxHEIGHT resolution
    mainWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    
    // Check that everything worked out okay
    if (!mainWindow)
    {
        std::cout << "Unable to create window\n";
        CheckSDLError(__LINE__);
        return false;
    }
    
    // initialisation wiimotes
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
    SDL_Delay(400);
    wiiuse_rumble(wiimotes[0],0);
    wiiuse_set_ir(wiimotes[0],1); //On active l'infrarouge pour la premiere Wiimote
    wiiuse_set_ir_vres(wiimotes[0],1024,768); //On définit l'espace infrarouge a (0->640 ; 0->480)

    
    // Create our opengl context and attach it to our window
    mainContext = SDL_GL_CreateContext(mainWindow);
    
    SetOpenGLAttributes();
    
    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);
    
    // Init GLEW
    /*#ifndef __APPLE__
    glewInit();
    #endif*/
return true;
}


bool SetOpenGLAttributes()
{
    // Set our OpenGL version.
    // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    
    // Turn on double buffering =we draw to a hidden “screen” and when we are done we swap the buffer we drew on with the buffer on the screen so that it becomes visible
    // /!\ Double buffering with a 24bit Z buffer You may need to change this to 16 or 32 for your system
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    return true;
}

int main(int argc, char *argv[])
{
    if (!Init())
        return -1;
       
    // Clear our buffer with a black background
    // This is the same as :
    // 		SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
    // 		SDL_RenderClear(&renderer);
    //
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(mainWindow);
    
    // Mettre le systeme de coordonnees a zero avant de modifier
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //Mettre la bonne perspective
    glOrtho(0,WIDTH,HEIGHT,0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
   
    RunGame();
    
    
    Cleanup();
     
    return 0;
}

void RunGame()
{
    int fps, last, now;
    bool loop = true;
    unsigned int checkTime;
    const unsigned int wantedfps = 35; //nombre d'image par secondes qu'on veut
    
    //Initialisation du moteur
    printf("1\n");
    if(moteur->init()==false)
        loop=false;
    
    //Pour le calcul des FPS
    last = SDL_GetTicks()/1000;
    fps = 0;
    
    //Pour le taux de rafraichissement
    checkTime = SDL_GetTicks();
    
    SDL_Event event;
    
    //Boucle generale
   
    while (loop) {
      

      
      
      //Gerer les evenements
      while (SDL_PollEvent(&event)) {
	

	
	if(wiiuse_poll(wiimotes,1)){
	  //Si on detecte un event sur l'une des Wiimote
	  

          
	  //On modifie les coordonnees du carre en fonction de l'infrarouge
	  y=wiimotes[0]->ir.dot[0].y;
	  y2=wiimotes[0]->ir.dot[1].y;
	  if(IS_HELD(wiimotes[0],WIIMOTE_BUTTON_HOME)) //Si on appuie sur HOME on quitte
	    loop=false;
	}


	switch(event.type) {
	  
          
	case SDL_QUIT:
	  moteur->fin();
	  loop = false;
	  break;
	case SDL_KEYUP:
	  moteur->clavier(event.key.keysym.sym);
	  break;
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym) {
	  case SDLK_ESCAPE:
	    loop = false; //on sort du jeu si on appuie sur escape
	    break;
	  default:
	    break;
            
	  }
	  
	default:
	  break;
	}
      }

 
      if(SDL_GetTicks() > (checkTime + 1000 / wantedfps) ) {

	// On met a jour la variable checkTime
	checkTime = SDL_GetTicks();
        
	// On incremente la variable fps
	fps++;
	// Gerer l'affichage du fps
	now = time(NULL);

	if(now!=last) {
	  
	  cout << "FPS: " << fps/(now-last) << endl;
	  last = now;
	  fps = 0;
	}
	// Demander au moteur de dessiner la scene
	moteur->gereScene();
	moteur->gereDeplacement(y,y2);

	SDL_GL_SwapWindow(mainWindow);
      }
      else {
	// Attendre 5 millisecondes

	SDL_Delay(5);
      }
    }
}

void Cleanup()
{

    // Delete our OpengL context
    SDL_GL_DeleteContext(mainContext);
    
    // Destroy our window
    SDL_DestroyWindow(mainWindow);
    
    // Shutdown SDL 2
    SDL_Quit();
    
    wiiuse_disconnect(wiimotes[0]); //On deconnecte la premiere Wiimote
}

void CheckSDLError(int line = -1)
{
    std::string error = SDL_GetError();
    
    if (error != "")
    {
        cout << "SLD Error : " << error << std::endl;
        
        if (line != -1)
            cout << "\nLine : " << line << std::endl;
        
        SDL_ClearError();
    }
}

void PrintSDL_GL_Attributes()
{
    int value = 0;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
    cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;
    
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
    cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}
