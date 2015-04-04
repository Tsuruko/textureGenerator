//
//  PerlinNoise.h
//  CSE168FinalProject
//
//  Created by Mona Liu on 6/2/14.
//
//

#ifndef __CSE168FinalProject__PerlinNoise__
#define __CSE168FinalProject__PerlinNoise__

#include <vector>
#include <numeric>
#include <random>
#include "Vector3.h"

static const int NumPerm = 512;

class PerlinNoise {
    
public:
    PerlinNoise();

    void Seed(unsigned int seed);
    
    float PerlinNoise2D(float, float);
    float getNoise(Vector3);
    float turbulence(Vector3 pos, float size);

    //previous implementation
    float persistence;
    float octaves;
    
private:
    std::vector<int> p;
    float ImprovedNoise(float x, float y, float z);

    //helper functions
    static float fade(float);
    static float lerp(float, float, float);
    static float gradient(int, float, float, float);
    
    //previous implementation
    float Noise(int i, int x, int y);
    float Smooth(int i, int x, int y);
    float InterpolateNoise(int i, float x, float y);
    float CosineInterpolate(float, float, float);
};

#endif /* defined(__CSE168FinalProject__PerlinNoise__) */
