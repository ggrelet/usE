//
//  Matrix4x4.h
//  RunnerGame
//
//  Created by Etcheverry Mayalen on 09/06/2016.
//  Copyright © 2016 Etcheverry Mayalen. All rights reserved.
//

#ifndef Mat4_h
#define Mat4_h
#include "Define.h"
#include "Vec4.h"

/// Vector in 3 dimensions, with basics operators overloaded.
template <class T>


class Mat4 {
    
public:
    inline Mat4 (void)	{
        for (int i =0; i<4; i++) {
            for (int j =0; j<4; j++) {
                p[i][j]= 0.0;
                }
            }
    }
    
    inline Mat4 (T p0, T p1, T p2, T p3,T p01, T p11, T p21, T p31,T p02, T p12, T p22, T p32,T p03, T p13, T p23, T p33 ) {
        p[0][0] = p0;
        p[0][1] = p1;
        p[0][2] = p2;
        p[0][3] = p3;
        p[1][0] = p01;
        p[1][1] = p11;
        p[1][2] = p21;
        p[1][3] = p31;
        p[2][0] = p02;
        p[2][1] = p12;
        p[2][2] = p22;
        p[2][3] = p32;
        p[3][0]= p03;
        p[3][1]= p13;
        p[3][2]= p23;
        p[3][3]= p33;
    };
    
    inline Mat4 (const Mat4 & m) {
        init (p[0][0], p[0][1],p[0][2],p[0][3],p[1][0],p[1][1],p[1][2],p[1][3],p[2][0],p[2][1],p[2][2],p[2][3],p[3][0],p[3][1],p[3][2],p[3][3]);
    }
    
    ~Mat4() {}
    
    inline Mat4 (T* pp) {
        p[0][0] = pp[0][0];
        p[0][1] = pp[0][1];
        p[0][2] = pp[0][2];
        p[0][3] = pp[0][3];
        p[1][0] = pp[1][0];
        p[1][1] = pp[1][1];
        p[1][2] = pp[1][2];
        p[1][3] = pp[1][3];
        p[2][0] = pp[2][0];
        p[2][1] = pp[2][1];
        p[2][2] = pp[2][2];
        p[2][3] = pp[2][3];
        p[3][0] = pp[3][0];
        p[3][1] = pp[3][1];
        p[3][2] = pp[3][2];
        p[3][3] = pp[3][3];
       
    };
    
    // *********
    // Operators
    // *********
    
    inline Vec4<T>& operator[] (int i) {
        return (p[i]);
    };
    
    inline const Vec4<T>& operator[] (int i) const {
        return (p[i]);
    };
    
    inline Mat4& operator= (const Mat4& P) {
        p[0][0] = P[0][0];
        p[0][1] = P[0][1];
        p[0][2] = P[0][2];
        p[0][3] = P[0][3];
        p[1][0] = P[1][0];
        p[1][1] = P[1][1];
        p[1][2] = P[1][2];
        p[1][3] = P[1][3];
        p[2][0] = P[2][0];
        p[2][1] = P[2][1];
        p[2][2] = P[2][2];
        p[2][3] = P[2][3];
        p[3][0] = P[3][0];
        p[3][1] = P[3][1];
        p[3][2] = P[3][2];
        p[3][3] = P[3][3];
        return (*this);
    };
    
    inline Mat4& operator+= (const Mat4 & P) {
        p[0][0] += P[0][0];
        p[0][1] += P[0][1];
        p[0][2] += P[0][2];
        p[0][3] += P[0][3];
        p[1][0] += P[1][0];
        p[1][1] += P[1][1];
        p[1][2] += P[1][2];
        p[1][3] += P[1][3];
        p[2][0] += P[2][0];
        p[2][1] += P[2][1];
        p[2][2] += P[2][2];
        p[2][3] += P[2][3];
        p[3][0] += P[3][0];
        p[3][1] += P[3][1];
        p[3][2] += P[3][2];
        p[3][3] += P[3][3];
        return (*this);
    };
    
    inline Mat4& operator-= (const Mat4 & P) {
        p[0][0] -= P[0][0];
        p[0][1] -= P[0][1];
        p[0][2] -= P[0][2];
        p[0][3] -= P[0][3];
        p[1][0] -= P[1][0];
        p[1][1] -= P[1][1];
        p[1][2] -= P[1][2];
        p[1][3] -= P[1][3];
        p[2][0] -= P[2][0];
        p[2][1] -= P[2][1];
        p[2][2] -= P[2][2];
        p[2][3] -= P[2][3];
        p[3][0] -= P[3][0];
        p[3][1] -= P[3][1];
        p[3][2] -= P[3][2];
        p[3][3] -= P[3][3];
        return (*this);
    };
    
