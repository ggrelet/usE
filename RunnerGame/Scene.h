//
//  Scene.h
//  RunnerGame
//
//  Created by Etcheverry Mayalen on 07/06/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#ifndef Scene_h
#define Scene_h

#include "Personnage.h"
#include "Menu.h"
#include "Rand.h"


class Scene
{
private:
    bool est_dans_accueil;
    bool est_dans_menu;
    bool est_dans_jeu;
    bool est_dans_gameOver;
    
    //Musique qui dure tout le jeu
    Mix_Music *musique; //
    Mix_Chunk *son; //son collision
    
    
    //score
    SDL_Rect position;
    SDL_Surface* ecran;
    SDL_Surface *texte; 
    TTF_Font *police;
    SDL_Color couleurNoire;
    int var=1;
    char b[20]="";
  
    

    //Menu
    Menu *menu;
    
    //gameOver
    Texture *gameOver;

    //jeu
    Personnage objets[11];
    Personnage *personnage;
    
    int positionsY[9];
    int pairs[5];
    int impairs[4];

    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;


    SDL_Window* m_fenetre;
    SDL_GLContext m_contexteOpenGL;
    SDL_Event m_evenements;

    void gererEvenements(void);
    void dessiner(void);
    void afficher(void);
    void dessinerSkybox(void);
    void dessinerObjets(void);
    void chargerTextures(void);
    void dessinerAccueil(void);
    void dessinerGameOver();

public:
    Scene(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    bool initOpenGl();
    bool initSDL2();
    bool initSDL_mixer();
    bool initSDL_ttf();
    ~Scene();
    void executer();
};

#endif /* Scene_h */
