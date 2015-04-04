//
//  PerlinNoise.cpp
//  CSE168FinalProject
//
//  Created by Mona Liu on 6/2/14.
//
//

#include "PerlinNoise.h"

PerlinNoise::PerlinNoise() {
    persistence = 0.5;
    octaves = 4;
    
    // Initialize the permutation vector with the reference values
	p = {
		151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
		8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
		35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,
		134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
		55,46,245,40,244,102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
		18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,
		250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
		189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167,
		43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,
		97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,
		107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };
	// Duplicate the permutation vector
	p.insert(p.end(), p.begin(), p.end());
}

void PerlinNoise::Seed(unsigned int seed) {
    //initialize vector and fill
    p.resize(256);
    std::iota(p.begin(), p.end(), 0);
    
    //randomize
    std::default_random_engine eng(seed);
    std::shuffle(p.begin(), p.end(), eng);
    
    //duplicate
    p.insert(p.end(), p.begin(), p.end());
}

////////////////////////////////////////////////////////////////////////////////

float PerlinNoise::fade (float t) {
    return t * t * t * ( t * (t * 6 - 15) + 10);
}

float PerlinNoise::lerp (float x, float a, float b) {
    return a + x * (b - a);
}

float PerlinNoise::gradient(int hash, float x, float y, float z) {
    // get lowest 4 bits of code
    int h = hash & 15;
    // convert to 12 gradient directions
    float u = (h < 8) ? x : y;
    float v = (h < 4) ? y : (h==12 || h==14) ? x : z;
    
    return ( ((h&1) == 0) ? u : -u) + ( ((h&2) == 0) ? v : -v);
}

float PerlinNoise::turbulence(Vector3 pos, float size) {
    float value = 0.0f;
    float initSize = size;
    
    while (size >= 1.0f) {
        value += getNoise(pos/size) * size;
        size = size / 2.0f;
    }
    
    return(0.5f * value / initSize);
}

////////////////////////////////////////////////////////////////////////////////

float PerlinNoise::getNoise(Vector3 pos) {
    //combination of interpolate Noise and Noise functions
    //uses permutation table to randomly generate number from 0-255
    
    //get unit cube
    int ix = int(pos.x) & 255;
    int iy = int(pos.y) & 255;
    int iz = int(pos.z) & 255;
    
    float xfac = pos.x - floor(pos.x);
    float yfac = pos.y - floor(pos.y);
    float zfac = pos.z - floor(pos.z);
    
    float u = fade(xfac);
    float v = fade(yfac);
    float w = fade(zfac);
    
    //hash coordinates
    int a = p[ix]+iy;
    int a2 = p[a]+iz;
    int ab = p[a+1]+iz;
    int b = p[ix+1]+iy;
    int ba = p[b]+iz;
    int b2 = p[b+1]+iz;
    
    float blendb = lerp(u, gradient(p[a2], xfac  , yfac, zfac),
                        gradient(p[ba], xfac-1, yfac, zfac));
    float blendc = lerp(u, gradient(p[ab], xfac  , yfac-1, zfac),
                        gradient(p[b2], xfac-1, yfac-1, zfac));
    float lerpb = lerp(v, blendb, blendc);
    
    blendb = lerp(u, gradient(p[a2+1], xfac  , yfac  , zfac-1),
                  gradient(p[ba+1], xfac-1, yfac  , zfac-1));
    blendc = lerp(u, gradient(p[ab+1], xfac  , yfac-1, zfac-1),
                  gradient(p[b2+1], xfac-1, yfac-1, zfac-1));
    float lerpc = lerp(v, blendb, blendc);
    
    return lerp(w, lerpb, lerpc);
}

////////////////////////////////////////////////////////////////////////////////

float PerlinNoise::CosineInterpolate(float a, float b, float x) {
    //cosine interpolation
    float r = x * PI;
    float f = (1.0f - cosf(r)) * 0.5f;
    return (a*(1.0f-f)) + (b*f);
}

float PerlinNoise::PerlinNoise2D(float x, float y) {
    
    //return ImprovedNoise(x, y, 0.8);
    
    
    float total = 0;
    for (int i = 0; i < octaves-1; i++) {
        int frequency = pow(2, i);
        int amplitude = pow(persistence, i);
        total += InterpolateNoise(i, x*frequency, y*frequency) * amplitude;
    }
    return total;
}

float PerlinNoise::Noise(int i, int x, int y) {
    int n = x + y * 57;
    int m = (n << 13) ^ n;
    
    //choose different noise functions
    if (i == 1)
        return ( 1.0 - ((m*(m*m*99173 + 584609)+4795410089) & 0x7fffffff) /
                1100344211);
    if (i == 2)
        return ( 1.0 - ((m*(m*m*42577 + 47783)+1000045097) & 0x7fffffff) /
                2145101801);
    if (i == 3)
        return ( 1.0 - ((m*(m*m*29311 + 789221)+1001854361) & 0x7fffffff) /
                3916211917);
    if (i == 4)
        return ( 1.0 - ((m*(m*m*7494 + 180287)+1248428663) & 0x7fffffff) /
                1780724107);

    return ( 1.0f - ((m*(m*m*15731 + 789221)+1376312589) & 0x7fffffff) /
            1073741824.0f);
}

float PerlinNoise::Smooth(int i, int x, int y) {
    
    float corners = ( Noise(i,x-1,y-1) + Noise(i,x+1,y-1) +
                      Noise(i,x-1,y+1) + Noise(i,x+1,y+1) ) / 16.0f;
    
    float sides   = ( Noise(i,x-1,y)  + Noise(i,x+1,y) +
                      Noise(i,x, y-1) + Noise(i,x,y+1) ) / 8.0f;
    
    float center  =  Noise(i, x, y) / 4.0f;
    
    return corners + sides + center;
}

float PerlinNoise::InterpolateNoise(int i, float x, float y) {
    int ix = int(x);
    float xfrac = x - ix;
    int iy = int(y);
    float yfrac = y - iy;
    
    float v1 = Smooth(i, ix  ,  iy);
    float v2 = Smooth(i, ix+1 , iy);
    float v3 = Smooth(i, ix , iy+1);
    float v4 = Smooth(i, ix+1,iy+1);
    
    float i1 = CosineInterpolate(v1, v2, xfrac);
    float i2 = CosineInterpolate(v3, v4, xfrac);
    
    return CosineInterpolate(i1, i2, yfrac);
}

////////////////////////////////////////////////////////////////////////////////
