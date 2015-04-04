//
//  WoodTexture.h
//  CSE168FinalProject
//
//  Created by Mona Liu on 6/3/14.
//
//

#ifndef __CSE168FinalProject__WoodTexture__
#define __CSE168FinalProject__WoodTexture__

#include "Texture.h"

class WoodTexture : public Texture {
    
public:
    WoodTexture();
    float getTexture(const Vector3& pos);
    
    PerlinNoise *pn;
};

#endif /* defined(__CSE168FinalProject__WoodTexture__) */
