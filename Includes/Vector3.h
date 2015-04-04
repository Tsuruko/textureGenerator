////////////////////////////////////////
// Vector3.h
////////////////////////////////////////

#ifndef CSE168_VECTOR3_H
#define CSE168_VECTOR3_H

#include "Core.h"

////////////////////////////////////////////////////////////////////////////////

class Vector3 {
public:
	Vector3();
	Vector3(float x0,float y0,float z0);
	void Set(float x0,float y0,float z0);
	void Zero();

	// Math routines
	void Add(const Vector3 &a);
	void Add(const Vector3 &a,const Vector3 &b);
	void AddScaled(const Vector3 &a,float s);
	void AddScaled(const Vector3 &a,const Vector3 &b,float s);
	void Subtract(const Vector3 &a);
	void Subtract(const Vector3 &a,const Vector3 &b);
	void Negate();
	void Negate(const Vector3 &a);
	void Scale(float s);
	void Scale(float s,const Vector3 &a);
	float Dot(const Vector3 &a) const;
	void Cross(const Vector3 &a,const Vector3 &b);
	float Magnitude() const;
	float Magnitude2() const;
	void Normalize();
	float Distance(const Vector3 &a) const;
	float Distance2(const Vector3 &a) const;
	void Lerp(float t,const Vector3 &a,const Vector3 &b);

	// Operator overloads
	Vector3 operator+(const Vector3 &a) const;
	const Vector3 &operator+=(const Vector3 &a) {x+=a.x; y+=a.y; z+=a.z; return *this;}
	Vector3 operator-(const Vector3 &a) const;
	const Vector3 &operator-=(const Vector3 &a) {x-=a.x; y-=a.y; z-=a.z; return *this;}
	Vector3 operator-() const;

	Vector3 operator*(float s) const;
	Vector3 operator*(const Vector3 &a) const;
	Vector3 operator*=(float s);
	const Vector3 &operator*=(const Vector3 &a) {x*=a.x; y*=a.y; z*=a.z; return *this;}

	Vector3 operator/(float s) const;
	Vector3 operator/(const Vector3 &a) const;
	const Vector3 &operator/=(float s) {float inv=1.0f/s; x*=inv; y*=inv; z*=inv; return *this;}
	const Vector3 &operator/=(const Vector3 &a) {x/=a.x; y/=a.y; z/=a.z; return *this;}

	float &operator[](int i) {return(((float*)this)[i]);}
	const float operator[](int i) const	;

	// Misc functions
	void Print(const char *name=0) const;

	// Static vectors
	static Vector3 XAXIS,YAXIS,ZAXIS, MINUSXAXIS, MINUSYAXIS, MINUSZAXIS;
	static Vector3 ORIGIN;

public:
	float x,y,z;
};

inline Vector3 operator*(float s,const Vector3 &a)				{return Vector3(s*a.x,s*a.y,s*a.z);}

////////////////////////////////////////////////////////////////////////////////

#endif