    inline Mat4& operator*= (const Mat4 & P) {
        for (int i =0; i<4; i++) {
            for (int j =0; j<4; j++) {
                p[i][j]= p[i][0]*P[0][j]+p[i][1]*P[1][j]+p[i][2]*P[2][j]+p[i][3]*P[3][j];
            }
        }
        return (*this);
    };
    
    inline Mat4& operator*= (T s) {
        p[0][0] *= s;
        p[0][1] *= s;
        p[0][2] *= s;
        p[0][3] *= s;
        p[1][0] *= s;
        p[1][1] *= s;
        p[1][2] *= s;
        p[1][3] *= s;
        p[2][0] *= s;
        p[2][1] *= s;
        p[2][2] *= s;
        p[2][3] *= s;
        p[3][0] *= s;
        p[3][1] *= s;
        p[3][2] *= s;
        p[3][3] *= s;
        return (*this);
    };
    
    /*inline Vec3& operator/= (const Vec3 & P) {
        p[0] /= P[0];
        p[1] /= P[1];
        p[2] /= P[2];
        return (*this);
    };
    
    inline Vec3& operator/= (T s) {
        p[0] /= s;
        p[1] /= s;
        p[2] /= s;
        return (*this);
    };*/
    
    inline Mat4 operator+ (const Mat4 & P) const {
        Mat4 res;
        res[0][0] = p[0][0] + P[0][0];
        res[0][1] = p[0][1] + P[0][1];
        res[0][2] = p[0][2] + P[0][2];
        res[0][3] = p[0][3] + P[0][3];
        res[1][0] = p[1][0] + P[1][0];
        res[1][1] = p[1][1] + P[1][1];
        res[1][2] = p[1][2] + P[1][2];
        res[1][3] = p[1][3] + P[1][3];
        res[2][0] = p[2][0] + P[2][0];
        res[2][1] = p[2][1] + P[2][1];
        res[2][2] = p[2][2] + P[2][2];
        res[2][3] = p[2][3] + P[2][3];
        res[3][0] = p[3][0] + P[3][0];
        res[3][1] = p[3][1] + P[3][1];
        res[3][2] = p[3][2] + P[3][2];
        res[3][3] = p[3][3] + P[3][3];
        return (res);
    };
    
    inline Mat4 operator- (const Mat4 & P) const {
        Mat4 res;
        res[0][0] = p[0][0] - P[0][0];
        res[0][1] = p[0][1] - P[0][1];
        res[0][2] = p[0][2] - P[0][2];
        res[0][3] = p[0][3] - P[0][3];
        res[1][0] = p[1][0] - P[1][0];
        res[1][1] = p[1][1] - P[1][1];
        res[1][2] = p[1][2] - P[1][2];
        res[1][3] = p[1][3] - P[1][3];
        res[2][0] = p[2][0] - P[2][0];
        res[2][1] = p[2][1] - P[2][1];
        res[2][2] = p[2][2] - P[2][2];
        res[2][3] = p[2][3] - P[2][3];
        res[3][0] = p[3][0] - P[3][0];
        res[3][1] = p[3][1] - P[3][1];
        res[3][2] = p[3][2] - P[3][2];
        res[3][3] = p[3][3] - P[3][3];
        return (res);
    };
    
    inline Mat4 operator- () const {
        Mat4 res;
        res[0][0] = -p[0][0];
        res[0][1] = -p[0][1];
        res[0][2] = -p[0][2];
        res[0][3] = -p[0][3];
        res[1][0] = -p[1][0];
        res[1][1] = -p[1][1];
        res[1][2] = -p[1][2];
        res[1][3] = -p[1][3];
        res[2][0] = -p[2][0];
        res[2][1] = -p[2][1];
        res[2][2] = -p[2][2];
        res[2][3] = -p[2][3];
        res[3][0] = -p[3][0];
        res[3][1] = -p[3][1];
        res[3][2] = -p[3][2];
        res[3][3] = -p[3][3];
        return (res);
    };
    
    inline Mat4 transposee() const {
        Mat4 res;
        for (int i =0; i<4; i++) {
            for (int j =0; j<4; j++) {
                res[i][j]= p[j][i];
            }
        }
        return (res);
    };
    
    inline Mat4 lookAt(Vec4<T> position, Vec4<T> pointCible, Vec4<T> axeVertical) const{
        
        Mat4 res;
        Vec4<T> orientation = normalize(pointCible - position);
        Vec4<T> deplacementLateral = normalize(cross(axeVertical,orientation));
        
        res[0][0] = deplacementLateral[0];
        res[0][1] = deplacementLateral[1];
        res[0][2] = deplacementLateral[2];
        
        res[1][0] = axeVertical[0];
        res[1][1] = axeVertical[1];
        res[1][2] = axeVertical[2];
        
        res[2][0] = -orientation[0];
        res[2][1] = -orientation[1];
        res[2][2] = -orientation[2];
        
        res[0][3] = -dot(deplacementLateral,position);
        res[1][3] = -dot(axeVertical,position);
        res[2][3] = dot(orientation,position);
        

        return (res);
    };

    
    
