
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

#include "Moteur.h"

//Constructeur
Moteur::Moteur()
{
  dans_menu = true; // on va directement dans le menu comme ca! 
  jeu = new Jeu();
  menu = new Menu();
}

//Destructeur
Moteur::~Moteur()
{
    delete jeu;
    delete menu;
}


void Moteur::gereScene()
{
	// Effacer le tampon des couleurs
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	if(!dans_menu){
	  dessineJeu();
	}
	else{
		dessineMenu();
	}
	//SDL_GL_SwapBuffers(); (mis dans le main?)
}

void Moteur::gereDeplacement(int y, int y2){
  
    jeu->gereDeplacement(y, y2);
}

void Moteur::dessineMenu()
{
     menu->affiche();
}

void Moteur::dessineJeu()
{
  
  jeu->affiche();
  jeu->gereSceneServeur();
}

bool Moteur::init()
{
	return jeu->init() && menu->init("data/menu.txt");;
}

void Moteur::clavier(unsigned char k)
{
    int gere=false;
    if(dans_menu)
    {
        gere = menu->clavier(k);
    }
    else
    {
        gere = jeu->clavier(k);
    }
    
    //Si la touche n'est pas geree
    if(!gere) {
        switch(k)
        {
                //On veut quitter
            case 'q':
                fin();
                break;
            default:
                break;
        }
    }
}

void Moteur::fin()
{
    est_fini = true;
}

bool Moteur::estFini()
{
    return est_fini;
}

//Echange entre menu et jeu
void Moteur::echangeFonctions()
{
    dans_menu = !dans_menu;
}

//Recommence la partie
void Moteur::initJeu()
{
    jeu->recommence();
}

//Est-ce que le jeu est en cours
bool Moteur::jeuEnCours()
{
    return jeu->enCours();
}

