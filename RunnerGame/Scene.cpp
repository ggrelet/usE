//
//  Scene.cpp
//  RunnerGame
//
//  Created by Etcheverry Mayalen on 07/06/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#include "Scene.h"
using namespace std;
#define MAX_WIIMOTE 1

Scene::Scene(string titreFenetre, int largeurFenetre, int hauteurFenetre):m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0) {
    continuer = true;
    personnage = new Personnage("data/ball.rtf");

}


Scene::~Scene() {

    SDL_GL_DeleteContext(m_contexteOpenGL);

    SDL_DestroyWindow(m_fenetre);

    SDL_Quit();

}



//initialisation de SDL2
bool Scene::initSDL2()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Failed to init SDL\n"<<endl;
        SDL_Quit();
        return false;
    }

    // Create our window centered at WIDTHxHEIGHT resolution
    m_fenetre = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  WIDTH,HEIGHT, SDL_WINDOW_OPENGL);

    // Check that everything worked out okay
    if (m_fenetre==0)
    {
        cout << "Unable to create window\n";
        SDL_Quit();
        return false;
    }

    return true;

}

//initialisation d'openGL

bool Scene::initOpenGl()
{
    m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);
    if(m_contexteOpenGL==0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();

        return false;
    }



    // Activer le masquage des faces cachées
    glEnable( GL_CULL_FACE );
    glCullFace(GL_BACK); // Face cachées = faces arrières
    glFrontFace(GL_CCW); // Face avant = sens trigo //attention

    // Activation du Depth Buffer
    glDepthFunc (GL_LESS); // Specify the depth test for the z-buffer
    glEnable(GL_DEPTH_TEST);


    //fond noir
    glClearColor(0.0, 0.0, 0.0, 0.0);

    SDL_GL_SwapWindow(m_fenetre);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Définition de la zone visible
    gluPerspective(ANGLE_VISION, RATIO, PRET, LOIN);

    return true;

}




void Scene::executer()
{
    initSDL2();
    initOpenGl();

    wiimote_t** wiimotes;
    int found, connected;

    wiimotes=wiiuse_init(MAX_WIIMOTE); //On initialise la premiere Wiimote
    found = wiiuse_find(wiimotes, MAX_WIIMOTE,5);//On essaie de la trouver
    if (!found){
        fprintf(stderr,"Aucune Wiimote trouvee\n");

    }
    connected = wiiuse_connect(wiimotes, MAX_WIIMOTE);
    if(connected) {
          printf("connected to wiimote \n");
    } else {
     printf("Failed to connect to any wiimote\n");
  
    }

    wiiuse_set_leds(wiimotes[0],WIIMOTE_LED_1); //On fixe sa DEL a la position 1
    wiiuse_rumble(wiimotes[0],1); //On la fait vibrer pendant 400 ms
    SDL_Delay(400);
    wiiuse_rumble(wiimotes[0],0);
    wiiuse_set_ir(wiimotes[0],1); //On active l'infrarouge pour la premiere Wiimote
    wiiuse_set_ir_vres(wiimotes[0],1024,768); //On définit l'espace infrarouge a (0->1024 ; 0->768)

    printf("Connexion etablie\n");

    //chargement des textures
    Texture texture0("Textures/verre6.jpg");
    texture0.charger();

    Texture texture_bk("Textures/perdicus_bk.tga");
    texture_bk.charger();
    cout << "bk: "<<texture_bk.getID()<<endl;

    Texture texture_dn("Textures/perdicus_dn.tga");
    texture_dn.charger();
    cout << "dn: "<<texture_dn.getID()<<endl;


    Texture texture_ft("Textures/perdicus_ft.tga");
    texture_ft.charger();
    cout << "ft: "<<texture_ft.getID()<<endl;


    Texture texture_lf("Textures/perdicus_lf.tga");
    texture_lf.charger();
    cout << "lf: "<< texture_lf.getID()<<endl;


    Texture texture_rt("Textures/perdicus_rt.tga");
    texture_rt.charger();
    cout << "rt: "<<texture_rt.getID()<<endl;


    Texture texture_up("Textures/perdicus_up.tga");
    texture_up.charger();
    cout << "up: "<<texture_up.getID()<<endl;



        while(continuer)
    {
        gererEvenements();
        //animer();
        dessiner();
        //afficher();
        }

}

void Scene::gererEvenements(void)
{
    SDL_Event evenement;


    while (SDL_PollEvent(&evenement))
    {
        switch(evenement.type)
        {
            case SDL_QUIT:
                continuer = false;
                break;
            case SDL_KEYDOWN:
                switch (evenement.key.keysym.scancode)
            {
                case SDL_SCANCODE_ESCAPE:
                    continuer = false;
                    break;
                case SDL_SCANCODE_Z: //va savoir pourquoi c'est W?
                    GLint mode[2];
                    glGetIntegerv (GL_POLYGON_MODE, mode);
                    glPolygonMode (GL_FRONT_AND_BACK, mode[1] ==  GL_FILL ? GL_LINE : GL_FILL);
                    break;
                case SDL_SCANCODE_UP:
                    personnage->avancer(1.5);
                    break;
                case SDL_SCANCODE_DOWN:
                    personnage->avancer(-1.5);
                    break;
                case SDL_SCANCODE_RIGHT:
                    personnage->tournerHorizontalement(-10.0);
                    break;
                case SDL_SCANCODE_LEFT:
                    personnage->tournerHorizontalement(10.0);
                    break;
                case SDL_SCANCODE_P:
                    personnage->tournerVerticalement(10.0);
                    break;
                case SDL_SCANCODE_SEMICOLON:
                    personnage->tournerVerticalement(-10.0);

                default:
                    break;
            }

            case SDL_MOUSEBUTTONDOWN:
                break;
            default:
                break;

        }

    }

}

