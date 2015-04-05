//
//  Scene.cpp
//  CSE168Project1
//
//  Created by Mona Liu on 4/4/14.
//
//

#include "Core.h"
#include "Scene.h"

Scene::Scene() {
    BMP = Bitmap();
    XRes = 0;
    YRes = 0;
    baseColor = Color::BLACK;
    myTexture = nullptr;
}

void Scene::SetResolution(int x, int y) {
    XRes = x;
    YRes = y;
    BMP = Bitmap(x, y);
}

void Scene::setColor(const Color c) {
    baseColor = c;
}
void Scene::setTexture(Texture *t) {
    myTexture = t;
}

////////////////////////////////////////////////////////////////////////////////

void Scene::Render() {
    clock_t t = clock();
    
    int progress = 0;
    for(int y = 0; y < YRes; y++) {
        //debugging print
        printf("Progress : %f\n", ((float)progress)/YRes);
        for(int x = 0; x < XRes; x++) {
            Color pixCol = baseColor;
            
            float n = myTexture->getTexture(Vector3(1.0f*x/XRes, 1.0f*y/YRes, 1.0f));
            Color d = baseColor.Difference(Color::WHITE);
            d.Scale(n);
            pixCol.Add(d);

            BMP.SetPixel(x, y, pixCol.ToInt());
        }
        progress++;
    }
    
    t = clock() - t;
    
    int numPix = XRes * YRes;
    printf("render time: %f seconds \n", ((float)t)/CLOCKS_PER_SEC);
    printf("pixels: %d\n", numPix);
    printf("done rendering\n\n");
    
}

////////////////////////////////////////////////////////////////////////////////

void Scene::SaveBitmap(const char *filename) {
    BMP.SaveBMP(filename);
}
