//
//  CellTexture.h
//  CSE168FinalProject
//
//  Created by Mona Liu on 6/5/14.
//
//

#ifndef __CSE168FinalProject__CellTexture__
#define __CSE168FinalProject__CellTexture__

#include "Texture.h"

class CellTexture : public Texture {
    
public:
    CellTexture();
    CellTexture(float, int, int, int);
    float getTexture(const Vector3& pos);
    
private:
    WorleyNoise *wn;
    
    float scale;
    int seed;
    int distanceMode;
    int combineMode;
};

#endif /* defined(__CSE168FinalProject__CellTexture__) */
