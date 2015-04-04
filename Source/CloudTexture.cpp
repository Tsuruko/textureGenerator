//
//  CloudTexture.cpp
//  CSE168FinalProject
//
//  Created by Mona Liu on 6/5/14.
//
//

#include "CloudTexture.h"

CloudTexture::CloudTexture() {
    pn = new PerlinNoise();
    
    scale = 1.0f;
    
    xPeriod = 0.015f;
    yPeriod = 0.01f;
    zPeriod = 0.016f;
    turbPower = 5.0;
    turbSize = 32.0;
}

CloudTexture::CloudTexture(float s) {
    pn = new PerlinNoise();
    
    scale = s;
    
    xPeriod = 0.015f;
    yPeriod = 0.01f;
    zPeriod = 0.016f;
    turbPower = 5.0;
    turbSize = 32.0;
}

float CloudTexture::getTexture(const Vector3 &pos) {
    Vector3 temp = Vector3((200.0f*pos.x)+TEXTOFF, (200.0f*pos.y)+TEXTOFF, pos.z+TEXTOFF);
    temp.Scale(scale);
    return pn->turbulence(temp, turbSize);
}
