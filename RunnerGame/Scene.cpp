//
//  Scene.cpp
//  RunnerGame
//
//  Created by Etcheverry Mayalen on 07/06/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#include "Scene.h"
using namespace std;
#define MAX_WIIMOTE 1

Scene::Scene(string titreFenetre, int largeurFenetre, int hauteurFenetre):m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0) {


    personnage = new Personnage(chemin+"data/perso.rtf");
    
    //initialisation objets
    for (int i=0; i<6; i++) {
        objets[i] = *new Personnage();
    }

      objets[0] = *new Personnage(-0.5,-10,-0.5,0,0,1,1,1,Vec4f(1.0f,0.0f,0.0f,1.0f),Vec4f(0.4f,0.4f,0.4f,1.0f), 20.0f, chemin+"data/cone.rtf");
    objets[1] = *new Personnage(0.5,-5,0.3,0,0,0.7,1,0.7,Vec4f(1.0f,0.0f,0.0f,1.0f),Vec4f(0.4f,0.4f,0.4f,1.0f), 20.0f, chemin+"data/cone.rtf");
    objets[2] = *new Personnage(-0.5,-15,0,0,0,1,1,1,Vec4f(1.0f,0.0f,0.0f,1.0f),Vec4f(0.4f,0.4f,0.4f,1.0f), 20.0f, chemin+"data/cone.rtf");
    objets[3] = *new Personnage(0.5,0,7,0,0,1,1,1,Vec4f(1.0f,0.0f,0.0f,1.0f),Vec4f(0.4f,0.4f,0.4f,1.0f), 20.0f, chemin+"data/cone.rtf");
    objets[4] = *new Personnage(0,0,0,0,0,30,10,30,Vec4f(0.6f,0.6f,0.95f,1.0f),Vec4f(0.0f,0.0f,0.0f,1.0f),100.0f,chemin+"data/tunnellight.rtf");
    objets[5] = *new Personnage(0,30,0,0,0,10,1,10,Vec4f(1.0f,1.0f,1.0f,1.0f),Vec4f(0.0f,0.0f,0.0f,1.0f),100.0f,chemin+"data/fond.rtf");
;


}

Scene::~Scene() {
    SDL_GL_DeleteContext(m_contexteOpenGL);

    SDL_DestroyWindow(m_fenetre);

    SDL_Quit();

}



//initialisation de SDL2
bool Scene::initSDL2()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Failed to init SDL\n"<<endl;
        SDL_Quit();
        return false;
    }

    // Create our window centered at WIDTHxHEIGHT resolution
    m_fenetre = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  WIDTH,HEIGHT, SDL_WINDOW_OPENGL);

    // Check that everything worked out okay
    if (m_fenetre==0)
    {
        cout << "Unable to create window\n";
        SDL_Quit();
        return false;
    }

    return true;

}

//initialisation d'openGL

bool Scene::initOpenGl()
{
    m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);
    if(m_contexteOpenGL==0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();

        return false;
    }



    // Activer le masquage des faces cachées
    glEnable( GL_CULL_FACE );
    glCullFace(GL_BACK); // Face cachées = faces arrières
    glFrontFace(GL_CCW); // Face avant = sens trigo //attention

    // Activation du Depth Buffer
    glDepthFunc (GL_LESS); // Specify the depth test for the z-buffer
    glEnable(GL_DEPTH_TEST);


    //fond noir
    glClearColor(0.0, 0.0, 0.0, 0.0);

    SDL_GL_SwapWindow(m_fenetre);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Définition de la zone visible
    gluPerspective(ANGLE_VISION, RATIO, PRET, LOIN);

    return true;
}




