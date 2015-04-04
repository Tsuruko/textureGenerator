////////////////////////////////////////
// Vector3.cpp
////////////////////////////////////////

#include "Vector3.h"

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::XAXIS(1.0f,0.0f,0.0f);
Vector3 Vector3::YAXIS(0.0f,1.0f,0.0f);
Vector3 Vector3::ZAXIS(0.0f,0.0f,1.0f);
Vector3 Vector3::ORIGIN(0.0f,0.0f,0.0f);

Vector3 Vector3::MINUSXAXIS(-1.0f,0.0f,0.0f);
Vector3 Vector3::MINUSYAXIS(0.0f,-1.0f,0.0f);
Vector3 Vector3::MINUSZAXIS(0.0f,0.0f,-1.0f);

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3() {
    Zero();
}

Vector3::Vector3(float x0,float y0,float z0) {
    x = x0;
    y = y0;
    z = z0;
}

void Vector3::Set(float x0,float y0,float z0) {
    x = x0;
    y = y0;
    z = z0;
}

void Vector3::Zero() {
    x = y = z = 0.0f;
}

////////////////////////////////////////////////////////////////////////////////

// Math routines

void Vector3::Add(const Vector3 &a) {
    x += a.x;
    y += a.y;
    z += a.z;
}

void Vector3::Add(const Vector3 &a,const Vector3 &b) {
    x=a.x+b.x; y=a.y+b.y; z=a.z+b.z;
}

void Vector3::AddScaled(const Vector3 &a,float s) {
    x += s * a.x;
    y += s * a.y;
    z += s * a.z;
}

void Vector3::AddScaled(const Vector3 &a,const Vector3 &b,float s) {
    x = a.x + s*b.x;
    y = a.y + s*b.y;
    z = a.z + s*b.z;
}

void Vector3::Subtract(const Vector3 &a) {
    x -= a.x;
    y -= a.y;
    z -= a.z;
}

void Vector3::Subtract(const Vector3 &a,const Vector3 &b) {
    x=a.x-b.x;
    y=a.y-b.y;
    z=a.z-b.z;
}

void Vector3::Negate() {
    x = -x;
    y = -y;
    z = -z;
}

void Vector3::Negate(const Vector3 &a) {
    x = -a.x;
    y = -a.y;
    z = -a.z;
}

void Vector3::Scale(float s) {
    x *= s;
    y *= s;
    z *= s;
}

void Vector3::Scale(float s,const Vector3 &a) {
    x = s * a.x;
    y = s * a.y;
    z = s * a.z;
}

float Vector3::Dot(const Vector3 &a) const {
    return x*a.x + y*a.y + z*a.z;
}

void Vector3::Cross(const Vector3 &a,const Vector3 &b) {
    x = a.y*b.z - a.z*b.y;
    y = a.z*b.x - a.x*b.z;
    z = a.x*b.y - a.y*b.x;
}

float Vector3::Magnitude() const {
    return sqrtf(x*x + y*y + z*z);
}

float Vector3::Magnitude2() const {
    return x*x + y*y + z*z;
}

void Vector3::Normalize() {
    Scale(1.0f / Magnitude());
}

float Vector3::Distance(const Vector3 &a) const {
    return sqrtf((x-a.x)*(x-a.x) + (y-a.y)*(y-a.y) + (z-a.z)*(z-a.z));
}

float Vector3::Distance2(const Vector3 &a) const {
    return (x-a.x)*(x-a.x) + (y-a.y)*(y-a.y) + (z-a.z)*(z-a.z);
}

void Vector3::Lerp(float t,const Vector3 &a,const Vector3 &b) {
    float s = 1.0f - t;
    x = s*a.x + t*b.x;
    y = s*a.y + t*b.y;
    z = s*a.z + t*b.z;
}

////////////////////////////////////////////////////////////////////////////////

// Operator overloads

Vector3 Vector3::operator+(const Vector3 &a) const {
    return Vector3(x+a.x, y+a.y, z+a.z);
}

Vector3 Vector3::operator-(const Vector3 &a) const {
    return Vector3(x-a.x, y-a.y, z-a.z);
}

Vector3 Vector3::operator-() const {
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(float s) const {
    return Vector3(s*x, s*y, s*z);
}

Vector3 Vector3::operator*(const Vector3 &a) const {
    return Vector3(x*a.x, y*a.y, z*a.z);
}

Vector3 Vector3::operator*=(float s) {
    x*=s;
    y*=s;
    z*=s;
    return *this;
}

Vector3 Vector3::operator/(float s) const {
    float inv = 1.0f/s;
    return Vector3(x*inv, y*inv, z*inv);
}

Vector3 Vector3::operator/(const Vector3 &a) const {
    return Vector3(x/a.x, y/a.y, z/a.z);
}

const float Vector3::operator[](int i) const {
    return(((float*)this)[i]);
}

////////////////////////////////////////////////////////////////////////////////

void Vector3::Print(const char *name) const {
    if(name) {
        printf("%s=",name);
        printf("{%f,%f,%f}\n",x,y,z);
    }
}



