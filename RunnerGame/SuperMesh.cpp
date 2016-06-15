//
//  SuperMesh.cpp
//  PROJET_IGR202
//
//  Created by Etcheverry Mayalen on 26/01/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#include <stdio.h>
#include "SuperMesh.h"


using namespace std;

void SuperMesh::loadOBJ (const std::string & filename) {
    
    vector<Vec4f> N;
    vector<Vec4f> Text;
    
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int l = 0;
    unsigned int t = 0;
    unsigned int iglobal=0;
    unsigned int jglobal=0;
    unsigned int tglobal=0;
    unsigned int gcurrent =0;
    
    unsigned int size=0;
    
    
    // premiere lecture pour trouver le nombre d'objets dans mon premier supermesh
    FILE * file = fopen(filename.c_str (), "r");
    if( file == NULL ){
        printf("Impossible to open the file !\n");
    }
    while( 1 ){
        
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        
        // else : parse lineHeader
        
        if (strcmp( lineHeader, "g" ) == 0 ){
            
            size+=1;
            
        }
        
        //else {printf("File can't be read by our simple parser :  Try exporting with other options\n");}
    }
    
    meshes.resize(size);
    
    
    
    // 2eme lecture pour trouver le nombre de sommets, normales, faces, texture pour chaque objet
    file = fopen(filename.c_str (), "r");
    if( file == NULL ){
        printf("Impossible to open the file a second time !\n");
    }
    
    
    unsigned int VSize [size]; //pour l'instant 4 mais nombre d'objets
    unsigned int NSize [size];
    unsigned int TSize [size];
    unsigned int SSize [size];
    unsigned int TexSize[size];
    
    for (int i=0; i<size; i++) {
        VSize [i] = 0;
        NSize [i] = 0;
        TSize [i] = 0;
        SSize [i] = 0;
        TexSize [i] = 0;
    }
    
     meshes.resize(size);
    

    while( 1 ){
        
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        
        // else : parse lineHeader
        
        if (strcmp( lineHeader, "g" ) == 0 ){
            
            gcurrent+=1;
            
        }
        
        
        else if ( strcmp( lineHeader, "v" ) == 0 ){
            VSize[gcurrent-1]+=1;
                    }
        else if ( strcmp( lineHeader, "vn" ) == 0 ){
            NSize[gcurrent-1]+=1;
        }
        
        else if ( strcmp( lineHeader, "vt" ) == 0 ){
            TexSize[gcurrent-1]+=1;
        }
        
        else if ( strcmp( lineHeader, "f" ) == 0 ){
            unsigned int vertexIndex[4], normalIndex[4], uvIndex[4];
            int matches = fscanf(file,"%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d \n", &vertexIndex[0], &uvIndex[0],&normalIndex[0], &vertexIndex[1],&uvIndex[1], &normalIndex[1], &vertexIndex[2],&uvIndex[2], &normalIndex[2],&vertexIndex[3],&uvIndex[3], &normalIndex[3]);
            
            if (matches==9) {
                TSize[gcurrent-1]+=1;
            }
            else if (matches==12) {
                SSize[gcurrent-1]+=1;
            }
        }
            
        //else {printf("File can't be read by our simple parser :  Try exporting with other options\n");}
        }
    
    gcurrent= 0;
    
    file = fopen(filename.c_str (), "r");
    if( file == NULL ){
        printf("Impossible to open the file a second time !\n");
    }
    
    while( 1 ){
        
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        
        // else : parse lineHeader
        
        if (strcmp( lineHeader, "g" ) == 0 ){
            
            fscanf(file, "%d\n", &gcurrent);
            gcurrent-=1;
            iglobal+=i;
            jglobal+=j;
            tglobal+=t;
            i=0;
            j=0;
            k=0;
            l=0;
            t=0;
            
            meshes[gcurrent].V.resize(VSize[gcurrent]);
            N.resize(NSize[gcurrent],Vec4f(0.0,0.0,0.0,0.0));
            Text.resize(TexSize[gcurrent],Vec4f(0.0,0.0,0.0,0.0));
            meshes[gcurrent].T.resize(TSize[gcurrent]);
            meshes[gcurrent].S.resize(SSize[gcurrent]);
            
            
        }
        
        
        else if ( strcmp( lineHeader, "v" ) == 0 ){
            Vertex vertex;
            fscanf(file, "%f %f %f\n", &vertex.p[0], &vertex.p[1], &vertex.p[2] );
            meshes[gcurrent].V[i]=vertex;
            i++;
        }
        
        
        else if ( strcmp( lineHeader, "vn" ) == 0 ){
            Vec4f normale;
            fscanf(file, "%f %f %f\n", &normale[0], &normale[1], &normale[2]);
            N[j]=normale;
            j++;
        }
        else if ( strcmp( lineHeader, "vt" ) == 0 ){
            Vec4f texture;
            fscanf(file, "%f %f %f\n", &texture[0], &texture[1], &texture[2]);
            Text[t]=texture;
            t++;
        }
        
        
        else if ( strcmp( lineHeader, "f" ) == 0 ){
            
            unsigned int vertexIndex[4], normalIndex[4], uvIndex[4];
            int matches = fscanf(file,"%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d \n", &vertexIndex[0], &uvIndex[0],&normalIndex[0], &vertexIndex[1],&uvIndex[1], &normalIndex[1], &vertexIndex[2],&uvIndex[2], &normalIndex[2],&vertexIndex[3],&uvIndex[3], &normalIndex[3]);
            
            /*int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2],&normalIndex[2]);*/
            
            if (matches == 9){
                
                meshes[gcurrent].V[vertexIndex[0]-1-iglobal].n=N[normalIndex[0]-1-jglobal];  // Attribution des normales aux sommets
                meshes[gcurrent].V[vertexIndex[1]-1-iglobal].n=N[normalIndex[1]-1-jglobal];
                meshes[gcurrent].V[vertexIndex[2]-1-iglobal].n=N[normalIndex[2]-1-jglobal];
                
                
                meshes[gcurrent].V[vertexIndex[0]-1-iglobal].vt=Text[uvIndex[0]-1-tglobal];  // Attribution des normales aux sommets
                meshes[gcurrent].V[vertexIndex[1]-1-iglobal].vt=Text[uvIndex[1]-1-tglobal];
                meshes[gcurrent].V[vertexIndex[2]-1-iglobal].vt=Text[uvIndex[2]-1-tglobal];
                
                 
                meshes[gcurrent].T[k].ve[0] = vertexIndex[0]-1-iglobal;  // On remplit la liste des triangles avec l'indice des vertex
                meshes[gcurrent].T[k].ve[1] = vertexIndex[1]-1-iglobal;
                meshes[gcurrent].T[k].ve[2] = vertexIndex[2]-1-iglobal;
                k++;
                
            }
            
            else if (matches == 12){
                meshes[gcurrent].V[vertexIndex[0]-1-iglobal].n=N[normalIndex[0]-1-jglobal];
                meshes[gcurrent].V[vertexIndex[1]-1-iglobal].n=N[normalIndex[1]-1-jglobal];
                meshes[gcurrent].V[vertexIndex[2]-1-iglobal].n=N[normalIndex[2]-1-jglobal];
                meshes[gcurrent].V[vertexIndex[3]-1-iglobal].n=N[normalIndex[3]-1-jglobal];
                
                meshes[gcurrent].V[vertexIndex[0]-1-iglobal].vt=Text[uvIndex[0]-1-tglobal];  // Attribution des normales aux sommets
                meshes[gcurrent].V[vertexIndex[1]-1-iglobal].vt=Text[uvIndex[1]-1-tglobal];
                meshes[gcurrent].V[vertexIndex[2]-1-iglobal].vt=Text[uvIndex[2]-1-tglobal];
                meshes[gcurrent].V[vertexIndex[3]-1-iglobal].vt=Text[uvIndex[3]-1-tglobal];
                
                
                
                meshes[gcurrent].S[l].v[0] = vertexIndex[0]-1-iglobal; // on remplit la liste des carrés avec l'indice de sommets
                meshes[gcurrent].S[l].v[1] = vertexIndex[1]-1-iglobal;
                meshes[gcurrent].S[l].v[2] = vertexIndex[2]-1-iglobal;
                meshes[gcurrent].S[l].v[3] = vertexIndex[3]-1-iglobal;
                l++;
            }
            
            
            
            //else {printf("File can't be read by our simple parser :  Try exporting with other options\n");}
        }
        
    }
    
    centerAndScaleToUnit();
    for (int g=0; g<meshes.size(); g++) {
        meshes[g].recomputeNormals();
    }

}


void SuperMesh::centerAndScaleToUnit () {
   Vec4f c;
    int l = 0;
    for( int g=0; g<meshes.size();g++) {
        l += meshes[g].V.size();
    }
    
    for( int g=0; g<meshes.size();g++) {
        for  (unsigned int i = 0; i < meshes[g].V.size (); i++){
            c += meshes[g].V[i].p;
        }}
    c/=l;
    
    float maxD = dist (meshes[0].V[0].p, c);
         for( int g=0; g<meshes.size();g++) {
    for (unsigned int i = 0; i < meshes[g].V.size (); i++){
        float m = dist (meshes[g].V[i].p, c);
        if (m > maxD)
            maxD = m;
    } }
    
    for( int g=0; g<meshes.size();g++){
        for  (unsigned int i = 0; i < meshes[g].V.size (); i++){
        meshes[g].V[i].p = (meshes[g].V[i].p - c) / maxD;
        meshes[g].V[i].p[3] = 1.0f;
        }
    }}


