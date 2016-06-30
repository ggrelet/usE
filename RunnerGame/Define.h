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

#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

//library SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#include <wiiuse.h>

//autres librairies
#include <string>
#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>




//nom de notre Programme
const std::string programName="Runner Game";

//taille
const int WIDTH=1024;
const int HEIGHT=768;

//vision
const float RATIO= (float)WIDTH/(float)HEIGHT;
const float PRET= 0.1;
const float LOIN=10000.0;
const float ANGLE_VISION=45.0;


//on doit initialiser le nombre maximal de wiimotes qu'on veut (une seule pour nous -> sera directement la camera de notre telephone par la suite)
const int MAX_WIIMOTE = 1;

#endif /* Define_h */
