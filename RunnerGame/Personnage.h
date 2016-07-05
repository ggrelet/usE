//
//  Personnage.h
//  RunnerGame
//
//  Created by Etcheverry Mayalen on 14/06/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#ifndef Personnage_h
#define Personnage_h

#include "SuperMesh.h"

class Personnage {

public:
    float posX;
    float posY;
    float posZ;
    float angleHorizontal;
    float angleVertical;
    float scaleX;
    float scaleY;
    float scaleZ;
    Vec4f Kd;
    Vec4f Ks;
    float eclairage;
    std::string posAvant;
    std::string posApres;

    SuperMesh supermesh;

    inline Personnage() {
        posX = 0.0f;
        posY = 0.0f;
        posZ = 0.0f;
        angleHorizontal = 0.0f;
        angleVertical = 0.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        scaleZ = 1.0f;
        Kd=Vec4f(1.0f,1.0f,1.0f,1.0f);
        Ks=Vec4f(1.0f,1.0f,1.0f,1.0f);
        eclairage=0.0f;
        posApres="neutre";
        posAvant="neutre";

    }

    inline Personnage(std::string fileName) {  // Initialisation des attributs
        posX = 0.0f;
        posY = -20.0f;
        posZ = 0.0f;
        angleHorizontal = 0.0f;
        angleVertical = 0.0f;
        scaleX = 1.0f;
        scaleY = 1.0f;
        scaleZ = 1.0f;
        Kd=Vec4f(1.0f,1.0f,1.0f,1.0f);
        Ks=Vec4f(1.0f,1.0f,1.0f,1.0f);
        eclairage=0.0f;
        posApres="neutre";
        posAvant="neutre";


        supermesh.loadOBJ(fileName);
    };

    Personnage(float posX, float posY, float posZ, float angleHorizontal,  float angleVertical,float scaleX, float scaleY, float scaleZ, Vec4f Kd, Vec4f Ks,float eclairage, std::string fileName);
    ~Personnage();
    void avancer(float distance);
    void tournerHorizontalement(float angle);
    void tournerVerticalement(float angle);
    void deplacement(void);
    void afficher(void);
    void regarder(void);

};

#include <stdio.h>

#endif /* Personnage_h */
