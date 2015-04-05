//
//  CellTexture.cpp
//  CSE168FinalProject
//
//  Created by Mona Liu on 6/5/14.
//
//

#include <vector>
#include "CellTexture.h"

CellTexture::CellTexture() {
    wn = new WorleyNoise();
    seed = 9743;
    distanceMode = WorleyNoise::EUCLIDIAN;
    combineMode = WorleyNoise::D2;
}

CellTexture::CellTexture(float sca, int s, int d, int c) {
    scale = sca;
    wn = new WorleyNoise();
    seed = s;
    distanceMode = d;
    combineMode = c;
}
float CellTexture::getTexture(const Vector3& pos) {
    vector<float> dists = vector<float>();
    dists.resize(3);

    Vector3 temp = Vector3(pos.x+TEXTOFF, pos.y+TEXTOFF, pos.z+TEXTOFF);
    temp.Scale(scale);
    float n = wn->Noise(temp, seed, distanceMode, dists, combineMode);
    return n;
}
