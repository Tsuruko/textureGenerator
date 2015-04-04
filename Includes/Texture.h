//
//  Texture.h
//  CSE168FinalProject
//
//  Created by Mona Liu on 6/3/14.
//
//

#ifndef __CSE168FinalProject__Texture__
#define __CSE168FinalProject__Texture__

#include "PerlinNoise.h"
#include "WorleyNoise.h"

class Texture {
    
public:
    virtual float getTexture(const Vector3& pos)=0;
    
};

#endif /* defined(__CSE168FinalProject__Texture__) */
