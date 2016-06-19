//
//  Scene.h
//  RunnerGame
//
//  Created by Etcheverry Mayalen on 07/06/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#ifndef Scene_h
#define Scene_h

#include "Define.h"
#include "Mat4.h"
#include "Texture.h"
#include "Personnage.h"

class Scene
{
private:
    //< Key,Value> Key: on utilisera un string pour distinguer nos textures(plus intuitif) -- map values: contenu associe a la clé (GluInt utilisé par openGL pour referencer ses textures)
    //agit comme un tableau dynamique: Textures[identifiant sous forme de string]=valeur
    

    bool continuer;
    Personnage *personnage;
    
    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;
    
    
    SDL_Window* m_fenetre;
    SDL_GLContext m_contexteOpenGL;
    SDL_Event m_evenements;
   
    void gererEvenements(void);
    void animer(void);
    void dessiner(void);
    void afficher(void);
    void dessinerSkybox(void);
    void dessinerObjets(void);
    
public:
    Scene(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    bool initOpenGl();
    bool initSDL2();
    ~Scene();
    void executer();
};

#endif /* Scene_h */