void Scene::animer(){

}

void Scene::dessiner(){
    // Vidage de l'écran
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Place la camera
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    //gluLookAt(10,0,0,0,0,0,0,0,1);
    personnage->regarder();

    dessinerSkybox();
    dessinerObjets();

    SDL_Delay(10);
    SDL_GL_SwapWindow(m_fenetre);
}

void Scene::dessinerSkybox() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float t = 800.0f;
    // On mémorise le repère courant avant d'effectuer la RST
    glDepthMask(GL_FALSE);

    // Utilisation de la texture CubeMap
    //glBindTexture(GL_TEXTURE_2D, 2);
    // Pas de teinte
    glColor3ub(255,255,255);


    vector<Vec4f> vertices;
    vertices.resize(8);

    vertices[0]=Vec4f(-t,-t,-t,1);
    vertices[1]=Vec4f(t,-t,-t,1);
    vertices[2]=Vec4f(t,-t,t,1);
    vertices[3]=Vec4f(-t,-t,t,1);
    vertices[4]=Vec4f(-t,t,-t,1);
    vertices[5]=Vec4f(t,t,-t,1);
    vertices[6]=Vec4f(t,t,t,1);
    vertices[7]=Vec4f(-t,t,t,1);

    glBindTexture(GL_TEXTURE_2D, 5);
    // Rendu de la géométrie
    glBegin(GL_QUADS);			// X Négatif
    glTexCoord2f(0,0); glVertex3f(vertices[0][0],vertices[0][1],vertices[0][2]);
    glTexCoord2f(1,0); glVertex3f(vertices[4][0],vertices[4][1],vertices[4][2]);
    glTexCoord2f(1,1); glVertex3f(vertices[7][0],vertices[7][1],vertices[7][2]);
    glTexCoord2f(0,1); glVertex3f(vertices[3][0],vertices[3][1],vertices[3][2]);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, 6);
    glBegin(GL_QUADS);			// X Positif
    glTexCoord2f(0,0); glVertex3f(vertices[5][0],vertices[5][1],vertices[5][2]);
    glTexCoord2f(1,0); glVertex3f(vertices[1][0],vertices[1][1],vertices[1][2]);
    glTexCoord2f(1,1); glVertex3f(vertices[2][0],vertices[2][1],vertices[2][2]);
    glTexCoord2f(0,1); glVertex3f(vertices[6][0],vertices[6][1],vertices[6][2]);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, 4);
    glBegin(GL_QUADS);			// Y Négatif
    glTexCoord2f(0,0); glVertex3f(vertices[1][0],vertices[1][1],vertices[1][2]);
    glTexCoord2f(1,0); glVertex3f(vertices[0][0],vertices[0][1],vertices[0][2]);
    glTexCoord2f(1,1); glVertex3f(vertices[3][0],vertices[3][1],vertices[3][2]);
    glTexCoord2f(0,1); glVertex3f(vertices[2][0],vertices[2][1],vertices[2][2]);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, 2);
    glBegin(GL_QUADS);			// Y Positif
    glTexCoord2f(0,0); glVertex3f(vertices[4][0],vertices[4][1],vertices[4][2]);
    glTexCoord2f(1,0); glVertex3f(vertices[5][0],vertices[5][1],vertices[5][2]);
    glTexCoord2f(1,1); glVertex3f(vertices[6][0],vertices[6][1],vertices[6][2]);
    glTexCoord2f(0,1); glVertex3f(vertices[7][0],vertices[7][1],vertices[7][2]);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, 7);
    glBegin(GL_QUADS);			// Z Négatif
    glTexCoord2f(1,0); glVertex3f(vertices[0][0],vertices[0][1],vertices[0][2]);
    glTexCoord2f(1,1); glVertex3f(vertices[1][0],vertices[1][1],vertices[1][2]);
    glTexCoord2f(0,1); glVertex3f(vertices[5][0],vertices[5][1],vertices[5][2]);
    glTexCoord2f(0,0); glVertex3f(vertices[4][0],vertices[4][1],vertices[4][2]);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, 3);
    glBegin(GL_QUADS);			// Z Positif
    glTexCoord2f(0,1); glVertex3f(vertices[7][0],vertices[7][1],vertices[7][2]);
    glTexCoord2f(0,0); glVertex3f(vertices[6][0],vertices[6][1],vertices[6][2]);
    glTexCoord2f(1,0); glVertex3f(vertices[2][0],vertices[2][1],vertices[2][2]);
    glTexCoord2f(1,1); glVertex3f(vertices[3][0],vertices[3][1],vertices[3][2]);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glDepthMask(GL_TRUE);
    }


void Scene::dessinerObjets(){
    personnage->afficher();

    Personnage *objet2 = new Personnage(3,0,0,0,0,"data/stalagtites1.rtf");

    objet2->afficher();

}


void Scene::afficher(){


}
