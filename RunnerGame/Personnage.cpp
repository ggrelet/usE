//
//  Personnage.cpp
//  RunnerGame
//
//  Created by Etcheverry Mayalen on 14/06/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#include "Personnage.h"

Personnage::Personnage(float posX, float posY, float posZ, float angleHorizontal,float angleVertical, float scaleX, float scaleY, float scaleZ, Vec4f Kd, Vec4f Ks, float eclairage, std::string fileName):posX(posX),posY(posY),posZ(posZ),angleHorizontal(angleHorizontal),angleVertical(angleVertical), scaleX(scaleX), scaleY(scaleY),scaleZ(scaleZ), Kd(Kd),Ks(Ks), eclairage(eclairage) {
    supermesh.loadOBJ(fileName);
    posApres="neutre";
    posAvant="neutre";
}

Personnage::~Personnage(){

}

void Personnage::deplacement(void) {
  if (posAvant=="neutre") {
      if (posApres=="droite") {
            posX = 0.5f;
        }

        else if (posApres=="gauche") {
              posX = -0.5f;
          }

          else if (posApres=="haut") {
                posZ = 0.5f;
            }

            else if (posApres=="bas") {
                  posZ = -0.5f;
              }

  }

      if (posAvant=="droite") {
          if (posApres=="neutre") {
                posX = 0.0f;
            }

            else if (posApres=="gauche") {
                  posX = -0.5f;
              }

              else if (posApres=="haut") {
                    posZ = 0.5f;
                }

                else if (posApres=="bas") {
                      posZ = -0.5f;
                  }

  }

      if (posAvant=="gauche") {
          if (posApres=="neutre") {
                posX = 0.0f;
            }

            else if (posApres=="droite") {
                  posX = 0.5f;
              }

              else if (posApres=="haut") {
                    posZ = 0.5f;
                }

                else if (posApres=="bas") {
                      posZ = -0.5f;
                  }

  }

      if (posAvant=="haut") {
          if (posApres=="neutre") {
                posZ = 0.5f;
            }

            else if (posApres=="droite") {
                  posX = 0.5f;
              }

              else if (posApres=="gauche") {
                    posX = -0.5f;
                }

                else if (posApres=="bas") {
                      posZ = -0.5f;
                  }

      }

          if (posAvant=="bas") {
              if (posApres=="neutre") {
                    posZ = 0.0f;
                }

                else if (posApres=="droite") {
                      posX = 0.5f;
                  }

                  else if (posApres=="gauche") {
                        posX = -0.5f;
                    }

                    else if (posApres=="haut") {
                          posZ = 0.5f;
                      }

          }

}

void Personnage::avancer(float distance){
    //if (posY<30.0f)
    posY += distance ;
    //else posY = -30.0f;

}

void Personnage::tournerHorizontalement(float angle){

    angleHorizontal+=angle; //doit rester entre -180 et 180

    while (this->angleHorizontal >= 180.0) // Lorsqu'on dépasse la limite (1/2 tour)
    {
        this->angleHorizontal -= 360.0;
    }
    while (this->angleHorizontal < -180.0) // Idem après 1/2 tours vers la droite
    {
        this->angleHorizontal += 360.0;
    }

}

void Personnage::tournerVerticalement(float angle)
{
    angleVertical += angle;

    if (45.0f < angleVertical)
    {
        angleVertical = 45.0f;
    }
    else if (-45.0f > this->angleVertical)
    {
        angleVertical = -45.0f;
    }
}

