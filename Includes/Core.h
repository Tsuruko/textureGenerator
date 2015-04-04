////////////////////////////////////////
// Core.h
////////////////////////////////////////

#ifndef CSE168_CORE_H
#define CSE168_CORE_H

////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#ifdef _WIN32
#include <windows.h>
#endif

#define PI	3.14159265f
#define TEXTOFF 100.0f

inline int Min2(int a,int b)					{return a<b ? a : b;}
inline float Min2(float a,float b)			{return a<b ? a : b;}
inline int Max2(int a,int b)					{return a>b ? a : b;}
inline float Max2(float a,float b)			{return a>b ? a : b;}
inline int Clamp(int x,int a,int b)			{if(x<a) return a; if(x>b) return b; return x;}
inline float Clamp(float x,float a,float b)	{if(x<a) return a; if(x>b) return b; return x;}

inline float Min3(float x,float y, float z)	{
	float vmin = x;
	if (y < vmin) vmin = y;
	if (z < vmin) vmin = z;
	return vmin;
}

inline float Max3(float x, float y, float z) {
	float vmax = x;
	if (y > vmax) vmax = y;
	if (z > vmax) vmax = z;
	return vmax;
}

////////////////////////////////////////////////////////////////////////////////

#endif