    static inline Mat4 identite() {
        Mat4 res;
        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++) {
                res[i][j]=0.0f;
            }
        }
        
        for (int k=0; k<4; k++) {
            res[k][k]=1.0f;
        }
        return (res);
    };
    
    static inline Mat4 scale(float sX, float sY,float sZ) {
        Mat4 res=identite();
        res[0][0]=sX;
        res[1][1]=sY;
        res[2][2]=sZ;
        return (res);
    };

    
    static inline Mat4 translation(float tX,float tY,float tZ) {
        Mat4 res=identite();
        res[0][3]=tX;
        res[1][3]=tY;
        res[2][3]=tZ;        return (res);
    };

    
    
    static inline Mat4 rotation(float thetaX,float thetaY,float thetaZ) {
        Mat4 res;
        Mat4 Rx;
        Mat4 Ry;
        Mat4 Rz;
        
        Rx[0][0] = 1.0f;
        Rx[0][1] = 0.0f;
        Rx[0][2] = 0.0f;
        Rx[0][3] = 0.0f;
        
        Rx[1][0] = 0.0f;
        Rx[1][1] = cos(thetaX);
        Rx[1][2] = -sin(thetaX);
        Rx[1][3] = 0.0f;
        
        Rx[2][0] = 0.0f;
        Rx[2][1] = sin(thetaX);
        Rx[2][2] = cos(thetaX);
        Rx[2][3] = 0.0f;
        
        Rx[3][0] = 0.0f;
        Rx[3][1] = 0.0f;
        Rx[3][2] = 0.0f;
        Rx[3][3] = 1.0f;
        
        Ry[0][0] = cos(thetaY);
        Ry[0][1] = 0.0f;
        Ry[0][2] = sin(thetaY);
        Ry[0][3] = 0.0f;
        
        Ry[1][0] = 0.0f;
        Ry[1][1] = 1.0f;
        Ry[1][2] = 0.0f;
        Ry[1][3] = 0.0f;
        
        Ry[2][0] = -sin(thetaY);
        Ry[2][1] = 0.0f;
        Ry[2][2] = cos(thetaY);
        Ry[2][3] = 0.0f;
        
        Ry[3][0] = 0.0f;
        Ry[3][1] = 0.0f;
        Ry[3][2] = 0.0f;
        Ry[3][3] = 1.0f;
        
        Rz[0][0] = cos(thetaZ);
        Rz[0][1] = -sin(thetaZ);
        Rz[0][2] = 0.0f;
        Rz[0][3] = 0.0f;
        
        Rz[1][0] = sin(thetaZ);
        Rz[1][1] = cos(thetaZ);
        Rz[1][2] = 0.0f;
        Rz[1][3] = 0.0f;
        
        Rz[2][0] = 0.0f;
        Rz[2][1] = 0.0f;
        Rz[2][2] = 1.0f;
        Rz[2][3] = 0.0f;
        
        Rz[3][0] = 0.0f;
        Rz[3][1] = 0.0f;
        Rz[3][2] = 0.0f;
        Rz[3][3] = 1.0f;
        
    
        res = Rx * Ry * Rz;
        return (res);
    };
    
    static inline Mat4 projection(float ANGLE_VISION,float RATIO, float PRET,float LOIN) {
        Mat4 projection;
        float tan = tanf(ANGLE_VISION/2);
        
        projection[0][0] = 1.0f/(tan* RATIO);
        projection[0][1] = 0.0f;
        projection[0][2] = 0.0f;
        projection[0][3] = 0.0f;
        
        projection[1][0] = 0.0f;
        projection[1][1] = 1.0f/tan;
        projection[1][2] = 0.0f;
        projection[1][3] = 0.0f;
        
        projection[2][0] = 0.0f;
        projection[2][1] = 0.0f;
        projection[2][2] = (-LOIN - PRET) / (LOIN - PRET);
        projection[2][3] = 2.0f * LOIN * PRET / (LOIN - PRET);
        
        projection[3][0] = 0.0f;
        projection[3][1] = 0.0f;
        projection[3][2] = 1.0f;
        projection[3][3] = 0.0f;
        
        projection[0][0] = 1.0f / (tan* RATIO);
        projection[0][1] = 0.0f;
        projection[0][2] = 0.0f;
        projection[0][3] = 0.0f;
        
        
        projection[0][0] = 1.0f / (tan* RATIO);
        projection[0][1] = 0.0f;
        projection[0][2] = 0.0f;
        projection[0][3] = 0.0f;
        return (projection);
    };
    
    inline float* mat_to_pointeur() {
        float* res= new float[16];
        for(int k = 0;k<16;k++){
        res[k]=p[k/4][k%4];
        }
        return res;
    };

    
    inline Mat4 operator* (const Mat4 & P) const {
        Mat4 res;
        for (int i =0; i<4; i++) {
            for (int j =0; j<4; j++) {
                res[i][j]= p[i][0]*P[0][j]+p[i][1]*P[1][j]+p[i][2]*P[2][j]+p[i][3]*P[3][j];
            }
        }
        return (res);
    };
    
    inline Mat4 operator* (T s) const {
        Mat4 res;
        for (int i =0; i<4; i++) {
            for (int j =0; j<4; j++) {
                res[i][j]= p[i][j]*s;
                }
        }
        return (res);
    };
    
    inline Vec4<T> operator* (Vec4<T>  v) const {
        Vec4<T> res;
        for (int k =0; k<4; k++) {
            res[k]= p[k][0]*v[0]+p[k][1]*v[1]+p[k][2]*v[2]+p[k][3]*v[3];
            }
        return (res);
    };
    
    
    /*inline Vec3 operator/ (const Vec3 & P) const {
        Vec3 res;
        res[0] = p[0] / P[0];
        res[1] = p[1] / P[1];
        res[2] = p[2] / P[2];
        return (res);
    };*/
    
    inline Mat4 operator/ (T s) const {
        Mat4 res;
        for (int i =0; i<4; i++) {
            for (int j =0; j<4; j++) {
                res[i][j]= p[i][j]/s;
                                }
                }
        return (res);
    };
    
    inline bool operator == (const Mat4 & a) const {
        for (int i =0; i<4; i++)
            for (int j =0; j<4; j++)
                if (p[i][j]!= a[i][j])
                    return false;
        return true;
    };
    
    inline bool operator != (const Mat4 & a) const {
        for (int i =0; i<4; i++)
            for (int j =0; j<4; j++)
                if (p[i][j]!= a[i][j])
                    return true;
        return false;
    };
    
    
    
    /////////////////////////////////////////////////////////////////
    
    inline Mat4 & init (T w, T x, T y, T z,T w1, T x1, T y1, T z1,T w2, T x2, T y2, T z2,T w3, T x3, T y3, T z3) {
        p[0][0] = w;
        p[0][1] = x;
        p[0][2] = y;
        p[0][3] = z;
        p[1][0] = w1;
        p[1][1] = x1;
        p[1][2] = y1;
        p[1][3] = z1;
        p[2][0] = w2;
        p[2][1] = x2;
        p[2][2] = y2;
        p[2][3] = z2;
        p[3][0]= w3;
        p[3][1]= x3;
        p[3][2]= y3;
        p[3][3]= z3;
        return (*this);
    };
    
