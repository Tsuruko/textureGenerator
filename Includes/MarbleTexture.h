//
//  MarbleTexture.h
//  CSE168FinalProject
//
//  Created by Mona Liu on 6/3/14.
//
//

#ifndef __CSE168FinalProject__MarbleTexture__
#define __CSE168FinalProject__MarbleTexture__

#include "Texture.h"

class MarbleTexture : public Texture {
    
public:
    MarbleTexture();
    MarbleTexture(float);
    
    void SetScale(float);
    
    float getTexture(const Vector3& pos);
    
    PerlinNoise *pn;
    
private:    
    float scale;
    float xPeriod;
    float yPeriod;
    float zPeriod;
    float turbPower;
    float turbSize;
};

#endif /* defined(__CSE168FinalProject__MarbleTexture__) */
