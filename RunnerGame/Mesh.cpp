// --------------------------------------------------------------------------
// Copyright(C) 2009-2015
// Tamy Boubekeur
//                                                                            
// All rights reserved.                                                       
//                                                                            
// This program is free software; you can redistribute it and/or modify       
// it under the terms of the GNU General Public License as published by       
// the Free Software Foundation; either version 2 of the License, or          
// (at your option) any later version.                                        
//                                                                            
// This program is distributed in the hope that it will be useful,            
// but WITHOUT ANY WARRANTY; without even the implied warranty of             
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              
// GNU General Public License (http://www.gnu.org/licenses/gpl.txt)           
// for more details.                                                          
// --------------------------------------------------------------------------

#include "Define.h"
#include "Mesh.h"
#include "Vec4.h"

using namespace std;

void Mesh::recomputeNormals () {
    for (unsigned int i = 0; i < V.size (); i++)
        V[i].n = Vec4f (0.0, 0.0, 0.0,0.0);
    for (unsigned int i = 0; i < T.size (); i++) {
        Vec4f e01 = V[T[i].ve[1]].p -  V[T[i].ve[0]].p;
        Vec4f e02 = V[T[i].ve[2]].p -  V[T[i].ve[0]].p;
        Vec4f n = cross (e01, e02);
        n.normalize ();
        for (unsigned int j = 0; j < 3; j++)
            V[T[i].ve[j]].n += n;
    }
    for (unsigned int i = 0; i < V.size (); i++)
        V[i].n.normalize ();
    
    for (unsigned int i = 0; i < S.size (); i++) {
        Vec4f e01 = V[S[i].v[1]].p -  V[S[i].v[0]].p;
        Vec4f e02 = V[S[i].v[2]].p -  V[S[i].v[0]].p;
        Vec4f n = cross (e01, e02);
        n.normalize ();
        for (unsigned int j = 0; j < 4; j++)
            V[S[i].v[j]].n += n;
    }
    for (unsigned int i = 0; i < V.size (); i++)
        V[i].n.normalize ();
}


void Mesh::centerAndScaleToUnit () {
    Vec4f c;
    for  (unsigned int i = 0; i < V.size (); i++)
        c += V[i].p;
    c /= V.size ();
    float maxD = dist (V[0].p, c);
    for (unsigned int i = 0; i < V.size (); i++){
        float m = dist (V[i].p, c);
        if (m > maxD)
            maxD = m;
    }
    for  (unsigned int i = 0; i < V.size (); i++)
        V[i].p = (V[i].p - c) / maxD;
}

void Mesh::deplacer(Vec4f position1, Vec4f position2) {

    
    int n = V.size();
    Vec4f deplacement = position2 - position1;
    
    for(int i=0;i<n;i++){
        V[i].p+=deplacement;
    }
    
    
}
    
    
