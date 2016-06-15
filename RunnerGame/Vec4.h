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

#pragma once

#include "Define.h"


/// Vector in 3 dimensions, with basics operators overloaded.
template <class T>


class Vec4 {

public:
    inline Vec4 (void)	{ p[0] = p[1] = p[2]=0.0;  p[3]=1.0; }

  inline Vec4 (T p0, T p1, T p2, T p3) {
	p[0] = p0;
	p[1] = p1;
	p[2] = p2;
    p[3] = p3;
  };

  inline Vec4 (const Vec4 & v) {
	init (v[0], v[1], v[2],v[3]);
  }
  
  ~Vec4() {}

  inline Vec4 (T* pp) { 
	p[0] = pp[0];
	p[1] = pp[1];
	p[2] = pp[2];
    p[3] = pp[3];
  };

  // *********
  // Operators
  // *********
	
  inline T& operator[] (int Index) {
	return (p[Index]);
  };

  inline const T& operator[] (int Index) const {
	return (p[Index]);
  };

  inline Vec4& operator= (const Vec4 & P) {
	p[0] = P[0];
	p[1] = P[1];
	p[2] = P[2];
    p[3] = P[3];
	return (*this);
  };

  inline Vec4& operator+= (const Vec4 & P) {
	p[0] += P[0];
	p[1] += P[1];
	p[2] += P[2];
    p[3] += P[3];
	return (*this);
  };

  inline Vec4& operator-= (const Vec4 & P) {
	p[0] -= P[0];
	p[1] -= P[1];
	p[2] -= P[2];
    p[3] -= P[3];
	return (*this);
  };

  inline Vec4& operator*= (const Vec4 & P) {
	p[0] *= P[0];
	p[1] *= P[1];
	p[2] *= P[2];
    p[3] *= P[3];
	return (*this);
  };

  inline Vec4& operator*= (T s) {
	p[0] *= s;
	p[1] *= s;
	p[2] *= s;
    p[3] *= s;
	return (*this);
  };

  inline Vec4& operator/= (const Vec4 & P) {
	p[0] /= P[0];
	p[1] /= P[1];
	p[2] /= P[2];
    p[3] /= P[3];
	return (*this);
  };

  inline Vec4& operator/= (T s) {
	p[0] /= s;
	p[1] /= s;
	p[2] /= s;
    p[3] /= s;
	return (*this);
  };

  inline Vec4 operator+ (const Vec4 & P) const {
	Vec4 res;
	res[0] = p[0] + P[0];
	res[1] = p[1] + P[1];
	res[2] = p[2] + P[2];
    res[3] = p[3] + P[3];
	return (res); 
  };

  inline Vec4 operator- (const Vec4 & P) const {
	Vec4 res;
	res[0] = p[0] - P[0];
	res[1] = p[1] - P[1];
	res[2] = p[2] - P[2];
    res[3] = p[3] - P[3];
	return (res); 
  };

  inline Vec4 operator- () const {
	Vec4 res;
	res[0] = -p[0];
	res[1] = -p[1];
	res[2] = -p[2];
    res[3] = -p[3];
	return (res); 
  };

  inline Vec4 operator* (const Vec4 & P) const {
	Vec4 res;
	res[0] = p[0] * P[0];
	res[1] = p[1] * P[1];
	res[2] = p[2] * P[2];
    res[3] = p[3] * P[3];
	return (res); 
  };

  inline Vec4 operator* (T s) const {
	Vec4 res;
	res[0] = p[0] * s;
	res[1] = p[1] * s;
	res[2] = p[2] * s;
    res[3] = p[3] * s;
	return (res); 
  };

  inline Vec4 operator/ (const Vec4 & P) const {
	Vec4 res;
	res[0] = p[0] / P[0];
	res[1] = p[1] / P[1];
	res[2] = p[2] / P[2];
    res[3] = p[3] / P[3];
	return (res); 
  };

