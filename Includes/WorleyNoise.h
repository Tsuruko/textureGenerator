//
//  WorleyNoise.h
//  CSE168FinalProject
//
//  Created by Mona Liu on 6/5/14.
//
//

#ifndef __CSE168FinalProject__WorleyNoise__
#define __CSE168FinalProject__WorleyNoise__

#include <vector>
#include "Vector3.h"

class WorleyNoise {
    
public:
    WorleyNoise();
    
    float Noise(Vector3, int, int, std::vector<float>, int);
    
    static float EuclidianDist(Vector3 p1, Vector3 p2);
    static float ManhattanDist(Vector3 p1, Vector3 p2);
    static float ChebyshevDist(Vector3 p1, Vector3 p2);
    
    static const int EUCLIDIAN = 10;
    static const int MANHATTAN = 11;
    static const int CHEBYSHEV = 12;
    
    static const int D1 = 20;
    static const int D2 = 21;
    static const int D3 = 22;

private:
    
    static unsigned int lcgRandom(unsigned int lastValue);
    unsigned int hash(unsigned int i, unsigned int j, unsigned int k);
    static unsigned int probLookup(unsigned int value);
    
    const unsigned int FNV_PRIME = 16777619;
    const unsigned int OFFSET_BASIS = 2166136261;
};

#endif /* defined(__CSE168FinalProject__WorleyNoise__) */
