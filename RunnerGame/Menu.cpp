
#include "Menu.h"

using namespace std;



Menu::Menu(string imagename): m_name(imagename){
    texture = new Texture(m_name);
    };

//Constructeur

Menu::~Menu()
{

}

void Menu::init() {
    texture->charger();

    // menu
    positions[0].x = 0;
    positions[0].y = 0;
    positions[0].w = WIDTH;
    positions[0].h = HEIGHT;

    //titre
    positions[1].x = 0;
    positions[1].y = 0;
    positions[1].w = 0;
    positions[1].h = 0;

    //"Nouveau"
    positions[2].x = 0;
    positions[2].y = 0;
    positions[2].w = 0;
    positions[2].h = 0;

    //"Quitter"
    positions[3].x = 0;
    positions[3].y = 0;
    positions[3].w = 0;
    positions[3].h = 0;

    //"Continuer"
    positions[3].x = 0;
    positions[3].y = 0;
    positions[3].w = 0;
    positions[3].h = 0;


}

//Gestion du clic
void Menu::clic(int x, int y)
{
    //Est-ce qu'on est dans le bouton nouveau?
    if((positions[2].x<x)&&(positions[2].x+positions[2].w>x)&&(positions[2].y<y)&&(positions[2].y+positions[2].h>y))
    {
       // moteur.initJeu();
       // moteur.echangeFonctions();
    }
    //Est-ce qu'on est dans le bouton positions[3]?
    else if((positions[3].x<x)&&(positions[3].x+positions[3].w>x)&&(positions[3].y<y)&&(positions[3].y+positions[3].h>y))
    {
        //moteur.fin();
    }
}

//Gestion du clavier
bool Menu::clavier(unsigned char k)
{
    switch(k)
    {
        case 'c':
            //moteur.echangeFonctions();
            return true;
        case 'n':
            //moteur.initJeu();
            //moteur.echangeFonctions();
            return true;
        default:
            return false;
    }
}

//Fonction d'affichage
void Menu::affiche()
{
    gluLookAt(0,-1,0,0,0,0,0,0,1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);


    glColor4f(1.0,1.0,1.0,0.0);

        glBindTexture(GL_TEXTURE_2D, texture->getID());
        glBegin(GL_QUADS);

        glTexCoord2i(0,0);
        glVertex3f(-1,0,-1);

        glTexCoord2i(1,0);
        glVertex3f(1,0,-1);

        glTexCoord2i(1,1);
        glVertex3f(1,0,1);

        glTexCoord2i(0,1);
        glVertex3f(-1,0,1);
        glEnd();


    glDisable(GL_TEXTURE_2D);

}