  inline Vec4 operator/ (T s) const {
	Vec4 res;
	res[0] = p[0] / s;
	res[1] = p[1] / s;
	res[2] = p[2] / s;
    res[3] = p[3] / s;
	return (res); 
  };
   
  inline bool operator == (const Vec4 & a) const {
	return(p[0] == a[0] && p[1] == a[1] && p[2] == a[2] && p[3] == a[3]);
  };
	
  inline bool operator != (const Vec4 & a) const {
	return(p[0] != a[0] || p[1] != a[1] || p[2] != a[2] || p[3] != a[3]);
  };
		
  inline bool operator < (const Vec4 & a) const {
	return(p[0] < a[0] && p[1] < a[1] && p[2] < a[2] && p[3] < a[3]);
  };
		
  inline bool operator >= (const Vec4 &a) const {
	return(p[0] >= a[0] && p[1] >= a[1] && p[2] >= a[2] && p[3] >= a[3]);
  };

  
  /////////////////////////////////////////////////////////////////

  inline Vec4 & init (T x, T y, T z, T w) {
	p[0] = x;
	p[1] = y;
	p[2] = z;
    p[3] = w;
	return (*this);
  };

  inline T squaredLength() const {
        return (dot (*this, *this));
  };
	
  inline T length() const {
        return (T)sqrt (squaredLength());
  };

  /// Return length after normalization
  inline T normalize (void) {
        T l = length ();
        if (l == 0.0f)
	  return 0;
        T invL = 1.0f / l;
        p[0] *= invL;
        p[1] *= invL;
        p[2] *= invL;
        p[3] *= invL;
        return l;
  };

		
  
  inline Vec4 projectOn (const Vec4 & N, const Vec4 & P) const {
	T w = dotProduct (((*this) - P), N);
	return (*this) - (N * w);
  }
    

protected:
  T p[4];
};


template <class T>
inline T dist (const Vec4<T> & a, const Vec4<T> & b) {
    return (a-b).length ();
}

template <class T>
inline T dot (const Vec4<T> & a, const Vec4<T> & b) {
      return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]+ a[3] * b[3]);
}

template <class T>
inline Vec4<T> cross (const Vec4<T> & a, const Vec4<T> & b) {
    Vec4<T> r;
    r[0] = a[1] * b[2] - a[2] * b[1];
    r[1] = a[2] * b[0] - a[0] * b[2];
    r[2] = a[0] * b[1] - a[1] * b[0];
    r[3]=1;
    return r;
}

template <class T>
inline Vec4<T> normalize (const Vec4<T> & x) {
    Vec4<T> n (x);
    n.normalize ();
    return n;
}

template <class T>
inline Vec4<T> interpolate (const Vec4<T> & u, const Vec4<T> & v, float alpha) {
      return (u * (1.0 - alpha) + v * alpha);
}

/**
 * Cartesion to polar coordinates conversion.
 * Result:
 * [0] = length
 * [1] = angle with z-axis
 * [2] = angle of projection into x,y, plane with x-axis
 */


template <class T>
inline Vec4<T> projectOntoVector (const Vec4<T> & v1, const Vec4<T> & v2) {
      return v2 * dotProduct (v1, v2);
}

template <class T>
inline Vec4<T> operator * (const T &s, const Vec4<T> &P) {
   return (P * s);
}

template <class T>
std::ostream & operator<< (std::ostream & output, const Vec4<T> & v) {
  output << v[0] << " " << v[1] << " " << v[2]<< " " << v[3];
  return output;
}

template <class T>
std::istream & operator>> (std::istream & input, Vec4<T> & v) {
  input >> v[0] >> v[1] >> v[2]>> v[3];
  return input;
}

typedef Vec4<float> Vec4f;
typedef Vec4<double> Vec4d;
typedef Vec4<int> Vec4i;

    
// Some Emacs-Hints -- please don't remove:
//
//  Local Variables:
//  mode:C++
//  tab-width:4
//  End:
