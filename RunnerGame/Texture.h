//
//  Texture.h
//  PROJET_IGR202
//
//  Created by Etcheverry Mayalen on 30/01/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#ifndef Texture_h
#define Texture_h


#endif /* Texture_h */


#include "Define.h"


class Texture
{
public:
    
    Texture(std::string fichierImage);
    ~Texture();
    void charger();
    GLuint getID() const;
    void setFichierImage(const std::string &fichierImage);
    
    
private:
    
    GLuint m_id;
    std::string m_fichierImage;
};


