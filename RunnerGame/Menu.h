//
//  Menu.h
//  RunnerGame
//
//  Created by Etcheverry Mayalen on 04/07/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#ifndef Menu_h
#define Menu_h

#include "Define.h"
#include "Texture.h"

class Menu {
private:
    //Surfaces pour le menu
    std::string m_name;
    Texture *texture;
    SDL_Rect positions[5];
    
    public:
    //Constructeur
    Menu(std::string imagename);
    //Destructeur
    ~Menu();
    
    //init car on charge les textures apres la fenetre 
    void init(void);
    //Gestion du clic
    void clic(int x, int y);
    
    //Gestion du clavier
    bool clavier(unsigned char k);
    
    //Fonction d'affichage
    void affiche(void);
};


#endif /* Menu_h */
