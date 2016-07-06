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
    est_dans_accueil = true;
    est_dans_menu = false;
    est_dans_jeu = false;
    menu = new Menu(chemin + "Textures/verre6.jpg");

    personnage = new Personnage(chemin+"data/perso.rtf");

    //initialisation objets
    for (int i=0; i<6; i++) {
        objets[i] = *new Personnage();
    }
    objets[0] = *new Personnage(0.7,-20,-0.4,0,0,0.7,0.5,0.5,Vec4f(1.0000f,0.5216f,0.1529f,1.0f),Vec4f(1.0f,0.0f,0.0f,1.0f), 10.0f,1.0f,1.0f, chemin + "data/cylindre.rtf");
    objets[1] = *new Personnage(-0.6,-10,-1.7,0,0,0.6,0.8,0.8,Vec4f(1.0000f,0.3922f,0.2745f,1.0f),Vec4f(1.0f,0.0f,0.0f,1.0f), 20.0f,1.0f,1.0f,  chemin+"data/cone.rtf");
    objets[2] = *new Personnage(0.5,0,0.3,0,0,0.4,0.4,0.4,Vec4f(0.0902f,0.3059f,0.9294f,1.0f),Vec4f(0.0f,0.2f,1.0f,1.0f), 200.0f, 1.0f,1.0f, chemin+"data/sphere.rtf");
    objets[3] = *new Personnage(-0.7,10,7,0,0,0.6,0.5,0.6,Vec4f(0.38f,0.98f,0.63f,1.0f),Vec4f(0.0f,1.0f,0.4f,1.0f), 10.0f, 1.0f,1.0f, chemin+"data/cylindre.rtf");


    objets[4] = *new Personnage(0,0,0,0,0,6,30,6,Vec4f(0.0902f,0.4196f,0.9294f,1.0f),Vec4f(0.0f,0.0f,0.0f,1.0f),100.0f,1.0f,1.0f, chemin+"data/tunnellight.rtf");
    objets[5] = *new Personnage(0,30,0,0,0,10,1,10,Vec4f(1.0f,1.0f,1.0f,1.0f),Vec4f(0.0f,0.0f,0.0f,1.0f),100.0f,1.0f,1.0f, chemin+"data/fond.rtf");


}

Scene::~Scene() {
    SDL_GL_DeleteContext(m_contexteOpenGL);

    SDL_DestroyWindow(m_fenetre);

    Mix_FreeMusic(musique); // Liberer les
    //Mix_FreeChunk(son);     //  pointeurs
    Mix_CloseAudio();

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

bool Scene::initSDL_mixer()
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }

    Mix_AllocateChannels(2); // Nombre de fichiers sonores


    
    string cheminMusique = chemin + "Musiques/musique2.mp3";

    musique = Mix_LoadMUS(cheminMusique.c_str()); // Charger musique

    //Mix_PlayMusic(musique, -1); // Jouer musique en boucle
    //Mix_VolumeMusic (50); // Volume (~moyen)

    /*   Son en cas de collision
    Mix_Chunk *son; // Son épisodique
    son = Mix_LoadWAV("Su3.wav"); // Charger le son
    Mix_VolumeChunk(son, 128); // Volume (max)
    */


    return true;
}


void Scene::executer()
{
    initSDL2();
    initOpenGl();
    initSDL_mixer();
    menu->init();
    SDL_Event evenement;

int tempsPrecedent = SDL_GetTicks(), tempsActuel = SDL_GetTicks(),tempsmvt = 0;
int z2 = 0;

    while (continuer) {

    SDL_PollEvent(&evenement);
    if(evenement.type==SDL_QUIT) continuer=false;


        if (est_dans_accueil) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode( GL_MODELVIEW );
            glLoadIdentity();

            dessinerAccueil();
            SDL_GL_SwapWindow(m_fenetre);
            SDL_Delay(2500);
            est_dans_accueil = false;
            est_dans_menu = true;
        }

        if (est_dans_menu) {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode( GL_MODELVIEW );
            glLoadIdentity();
            menu->affiche();
            SDL_GL_SwapWindow(m_fenetre);

            if(evenement.key.keysym.scancode==SDL_SCANCODE_UP) {
                    est_dans_menu = false;
                    est_dans_jeu= true;
                    Mix_PlayMusic(musique, -1); // Jouer musique en boucle
                    Mix_VolumeMusic (50); // Volume (~moyen)
                }
        }


       if(est_dans_jeu) {
tempsActuel = SDL_GetTicks();

    #ifndef __APPLE__
    pthread_mutex_lock(&lock);
    int x = pos.x;
    int y = pos.y;
    int z1 = pos.z1;
    pthread_mutex_unlock(&lock);

//tempsActuel = SDL_GetTicks();

        if (x > 768){
          personnage->posAvant=personnage->posApres;
          personnage->posApres="gauche";
          personnage->deplacement();
        }

        if (x < 256){
          personnage->posAvant=personnage->posApres;
          personnage->posApres="droite";
          personnage->deplacement();
          //dessiner();
          //afficher();
          /*personnage->posAvant=personnage->posApres;
          personnage->posApres="neutre";
          personnage->deplacement();
          dessiner();
          afficher();
        */}

        /*if (y < 92){
          personnage->posAvant=personnage->posApres;
          personnage->posApres="haut";
          personnage->deplacement();
          }

        if (y > 676){
          personnage->posAvant=personnage->posApres;
          personnage->posApres="bas";
          personnage->deplacement();
          }

        if (y < 576 && y > 192 && x < 768 && x > 256 ){
            personnage->posAvant=personnage->posApres;
            personnage->posApres="neutre";
            personnage->deplacement();
            }*/

#endif

    if (fabs(tempsActuel - tempsPrecedent) > 20) /* Si 30 ms se sont écoulées */
    {
        #ifndef __APPLE__
        if (z1-z2 > 20 || z2-z1 > 20){
        personnage->avancer(0.5);
        z2 = z1;
        }
        #endif

        #ifdef __APPLE__
        personnage->avancer(0.2);
        #endif
      //gererEvenements();
      dessiner();
      afficher();
      tempsPrecedent=tempsActuel;
    }
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
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    personnage->regarder();
    //gluLookAt(0, -30, 0, 0, 0, 0, 0, 0, 1);

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

void Scene::dessinerAccueil(){
        gluLookAt(0,-1,0,0,0,0,0,0,1);

        Texture *accueilImg = new Texture(chemin +"Textures/verre3.jpg");
        accueilImg->charger();

        glEnable(GL_TEXTURE_2D);

        //On dessine l'image de fond

        glBindTexture(GL_TEXTURE_2D, accueilImg->getID());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glColor4f(1.0,1.0,1.0,0.0);

        glBegin(GL_QUADS);
        glTexCoord2i(0,0);
        glVertex3f(-1,0,-1);
        glTexCoord2i(1,0);
        glVertex3f(1,0,-1);
        glTexCoord2i(1,1);
        glVertex3f(1,0,1);
        glTexCoord2i(0,1);
        glVertex3f(-1,0,1);
        glEnd();

        glDisable(GL_TEXTURE_2D);

    }