void Scene::executer()
{
    initSDL2();
    initOpenGl();
    SDL_Event evenement;

int tempsPrecedent = 0, tempsActuel = 0;
    int z2 = 0;
    while (continuer) {
        SDL_PollEvent(&evenement);
        if(evenement.type==SDL_QUIT) continuer=false;
    

#ifndef __APPLE__
    pthread_mutex_lock(&lock);
    int x = pos.x;
    int y = pos.y;
    int z1 = pos.z1;
    pthread_mutex_unlock(&lock);

        if (x > 768){

            personnage->posAvant=personnage->posApres;
            personnage->posApres="gauche";
            personnage->deplacement();
            }

        if (x < 256){
          personnage->posAvant=personnage->posApres;
          personnage->posApres="droite";
          personnage->deplacement();
          }

        if (y < 192){
          personnage->posAvant=personnage->posApres;
          personnage->posApres="haut";
          personnage->deplacement();
          }

        if (y > 576){
          personnage->posAvant=personnage->posApres;
          personnage->posApres="bas";
          personnage->deplacement();
          }

        if (y < 576 && y > 192 && x < 768 && x > 256 ){
            personnage->posAvant=personnage->posApres;
            personnage->posApres="neutre";
            personnage->deplacement();
            }
#endif


    tempsActuel = SDL_GetTicks();

    if (tempsActuel - tempsPrecedent > 20) /* Si 30 ms se sont écoulées */
    {
        #ifndef __APPLE__
        if (z1-z2 > 20 || z2-z1 > 20){
        personnage->avancer(0.1);
        z2 = z1;
        }
        #endif
        
        #ifdef __APPLE__
        personnage->avancer(0.1);
        #endif
      gererEvenements();
      dessiner();
      afficher();
      tempsPrecedent=tempsActuel;
    }
  }
}


void Scene::gererEvenements(void)
{
    SDL_Event evenement;


    while (SDL_PollEvent(&evenement))
    {
        switch(evenement.type)
        {
            case SDL_QUIT:
                continuer = false;
                break;
            case SDL_KEYDOWN:
                switch (evenement.key.keysym.scancode)
            {
                case SDL_SCANCODE_ESCAPE:
                    continuer = false;
                    break;
                case SDL_SCANCODE_Z: //va savoir pourquoi c'est W?
                    GLint mode[2];
                    glGetIntegerv (GL_POLYGON_MODE, mode);
                    glPolygonMode (GL_FRONT_AND_BACK, mode[1] ==  GL_FILL ? GL_LINE : GL_FILL);
                    break;
                case SDL_SCANCODE_UP:
                    //personnage->avancer(0.5);
                    personnage->posAvant=personnage->posApres;
                    personnage->posApres="haut";
                    personnage->deplacement();
                    break;
                case SDL_SCANCODE_DOWN:
                    //personnage->avancer(-0.5);
                    personnage->posAvant=personnage->posApres;
                    personnage->posApres="bas";
                    personnage->deplacement();
                    break;
                case SDL_SCANCODE_RIGHT:
                    //personnage->tournerHorizontalement(-10.0);
                    personnage->posAvant=personnage->posApres;
                    personnage->posApres="droite";
                    personnage->deplacement();
                    break;
                case SDL_SCANCODE_LEFT:
                    //personnage->tournerHorizontalement(10.0);
                    personnage->posAvant=personnage->posApres;
                    personnage->posApres="gauche";
                    personnage->deplacement();

                    break;
                case SDL_SCANCODE_P:
                    //personnage->tournerVerticalement(10.0);
                    personnage->posAvant=personnage->posApres;
                    personnage->posApres="neutre";
                    personnage->deplacement();

                    break;
                case SDL_SCANCODE_SEMICOLON:
                    personnage->tournerVerticalement(-10.0);

                default:
                    break;
            }

            case SDL_MOUSEBUTTONDOWN:
                break;
            default:
                break;

        }

    }

}

void Scene::dessiner(){
    // Vidage de l'écran
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Place la camera
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    personnage->regarder();

    dessinerObjets();

}

void Scene::dessinerObjets(){

    for (int i=0; i<6; i++) {
        objets[i].afficher();
    }

}

void Scene::afficher(){

    SDL_GL_SwapWindow(m_fenetre);


}