void Personnage::afficher(void){
   // On mémorise le repère courant avant d'effectuer la RST
    glPushMatrix();

    // Positionne l'objet en lieu de dessin
    glTranslatef(posX, posY, 0.0);
    glRotated(angleHorizontal, 0.0, 0.0, 1.0);

    glScaled(scaleX, scaleY, scaleZ);



        Vec4f position;
        Vec4f normale;


        Vec4f ligthPos1(0.0f,5.0f,0.0f,1.0f);
        Vec4f ligthPos2(0.0f,-1.0f,0.0f,1.0f);

        Vec4f fd = 3.0f * Kd / 3.14;
        float s= 10.0f;

        for (int g=0; g<supermesh.meshes.size();g++){
            glBindTexture(GL_TEXTURE_2D, 0);

            glBegin (GL_TRIANGLES);
            for (unsigned int i = 0; i < supermesh.meshes[g].T.size(); i++) {


                for (unsigned int j = 0; j < 3; j++) {
                    const Vertex & v = supermesh.meshes[g].V[supermesh.meshes[g].T[i].ve[j]];


                    Vec4f l1 = normalize (ligthPos1 - v.p);
                    Vec4f r1 =  l1 - 2.0f * dot(v.n, l1) * v.n;

                    Vec4f l2 = normalize (ligthPos2 - v.p);
                    Vec4f r2 = l2 - 2.0f * dot(v.n, l1) * v.n;


                    Vec4f w0 = normalize (-v.p);


                    //BLIN-PHONG:



                    Vec4f fs1=Ks*pow(dot(r1,w0),s);
                    Vec4f fs2=Ks*pow(dot(r2,w0),s);

                    Vec4f L1 = Vec4f(1.0f,1.0f,1.0f,1.0f);
                    Vec4f L2 = Vec4f(1.0f,1.0f,1.0f,1.0f);


                    Vec4f color1 = eclairage*10*L1*(fd+fs1)*(fmax(dot(v.n,l1),0.0f)) ;
                    Vec4f color2 = eclairage*L2*(fd+fs2)*(fmax(dot(v.n,l2),0.0f)) ;



                    Vec4f color = (color1 + color2);

                    position =  v.p;
                    normale = v.n;

                    glColor4f(color[0],color[1],color[2],1.0f);
                    //glColor3f(1, 1,1);
                    //glTexCoord2f(v.vt[0], v.vt[1]);
                    glNormal3f (normale[0], normale[1], normale[2]);
                    glVertex3f (position[0], position[1], position[2]);
                }
            }
            glEnd ();

            glBegin (GL_QUADS);
            for (unsigned int i = 0; i < supermesh.meshes[g].S.size(); i++) {
                for (unsigned int j = 0; j < 4; j++) {
                    glColor4f(1.0,0.0,0.0,0.2);
                    const Vertex & v = supermesh.meshes[g].V[supermesh.meshes[g].S[i].v[j]];

                    Vec4f l1 = normalize (ligthPos1 - v.p);
                    Vec4f r1 =  l1 - 2.0f * dot(v.n, l1) * v.n;

                    Vec4f l2 = normalize (ligthPos2 - v.p);
                    Vec4f r2 = l2 - 2.0f * dot(v.n, l1) * v.n;


                    Vec4f w0 = normalize (-v.p);


                    Vec4f fs1=Ks*pow(dot(r1,w0),s);
                    Vec4f fs2=Ks*pow(dot(r2,w0),s);

                    Vec4f L1 = Vec4f(1.0f,1.0f,1.0f,1.0f);
                    Vec4f L2 = Vec4f(1.0f,1.0f,1.0f,1.0f);


                    Vec4f color1 = eclairage*10*L1*(fd+fs1)*(fmax(dot(v.n,l1),0.0f)) ;
                    Vec4f color2 = eclairage*L2*(fd+fs2)*(fmax(dot(v.n,l2),0.0f)) ;



                    Vec4f color = (color1 + color2);


                    position = v.p;
                    normale = v.n;

                    glColor4f(color[0],color[1],color[2],1.0f);
                    //glColor3f(1, 1,1);
                    //glTexCoord2f(v.vt[0], v.vt[1]);
                    glNormal3f (normale[0], normale[1], normale[2]);
                    glVertex3f (position[0], position[1], position[2]);
                }
            }
            glEnd ();
            glBindTexture(GL_TEXTURE_2D, 0);

        }

   glPopMatrix();

}

void Personnage::regarder(void)
{
    gluLookAt(posX, posY, posZ, posX-sin(angleHorizontal * M_PI/180), posY+cos(angleHorizontal*M_PI/180), posZ + tan(angleVertical*M_PI/180), 0, 0, 1);

   }
