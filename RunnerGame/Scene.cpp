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
    menu = new Menu(chemin + "Textures/go.jpg");
    
    personnage = new Personnage(chemin+"data/perso.rtf");
    
    //Tableau des positions possibles en Y pour l'aléatoire
    positionsY[0] = pairs[0] = -24;
    positionsY[1] = impairs[0] = -18;
    positionsY[2] = pairs[1] = -12;
    positionsY[3] = impairs[0] = -6;
    positionsY[4] = pairs[2] = 0;
    positionsY[5] = impairs[0] = 6;
    positionsY[6] = pairs[3] =12;
    positionsY[7] = impairs[0] = 18;
    positionsY[8] = pairs[4] =24;
    



    //initialisation objets
    for (int i=0; i<11; i++) {
        objets[i] = *new Personnage();
    }


    objets[0] = *new Personnage(-0.7,-24,-0.4,0,0,0.7,0.5,0.5,Vec4f(0.278f, 0.333f, 0.357f,1.0f),Vec4f(1.0f,0.0f,0.0f,1.0f), 15.0f,1.0f,0.1f, chemin + "data/cylindre.rtf");
    objets[1] = *new Personnage(0.7,-18,-1.7,0,0,0.6,0.8,0.8,Vec4f(0.239f,0.545f,0.914f,1.0f),Vec4f(1.0f,0.0f,0.0f,1.0f), 20.0f,1.0f,0.1f,  chemin+"data/cone.rtf");
    objets[2] = *new Personnage(-0.7,-12,0.3,0,0,0.4,0.4,0.4,Vec4f(0.157f,0.196f,0.357f,1.0f),Vec4f(0.0f,0.2f,1.0f,1.0f), 200.0f, 1.0f,0.1f, chemin+"data/sphere.rtf");
    objets[3] = *new Personnage(0.7,-6,7,0,0,0.6,0.5,0.6,Vec4f(0.820f,0.282f,0.255f,1.0f),Vec4f(0.0f,1.0f,0.4f,1.0f), 15.0f, 1.0f,0.1f, chemin+"data/cylindre.rtf");
    objets[4] = *new Personnage(-0.7,0,-0.4,0,0,0.4,0.4,0.4,Vec4f(0.921f,0.420f,0.337f,1.0f),Vec4f(1.0f,0.0f,0.0f,1.0f), 200.0f,1.0f,0.1f, chemin + "data/sphere.rtf");
    objets[5] = *new Personnage(0.7,6,-1.7,0,0,0.6,0.8,0.8,Vec4f(0.968f,0.855f,0.392f,1.0f),Vec4f(1.0f,0.0f,0.0f,1.0f), 20.0f,1.0f,0.1f,  chemin+"data/cone.rtf");
    objets[6] = *new Personnage(-0.7,12,0.3,0,0,0.4,0.4,0.4,Vec4f(0.980f,0.773f,0.110f,1.0f),Vec4f(0.0f,0.2f,1.0f,1.0f), 200.0f, 1.0f,0.1f, chemin+"data/sphere.rtf");
    objets[7] = *new Personnage(0.7,18,7,0,0,0.6,0.5,0.6,Vec4f(0.0f,0.659f,0.522f,1.0f),Vec4f(0.0f,1.0f,0.4f,1.0f), 15.0f, 1.0f,0.1f, chemin+"data/cylindre.rtf");
    objets[8] = *new Personnage(-0.7,24,7,0,0,0.6,0.5,0.6,Vec4f(0.0f,0.530f,0.522f,1.0f),Vec4f(0.0f,1.0f,0.4f,1.0f), 20.0f, 1.0f,0.1f, chemin+"data/cone.rtf");


    objets[9] = *new Personnage(0,0,0,0,0,6,30,6,Vec4f(0.235,0.27f,0.439f,1.0f),Vec4f(0.0f,0.0f,0.0f,1.0f),500.0f,1.0f,1.0f, chemin+"data/tunnellight.rtf");

    objets[10] = *new Personnage(0,30,0,0,0,10,1,10,Vec4f(1.0f,1.0f,1.0f,1.0f),Vec4f(0.0f,0.0f,0.0f,1.0f),100.0f,1.0f,1.0f, chemin+"data/fond.rtf");

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
    string cheminSon = chemin + "Musiques/su3.mp3";

    musique = Mix_LoadMUS(cheminMusique.c_str()); // Charger musique
    
    //Son en cas de collision
    Mix_Chunk *son; // Son épisodique
    son = Mix_LoadWAV(cheminSon.c_str()); // Charger le son
    //Mix_VolumeChunk(son, 128); // Volume (max)
    
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
                Mix_VolumeMusic (0); // Volume (~moyen)

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

        personnage->avancer(0.4);

        z2 = z1;
        }
        #endif


        #ifdef __APPLE__
        personnage->avancer(0.6);
        #endif
      dessiner();

      afficher();
      tempsPrecedent=tempsActuel;
        for (int i = 0 ; i<9 ; i++) {
            if (personnage->inCollisionWith(objets[i])) {
                est_dans_jeu = false;
                est_dans_menu = true;
                evenement.key.keysym.scancode=SDL_SCANCODE_LEFT;
                break;
            }
        }
      }
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
    
    if (niveau == 3) {
        for (int i=0; i<9; i++) {
            for (int j =0; j<3; j++) {
                objets[i].Kd[j] = Rand::randf();
            }
        }
    }
    int indice= 0;
    
    if (newNiveau) {
        for (int i=0; i<9; i++) {
            for (int j =0; j<3; j++) {
                objets[i].Kd[j] = Rand::randf();
            }
            
            indice=Rand::randi(9-i);
            int tmp=positionsY[8-i];
            positionsY[8-i] = positionsY[indice];
            positionsY[indice]=tmp;
            objets[i].posY = positionsY[8-i];
            }
            
    }
    
    for (int i=0; i<9; i++) {
        bool inPairs = std::find(std::begin(pairs), std::end(pairs), objets[i].posY) != std::end(pairs);
        if(inPairs){
           objets[i].posX = -0.7;
        }

        else {
            objets[i].posX = 0.7;
        }
    
    }
    
    for (int i=0; i<11; i++) {
        objets[i].afficher();
    }

}

void Scene::afficher(){
    SDL_GL_SwapWindow(m_fenetre);
}

void Scene::dessinerAccueil(){
        gluLookAt(0,-2,0,0,0,0,0,0,1);

        Texture *accueilImg = new Texture(chemin +"Textures/accueil.jpg");
        accueilImg->charger();

        glEnable(GL_TEXTURE_2D);

        //On dessine l'image de fond

        glBindTexture(GL_TEXTURE_2D, accueilImg->getID());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // On mémorise le repère courant avant d'effectuer la RST
    glPushMatrix();
    // Positionne l'objet en lieu de dessin
    glRotated(90.0, 0.0, 1.0, 0.0);
    glScaled(1, 1, 1.5);


        glColor4f(1.0,1.0,1.0,0.0);

        glBegin(GL_QUADS);
        glTexCoord2i(0,0);
        glVertex3f(-1,0,-1);
        glTexCoord2i(0,1);
        glVertex3f(1,0,-1);
        glTexCoord2i(1,1);
        glVertex3f(1,0,1);
        glTexCoord2i(1,0);
        glVertex3f(-1,0,1);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();

    }

//retourne un nombre aléatoire entre [0,1]

