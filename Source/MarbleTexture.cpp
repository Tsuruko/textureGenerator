//
//  MarbleTexture.cpp
//  CSE168FinalProject
//
//  Created by Mona Liu on 6/3/14.
//
//

#include "MarbleTexture.h"

MarbleTexture::MarbleTexture() {
    pn = new PerlinNoise();
    
    scale = 10.0f;
    
    xPeriod = 0.015f;
    yPeriod = 0.01f;
    zPeriod = 0.016f;
    turbPower = 5.0;
    turbSize = 32.0;
}

MarbleTexture::MarbleTexture(float s) {
    pn = new PerlinNoise();
    
    scale = s;
    
    xPeriod = 0.015f;
    yPeriod = 0.01f;
    zPeriod = 0.016f;
    turbPower = 5.0;
    turbSize = 32.0;
}

float MarbleTexture::getTexture(const Vector3 &pos) {
    Vector3 temp = Vector3(pos.x+TEXTOFF, pos.y+TEXTOFF, pos.z+TEXTOFF);
    temp.Scale(scale);

    float noise = pos.x*xPeriod + pos.y*yPeriod + pos.z*zPeriod +
                    turbPower * pn->turbulence(temp, turbSize);

    return fabsf(sinf(noise * PI));
}