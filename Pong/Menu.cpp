#include "Menu.h"
#include <string>
#include <fstream>

using namespace std;

//Moteur du jeu 
extern Moteur moteur;

//Constructeur
Menu::Menu()
{
}

Menu::~Menu()
{
	glDeleteTextures(5,images);
}

//Fonction d'initialisation
bool Menu::init(const string &file)
{
	SDL_Surface *myimages[5];
	
	
	//Ouverture du fichier de paramétrage
	ifstream input(file.c_str());

	//Test si le fichier s'est bien ouvert
	if(!input)
	        {
        	cerr << "Erreur dans l'ouverture du fichier " << file << endl;
	        return false;
        	}

	//Récupération du nom de l'image pour le menu
	string nom;
	input >> nom;

	//On charge l'image de fond
	myimages[0] = IMG_Load(nom.c_str());
	positions[0].x = 0;
	positions[0].y = 0;
	positions[0].w = WIDTH;
	positions[0].h = HEIGHT;
	
	//On récupère la surface de l'image "Titre"
	input >> nom;
	myimages[1] = IMG_Load(nom.c_str());
	
	//Initialisation des positionss du menu
	input >> positions[1].x >> positions[1].y;
	positions[1].w = myimages[1]->w;
	positions[1].h = myimages[1]->h;
	
	//On récupère la surface de l'image "Nouveau"
	input >> nom;
	myimages[2] = IMG_Load(nom.c_str());
	
	//Initialisation de la positions du bouton nouveau
	input >> positions[2].x >> positions[2].y;
	positions[2].w = myimages[2]->w;
	positions[2].h = myimages[2]->h;
	
	//On récupère la surface de l'image "Quitter"
	input >> nom;
	myimages[3] = IMG_Load(nom.c_str());

	//Initialisation de la positions du bouton positions[3]
	input >> positions[3].x >> positions[3].y;
	positions[3].w = myimages[3]->w;
	positions[3].h = myimages[3]->h;

	//On recupere la surface de l'image "Continuer"
	input >> nom;
	myimages[4] = IMG_Load(nom.c_str());

	//Initialisation de la positions du bouton positions[3]
	input >> positions[4].x >> positions[4].y;
	positions[4].w = myimages[4]->w;
	positions[4].h = myimages[4]->h;
	
	//Ferme le fichier	
	input.close();

	//On passe les textures SDL en textures OpenGL
	glGenTextures(5,images);
	
	for(int i=0;i<5;i++)
    {   // Format de l'image
        
        GLenum formatInterne(0);
        GLenum format(0);
        
        
        // Détermination du format et du format interne pour les images à 3 composantes
        
        if(myimages[i]->format->BytesPerPixel == 3)
        {
            // Format interne
            
            formatInterne = GL_RGB;
            
            
            // Format
            
            if(myimages[i]->format->Rmask == 0xff)
                format = GL_RGB;
            
            else
                format = GL_BGR;
        }
        
        
        // Détermination du format et du format interne pour les images à 4 composantes
        
        else if(myimages[i]->format->BytesPerPixel == 4)
        {
            // Format interne
            
            formatInterne = GL_RGBA;
            
            
            // Format
            
            if(myimages[i]->format->Rmask == 0xff)
                format = GL_RGBA;
            
            else
                format = GL_BGRA;
        }
        
        
        // Dans les autres cas, on arrête le chargement
        
        else
        {
            std::cout << "Erreur, format interne de l'image inconnu" << std::endl;
            SDL_FreeSurface(myimages[i]);
        }
        

		glBindTexture(GL_TEXTURE_2D,images[i]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        

		
		glTexImage2D(GL_TEXTURE_2D,0,formatInterne,myimages[i]->w,myimages[i]->h,0,
				format,GL_UNSIGNED_BYTE,myimages[i]->pixels);

		
	}

	//On retourne vrai
	return true;
}

//Gestion du clic
void Menu::clic(int x, int y)
{
//Est-ce qu'on est dans le bouton nouveau?
if((positions[2].x<x)&&(positions[2].x+positions[2].w>x)&&(positions[2].y<y)&&(positions[2].y+positions[2].h>y))
	{
	moteur.initJeu();
	moteur.echangeFonctions();
	}
//Est-ce qu'on est dans le bouton positions[3]?
else if((positions[3].x<x)&&(positions[3].x+positions[3].w>x)&&(positions[3].y<y)&&(positions[3].y+positions[3].h>y))
	{
	moteur.fin();
	}
}

//Gestion du clavier
bool Menu::clavier(unsigned char k)
{
	switch(k)
	{
		case 'c':
			moteur.echangeFonctions();
			return true;
		case 'n':
			moteur.initJeu();
			moteur.echangeFonctions();
			return true;
		default:
			return false;
	}
}

//Fonction d'affichage
void Menu::affiche()
{
	int i;
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	glAlphaFunc(GL_LESS,10);
	glEnable(GL_ALPHA_TEST);

	//On dessine l'image de fond

	glColor4f(1.0,1.0,1.0,0.0);
	for(i=0;i<4;i++)
		{
		glBindTexture(GL_TEXTURE_2D, images[i]);
		glBegin(GL_QUADS);
			glTexCoord2i(0,0);glVertex2i(positions[i].x,positions[i].y); 
			glTexCoord2i(1,0);glVertex2i(positions[i].x+positions[i].w,positions[i].y);
			glTexCoord2i(1,1);glVertex2i(positions[i].x+positions[i].w,positions[i].y+positions[i].h);
			glTexCoord2i(0,1);glVertex2i(positions[i].x,positions[i].y+positions[i].h);
		glEnd();
		}
	
	//Pour le dernier bouton, cela dépend si le jeu est en cours
	//Remarque i vaut 4, donc c'est bien
	if(moteur.jeuEnCours())
	{
		glBindTexture(GL_TEXTURE_2D, images[i]);
		glBegin(GL_QUADS);
			glTexCoord2i(0,0);glVertex2i(positions[i].x,positions[i].y); 
			glTexCoord2i(1,0);glVertex2i(positions[i].x+positions[i].w,positions[i].y);
			glTexCoord2i(1,1);glVertex2i(positions[i].x+positions[i].w,positions[i].y+positions[i].h);
			glTexCoord2i(0,1);glVertex2i(positions[i].x,positions[i].y+positions[i].h);
		glEnd();
	}
	
	glDisable(GL_TEXTURE_2D);
}
