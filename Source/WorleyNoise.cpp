//
//  WorleyNoise.cpp
//  CSE168FinalProject
//
//  Created by Mona Liu on 6/5/14.
//
// see http://aftbit.com/cell-noise-2/ for original java implementation

#include "WorleyNoise.h"

WorleyNoise::WorleyNoise() {
    
}

float WorleyNoise::EuclidianDist(Vector3 p1, Vector3 p2) {
    return p1.Distance2(p2);
}

float WorleyNoise::ManhattanDist(Vector3 p1, Vector3 p2) {
    return fabsf(p1.x - p2.x) + fabsf(p1.y - p2.y) + fabsf(p1.z - p2.z);
}

float WorleyNoise::ChebyshevDist(Vector3 p1, Vector3 p2) {
    Vector3 diff = p1 - p2;
    return Max3(fabsf(diff.x), fabsf(diff.y), fabsf(diff.z));
}

/// <summary>
/// Given a uniformly distributed random number this function returns the number of feature points in a given cube.
/// </summary>
/// <param name="value">a uniformly distributed random number</param>
/// <returns>The number of feature points in a cube.</returns>
// Generated using mathmatica with "AccountingForm[N[Table[CDF[PoissonDistribution[4], i], {i, 1, 9}], 20]*2^32]"
unsigned int WorleyNoise::probLookup(unsigned int value) {
    if (value < 393325350) return 1;
    if (value < 1022645910) return 2;
    if (value < 1861739990) return 3;
    if (value < 2700834071) return 4;
    if (value < 3372109335) return 5;
    if (value < 3819626178) return 6;
    if (value < 4075350088) return 7;
    if (value < 4203212043) return 8;
    return 9;
}

/// <summary>
/// LCG Random Number Generator.
/// LCG: http://en.wikipedia.org/wiki/Linear_congruential_generator
/// </summary>
/// <param name="lastValue">The last value calculated by the lcg or a seed</param>
/// <returns>A new random number</returns>
unsigned int WorleyNoise::lcgRandom(unsigned int lastValue) {
    return (unsigned int)((1103515245u * lastValue + 12345u) % 0x100000000u);
}
unsigned int WorleyNoise::hash(unsigned int i, unsigned int j, unsigned int k) {
    return (unsigned int)((((((OFFSET_BASIS ^ (unsigned int)i) * FNV_PRIME) ^
                             (unsigned int)j) * FNV_PRIME) ^ (unsigned int)k) * FNV_PRIME);
}

float WorleyNoise::Noise(Vector3 pos, int seed, int distanceFunc,std::vector<float> distances, int combine) {
    unsigned int lRand, numberfeatPts;
    Vector3 rDiff, featPt;
    float cubeX, cubeY, cubeZ;
        
    //Initialize values in distance array to large values
    for (int i = 0; i < distances.size(); i++) {
        distances[i] = 6666;
    }
    
    //1. Determine which cube the evaluation point is in
    int evalCubeX = (int)floor(pos.x);
    int evalCubeY = (int)floor(pos.y);
    int evalCubeZ = (int)floor(pos.z);
        
    for (int i = -1; i < 2; ++i)
        for (int j = -1; j < 2; ++j)
            for (int k = -1; k < 2; ++k) {
                cubeX = evalCubeX + i;
                cubeY = evalCubeY + j;
                cubeZ = evalCubeZ + k;
                    
                //2. Generate a reproducible random number generator for the cube
                lRand = lcgRandom(hash((unsigned int)(cubeX+seed), (unsigned int)(cubeY), (unsigned int)(cubeZ)));
                //3. Determine how many feature points are in the cube
                numberfeatPts = probLookup(lRand);
                //4. Randomly place the feature points in the cube
                for (unsigned int l = 0; l < numberfeatPts; ++l) {
                    lRand = lcgRandom(lRand);
                    rDiff.x = (float)lRand / 0x100000000;
                        
                    lRand = lcgRandom(lRand);
                    rDiff.y = (float)lRand / 0x100000000;
                        
                    lRand = lcgRandom(lRand);
                    rDiff.z = (float)lRand / 0x100000000;
                        
                    featPt = Vector3(rDiff.x+cubeX, rDiff.y+cubeY, rDiff.z+cubeZ);
                        
                    //5. Find the feature point closest to the evaluation point.
                    //This is done by inserting the distances to the feature points into a sorted list
                    float dist = 0;
                    if (distanceFunc == EUCLIDIAN) dist = EuclidianDist(pos, featPt);
                    if (distanceFunc == MANHATTAN) dist = ManhattanDist(pos, featPt);
                    if (distanceFunc == CHEBYSHEV) dist = ChebyshevDist(pos, featPt);
//
                    float temp;
                    //sorted insertion
                    for (int i = (int)distances.size()-1; i >= 0; i--) {
                        if (dist > distances[i]) break;
                        temp = distances[i];
                        distances[i] = dist;
                        if (i+1 < (int)distances.size()) distances[i+1] = temp;
                    }
                }
                //6. Check the neighboring cubes to ensure their are no closer evaluation points.
                // This is done by repeating steps 1 through 5 above for each neighboring cube
            }
    float color = 0.0f;
    if (combine == D1) color = distances[0];
    if (combine == D2) color = distances[1] - distances[0];
    if (combine == D3) color = distances[2] - distances[0];
    
    if(color < 0.0f) color = 0.0f;
    if(color > 1.0f) color = 1.0f;
    return color;
}