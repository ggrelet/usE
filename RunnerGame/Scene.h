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

class Scene
{
private:
    bool est_dans_accueil;
    bool est_dans_menu;
    bool est_dans_jeu;
    Mix_Music *musique; // Musique qui dure tout le jeu


    //Menu
    Menu *menu;

    //jeu
    Personnage objets[11];
    Personnage *personnage;

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

public:
    Scene(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    bool initOpenGl();
    bool initSDL2();
    bool initSDL_mixer();
    ~Scene();
    void executer();
};

#endif /* Scene_h */
