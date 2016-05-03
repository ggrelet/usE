#ifndef H_JEU
#define H_JEU

//On va definir une classe Jeu
class Jeu;

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

#include "Define.h"

#include <math.h>
#include <vector>
#include <iostream>

#include "Objet.h"
#include "Rand.h"
#include "Physique.h"
#include "Moteur.h"

class Jeu
{
	private:
        //Les objets
		//std::vector<Objet> objets;
    Objet objets[3];

        //Pour la creation des balles
		unsigned int last;
    
        //Pour savoir si la partie est en cours
        bool jeuEnCours;
	
		//Initialisation des objets et des textures
		bool initObjets();
		bool initTextures();

	public:
		//Constructeur et Destructeur
		Jeu();
		~Jeu();

		//Initialisation de la classe
		bool init();

		//Afficher le jeu
		void affiche();
		void affObjets();

    //Gere la scene (mise a jour)
    void gereSceneServeur();
    
    void gereDeplacement(int y, int y2);
    
    //Gestion du clavier
    bool clavier(unsigned char);
    
    //Recommence la partie
    void recommence();
    
    //Est-ce que le jeu est en cours
    bool enCours();
    
    //Mis a jour du temps pour les objets
    void toucheObjets();

};
#endif
