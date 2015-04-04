////////////////////////////////////////
// Color.cpp
////////////////////////////////////////

#include "Color.h"

////////////////////////////////////////////////////////////////////////////////

Color Color::WHITE(1.0,1.0,1.0);
Color Color::GREY(0.25,0.25,0.25);
Color Color::BLACK(0.0,0.0,0.0);
Color Color::RED(1.0,0.0,0.0);
Color Color::YELLOW(1.0,1.0,0.0);
Color Color::BLUE(0.0,0.0,1.0);
Color Color::GREEN(0.0,0.75,0.0);

////////////////////////////////////////////////////////////////////////////////

Color::Color() {
    Red = Green = Blue = 1.0;
}

Color::Color(float r, float g, float b) {
    Red=r;
    Green=g;
    Blue=b;
}

void Color::Set(float r, float g, float b) {
    Red=r;
    Green=g;
    Blue=b;
}

void Color::Add(const Color c) {
    Red += c.Red;
    Green += c.Green;
    Blue += c.Blue;
}

void Color::AddScaled(const Color c, float s) 	{
    Red += s * c.Red;
    Green += s * c.Green;
    Blue += s * c.Blue;
}

void Color::Scale(float s) {
    Red *= s;
    Green *= s;
    Blue *= s;
}

void Color::Scale(const Color c, float s) {
    Red = s * c.Red;
    Green = s * c.Green;
    Blue = s * c.Blue;
}

void Color::Multiply(const Color c) {
    Red *= c.Red;
    Green *= c.Green;
    Blue *= c.Blue;
}

int Color::ToInt() {
    int r = (Red<0) ? 0 : ((Red>=1.0) ? 255 : int(Red*256.0f));
    int g = (Green<0) ? 0 : ((Green>=1.0) ? 255 : int(Green*256.0f));
    int b = (Blue<0) ? 0 : ((Blue>=1.0) ? 255 : int(Blue*256.0f));
    return (r<<16) | (g<<8) | b;
}

void Color::FromInt(int c) {
    Set(float((c>>16)&0xff)/255.0f,float((c>>8)&0xff)/255.0f,float(c&0xff)/255.0f);
}

Color Color::Difference(const Color c) {
    float r = Red - c.Red;
    float g = Green - c.Green;
    float b = Blue - c.Blue;
    
    return Color(r, g, b);
}

