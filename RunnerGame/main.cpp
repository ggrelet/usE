//
//  main.cpp
//  RunnerGame
//
//  Created by Etcheverry Mayalen on 02/06/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#include "Define.h"
#include "Scene.h"
#include "Mat4.h"

using namespace std;

//VARIABLES GLOBALES:

int main( int argc, char* argv[] )
{
    Scene scene(programName,WIDTH,HEIGHT);

    scene.executer();
    
    
    return 0;
}



