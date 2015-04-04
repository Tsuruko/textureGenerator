//
//  CloudTexture.h
//  CSE168FinalProject
//
//  Created by Mona Liu on 6/5/14.
//
//

#ifndef __CSE168FinalProject__CloudTexture__
#define __CSE168FinalProject__CloudTexture__

#include "Texture.h"

class CloudTexture : public Texture {
    
public:
    CloudTexture();
    CloudTexture(float);
    
    void SetScale(float);
    
    float getTexture(const Vector3& pos);
    
    PerlinNoise *pn;
    
private:
    float turbulence(Vector3 pos, float size);
    
    float scale;
    float xPeriod;
    float yPeriod;
    float zPeriod;
    float turbPower;
    float turbSize;
};

#endif /* defined(__CSE168FinalProject__CloudTexture__) */
