
/*
Un pong en SDL/OpenGL
A pong in SDL/OpenGL
Copyright (C) 2006 BEYLER Jean Christophe

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "Jeu.h"

using namespace std;


//Variable globale
extern Moteur moteur;

//Constructeur
Jeu::Jeu()
{
    last = 0;
    jeuEnCours = true;
    Objet o;
    objets[0]=o;
    objets[1]=o;
    objets[2]=o;
    
}	

//Destructeur
Jeu::~Jeu()
{
}

bool Jeu::initTextures()
{
    int k;
    GLuint txtsurf;
    
    
    SDL_Surface *tmpsurf;
    
    for(k=0;k<2;k++)
    {
        
        if(k==0)
        {
            string fichier="data/balle.png";
            //On charge l'image "data/balle.bmp"
            tmpsurf = IMG_Load(fichier.c_str());
        }
        else
        {
            //On charge l'image "data/barre.bmp"
            tmpsurf = IMG_Load("data/barre.png");
        }
        
        if(tmpsurf==0)
        {std::cout << "Erreur : " << SDL_GetError() << std::endl;}
        
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
            std::cout << "Erreur, format interne de l'image inconnu" << std::endl;
            SDL_FreeSurface(tmpsurf);
        }

            
        
        //On passe la texture a OpenGL
        
        //Generation d'un indice de texture
        glGenTextures(1,&txtsurf);
        
        //On choisit la texture et on definit un simple filtre pour la texture
        glBindTexture(GL_TEXTURE_2D,txtsurf);
        /*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);*/
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
        //Chargement de l'image
        glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, tmpsurf->w, tmpsurf->h, 0, format, GL_UNSIGNED_BYTE, tmpsurf->pixels);
        
        //Liberation des surfaces
        SDL_FreeSurface(tmpsurf);
        
        if(k==0)
        {
            //On passe la texture aux objets de type balle
            Objet::setTxtBalle(txtsurf);
        }
        else
        {
            //On passe la texture aux objets de type barre
            Objet::setTxtBarre(txtsurf);
        }
    }
    return true;
}


//Initialisation du jeu
bool Jeu::init()
{
    return initObjets() && initTextures() && Physique::init();
}

bool Jeu::initObjets()
{
   // objets.clear();
    return true;
}

//Recommence la partie
void Jeu::recommence()
{
    
    Physique::init();
    jeuEnCours = true;
    
    //C'est une barre et sans vitesse
     objets[0].setType(BARRE);
     objets[0].setVitesse(0);
     objets[0].setTaille(HAUT_BARRE,LARG_BARRE);
     objets[0].setPos(WIDTH/8-HAUT_BARRE/2,HEIGHT/2 -LARG_BARRE/2);
    
    
    objets[1].setType(BARRE);
    objets[1].setVitesse(0);
    objets[1].setTaille(HAUT_BARRE,LARG_BARRE);
    objets[1].setPos(7*WIDTH/8-HAUT_BARRE/2,HEIGHT/2 -LARG_BARRE/2);
    
    //balle
    
    objets[2].setType(CERCLE);
    
    // Definit la position (milieu de l'ecran)
    objets[2].setPos(WIDTH/2-TAILLE_BALLE, HEIGHT/2-TAILLE_BALLE);
    
    // Choisit aleatoirement une direction (refusant un 0 pour vx ou vy)
    int vx = Rand::randi(5000) - 2500;
    if(vx == 0)
        vx++;
    int vy = Rand::randi(5000) - 2500;
    if(vy == 0)
        vy++;
    objets[2].setDirVitesse(vx,vy);
    
    // On definit une norme de 4 pour la vitesse
    objets[2].setVitesse(4);
    objets[2].setTaille(TAILLE_BALLE,TAILLE_BALLE);
    
}


void Jeu::affiche()
{
    affObjets();
}

void Jeu::affObjets()
{
    unsigned int i;

    for(i=0;i<3;i++)
    {
        objets[i].affiche();
    }
}


void Jeu::gereSceneServeur()
{
    Physique::updateObjets(objets);
}

void Jeu::gereDeplacement(int y, int y2){
    objets[0].setPos(objets[0].getX(),y);
    objets[1].setPos(objets[1].getX(),y2);
}

//Gestion du clavier
bool Jeu::clavier(unsigned char k)
{
    switch(k)
    {
            //On veut voir le menu
        case 'q':
            moteur.echangeFonctions();
            return true;
        /*case 'z':
            objets[0].deplacementHaut();
            return true;
        case 's':
            objets[0].deplacementBas();
            return true;
        case 'p':
            objets[1].deplacementHaut();
            return true;
        case 'm':
            objets[1].deplacementBas();
            return true;*/
        default:
            return false;
    }
}

//Est-ce que le jeu est en cours ?
bool Jeu::enCours()
{
    return jeuEnCours;
}

void Jeu::toucheObjets()
{
    unsigned int i;
    for(i=0;i<3;i++)
    {
        objets[i].setDernierTps();
    }
}

