//
//  WoodTexture.cpp
//  CSE168FinalProject
//
//  Created by Mona Liu on 6/3/14.
//
//

#include "WoodTexture.h"

WoodTexture::WoodTexture() {
    pn = new PerlinNoise();
}

float WoodTexture::getTexture(const Vector3 &pos) {
    Vector3 temp = Vector3(pos.x+TEXTOFF, pos.y+TEXTOFF, pos.z+TEXTOFF);
    float n = 20 * pn->getNoise(temp);
    return n - floor(n);
}