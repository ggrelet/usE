#ifndef H_PHYSIQUE
#define H_PHYSIQUE

#include <vector>
#include "Objet.h"

class Physique
{
	public :
		//Fonction qui met à jour les objets
		static void updateObjets(Objet objets[3]);
		
		//Fonction qui teste la collision entre les objets et le rectangle (x,y,w,h)
		static bool isCollision(Objet objets[3], 
			double x, double y, double w, double h);
    
        //Fonction d'initialisation
        static bool init();
		
	private :
		//Fonction qui gere la collision avec l'objet i
		static int collisionObjet(Objet objets[3], int i);
    
        //Fonction qui gere la collision avec l'objet i utilisant les zones
        static int collisionObjetZone(Objet objets[3], int idx);
		
		//Fonction qui teste la collision entre deux rectangles
		static bool collisionRect(double x1,double y1,double w1, double h1,
			double x2, double y2,double w2,double h2);
		
		//Fonction qui teste la collision entre deux cercles
		static bool collisionCercle(double cx1,double cy1,
			double r1, double cx2, double cy2, double r2);
    
        //Tableau de zones
        static std::vector<int> tableau_zones[QUADLIGNE][QUADCOL];
    
        //Enlever un objet d'une zone
        static void enleverObjetZone(int idx, int i, int j);
    
        //Ajouter un objet dans une zone
        static void ajouterObjetZone(int idx, int i, int j);
    
        //Ajouter un objet dans le tableau de zones
        static void ajouterObjetDansZones(Objet objets[3], int idx);
    
        //Enlever un objet du le tableau de zones
        static void enleverObjetDesZones(Objet objets[3], int idx);
    
        //Recupere la position de l'objet o dépendant de l'entier i
        static void recupereCoinObjet(Objet &o, int i, double &x, double &y);
    
        //Recupere la colonne en fonction de la position x
        static int recupereZoneColonne(double x);
    
        //Recupere la ligne en fonction de la position y
        static int recupereZoneLigne(double y);

};

#endif
