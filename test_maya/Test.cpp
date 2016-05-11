//
//  Test.c
//  
//
//  Created by Etcheverry Mayalen on 24/05/2016.
//
//

//includes

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
//Bibliotheque SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Bibliotheque openGL
#define GLEW_STATIC 1
#ifdef __APPLE__
#include <OpenGL/gl.h>

#else
#include <GL/gl.h>
#endif

//Bibliotehque wiiuse
#include <wiiuse.h>

#define MAX_WIIMOTE 1

using namespace std;

//variables globales
string programName = "test usE";

// Our SDL_Window and context
SDL_Window *mainWindow;
SDL_GLContext mainContext;

int main(int argc,char **argv)
{
    
    SDL_Event event;
    
    // position initiale
    SDL_Rect pos1={100,100};
    bool continuer=true;
    
    
    wiimote_t** wiimotes;
    int found, connected;
    
    //On initialise la SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    
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
    
    // Create our mainWindow centered at 1024x768 resolution
    mainWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  1024, 768, SDL_WINDOW_OPENGL);
    // Create our opengl context and attach it to our window
    mainContext = SDL_GL_CreateContext(mainWindow);
    
    
    //------------------- Clear our buffer with a black background
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(mainWindow);

    //-------------------
    
    // Mettre le systeme de coordonnees a zero avant de modifier
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //Mettre la bonne perspective
    glOrtho(0,1064,768,0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    //------------------- Chargement de notre texture
    
    GLuint txtsurf;
    SDL_Surface *tmpsurf;
    
    //On charge l'image "data/balle.png"
    string fichier="balle.png";
    tmpsurf = IMG_Load(fichier.c_str());
    
    if(tmpsurf==0)
    {cout << "Erreur : " << SDL_GetError() << endl;}
    
    // Format de l'image
    GLenum formatInterne(0);
    GLenum format(0);
    
    
    // Détermination du format et du format interne pour les images à 3 composantes
    if(tmpsurf->format->BytesPerPixel == 3)
    {
        // Format interne
        
        formatInterne = GL_RGB;
        
        
        // Format
        
        if(tmpsurf->format->Rmask == 0xff)
            format = GL_RGB;
        
        else
            format = GL_BGR;
    }
    
    // Détermination du format et du format interne pour les images à 4 composantes
    
    else if(tmpsurf->format->BytesPerPixel == 4)
    {
        // Format interne
        formatInterne = GL_RGBA;
        
        
        // Format
        if(tmpsurf->format->Rmask == 0xff)
            format = GL_RGBA;
        
        else
            format = GL_BGRA;
    }
    
    
    // Dans les autres cas, on arrête le chargement
    else
    {
        cout << "Erreur, format interne de l'image inconnu" << endl;
        SDL_FreeSurface(tmpsurf);
    }
    
    //On passe la texture a OpenGL
    
    cout<<format<<endl;
    cout<<formatInterne<<endl;
    
    //Generation d'un indice de texture
    glGenTextures(1,&txtsurf);
    
    //On choisit la texture et on definit un simple filtre pour la texture
    glBindTexture(GL_TEXTURE_2D,txtsurf);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    
    
    //Chargement de l'image
    glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, tmpsurf->w, tmpsurf->h, 0, format, GL_UNSIGNED_BYTE, tmpsurf->pixels);
    
    //Liberation des surfaces
    SDL_FreeSurface(tmpsurf);

    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txtsurf);
    
    
    //------------------- Deroulement du jeu:

    
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
        
        //------------------- Affichage notre image de taille 30*30

        glBegin(GL_QUADS);
        glTexCoord2i(0.0,0.0);
        glVertex3f(pos1.x,pos1.y,0);
        glTexCoord2i(1.0,0.0);
        glVertex3f(pos1.x+100,pos1.y,0);
        glTexCoord2i(1.0,1.0);
        glVertex3f(pos1.x+100,pos1.y+100,0);
        glTexCoord2i(0.0,1.0);
        glVertex3f(pos1.x,pos1.y+100,0);
        glEnd();
        

        SDL_Delay(10);
        SDL_GL_SwapWindow(mainWindow);
    }
        
   //------------------- Cleanup
    
    glDisable(GL_TEXTURE_2D);
    
    // Delete our OpengL context
    SDL_GL_DeleteContext(mainContext);
        
    // Destroy our window
    SDL_DestroyWindow(mainWindow);
        
    // Shutdown SDL 2
    SDL_Quit();

    //On deconnecte la premiere Wiimote
    /*wiiuse_disconnect(wiimotes[0]);*/
    
    return EXIT_SUCCESS;
}

    
    
    

