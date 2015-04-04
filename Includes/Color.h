////////////////////////////////////////
// Color.h
////////////////////////////////////////

#ifndef CSE168_COLOR_H
#define CSE168_COLOR_H

#include "Core.h"

////////////////////////////////////////////////////////////////////////////////

class Color {
public:
	Color();
	Color(float, float, float);

	void Set(float r,float g,float b);

	void Add(const Color c);
	void AddScaled(const Color c,float s);
	void Scale(float s);
	void Scale(const Color c,float s);
	void Multiply(const Color c);
    
    Color Difference(const Color c);

	int ToInt();
	void FromInt(int c);

	static Color WHITE,GREY,BLACK;
	static Color RED,YELLOW,BLUE,GREEN;

private:
	float Red,Green,Blue;
};

////////////////////////////////////////////////////////////////////////////////

#endif
