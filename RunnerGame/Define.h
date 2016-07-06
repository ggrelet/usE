//
//  Define.h
//  RunnerGame
//
//  Created by Etcheverry Mayalen on 02/06/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#ifndef Define_h
#define Define_h

//library openGL
#define GLEW_STATIC 1
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL2_image/SDL_image.h>

#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL_image.h>

#endif

//library SDL2
#include <SDL2/SDL.h>

#ifndef __APPLE__
#include "wiiuse.h"
#endif


//autres librairies
#include <string>
#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <pthread.h>

const std::string chemin = "/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/FIRST/git_usE/RunnerGame/";

#ifndef __APPLE__
chemin="";
#endif
//const std::string chemin = "";

//nom de notre Programme
const std::string programName="Runner Game";

const int WIDTH=1084;
const int HEIGHT=768;
//taille
#ifndef __APPLE__
const int WIDTH=1920;
const int HEIGHT=1200;
#endif

//vision
const float RATIO= (float)WIDTH/(float)HEIGHT;
const float PRET= 0.1;
const float LOIN=10000.0;
const float ANGLE_VISION=45.0;


//on doit initialiser le nombre maximal de wiimotes qu'on veut (une seule pour nous -> sera directement la camera de notre telephone par la suite)
const int MAX_WIIMOTE = 1;

struct wii_pos {
	int x;
	int y;
	int z1;
};

extern struct wii_pos pos;

#ifndef __APPLE__
extern wiimote_t** wiimotes;
#endif

extern pthread_mutex_t lock;

extern bool continuer;

#endif /* Define_h */