protected:
    Vec4<T> p[4];
};



template <class T>
inline T dot (const Mat4<T> & a, const Mat4<T> & b) {
    T res = NULL;
    for (int k=0; k<4; k++) {
        res+=(a.transposee()*b)[k][k];
    }
    return (res);
}



template <class T>

inline Mat4<T> operator * (const T &s, const Mat4<T> &P) {
    return (P * s);
}

template <class T>
inline Vec4<T> operator * (const Mat4<T> &P, const Vec4<T> &v) {
    return (P * v);
}

template <class T>
std::ostream & operator<< (std::ostream & output, const Mat4<T> & v) {
    output << v[0][0] << " " << v[0][1] << " " << v[0][2] << " " << v[0][3]<<std::endl;
    output << v[1][0] << " " << v[1][1] << " " << v[1][2] << " " << v[1][3]<<std::endl;
    output << v[2][0] << " " << v[2][1] << " " << v[2][2] << " " << v[2][3]<<std::endl;
    output << v[3][0] << " " << v[3][1] << " " << v[3][2] << " " << v[3][3]<<std::endl;
    return output;
}

template <class T>
std::istream & operator>> (std::istream & input, Mat4<T> & v) {
    input >> v[0][0] >> v[0][1] >> v[0][2] >> v[0][3]>> v[1][0] >> v[1][1] >> v[1][2] >> v[1][3]>> v[2][0] >> v[2][1] >> v[2][2] >> v[2][3]>> v[3][0] >> v[3][1] >> v[3][2] >> v[3][3];
    return input;
}

typedef Mat4<float> Mat4f;
typedef Mat4<double> Mat4d;
typedef Mat4<int> Mat4i;


#endif /* Mat4_h */
