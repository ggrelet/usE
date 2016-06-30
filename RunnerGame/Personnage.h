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
    
    
    SuperMesh supermesh;
    inline Personnage() {
        posX = 0.0f;
        posY = 0.0f;
        posZ = 0.0f;
        angleHorizontal = 0.0f;
        angleVertical = 0.0f;
        
    }
    
    inline Personnage(std::string fileName) {  // Initialisation des attributs
        posX = 0.0f;
        posY = 0.0f;
        posZ = 0.0f;
        angleHorizontal = 0.0f;
        angleVertical = 0.0f;
        
        supermesh.loadOBJ(fileName);
    };
    
    Personnage(float posX, float posY, float posZ, float angleHorizontal,  float angleVertical, std::string fileName);
    ~Personnage();
    void avancer(float distance);
    void tournerHorizontalement(float angle);
    void tournerVerticalement(float angle);
    void afficher(void);
    void regarder(void);
    
};

#include <stdio.h>

#endif /* Personnage_h */
