//
//  Camera.cpp
//  CSE168Project1
//
//  Created by Mona Liu on 4/4/14.
//
//

#include <math.h>
#include <time.h>
#include "Camera.h"

Camera::Camera() {
    BMP = Bitmap();
    XRes = 0;
    YRes = 0;
    numTri = 0.0f;
    SuperSample = 1.0f;
}
void Camera::SetResolution(int x, int y) {
    XRes = x;
    YRes = y;
    BMP = Bitmap(x, y);
}

void Camera::SetSuperSample(int s) {
    SuperSample = s;
}

////////////////////////////////////////////////////////////////////////////////

void Camera::RenderPixel(int x, int y, Scene *s) {
    Color pixCol = Color::BLACK;
    
    for (int i = 0; i < SuperSample; i++) {
        for (int j = 0; j < SuperSample; j++) {

            Color shade = s->GetSkyColor();

            //this is for cloud
            //float n = s->getTexture(Vector3(200.0f*x/XRes, 200.0f*y/YRes, 1.0f));
            
            
            float n = s->getTexture(Vector3(1.0f*x/XRes, 1.0f*y/YRes, 1.0f));
            Color d = s->GetSkyColor().Difference(Color::WHITE);
            d.Scale(n);
            shade.Add(d);
            
            pixCol.AddScaled(shade, 1.0f/(float)(SuperSample*SuperSample));
        }

    }
    BMP.SetPixel(x, y, pixCol.ToInt());
}

void Camera::Render(Scene &s) {
    clock_t t = clock();
    
    numTri = 0;
    
    int progress = 0;
    for(int y = 0; y < YRes; y++) {
        //debugging print
        printf("Progress : %f\n", ((float)progress)/YRes);
        for(int x = 0; x < XRes; x++) {
            RenderPixel(x, y, &s);
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

void Camera::SaveBitmap(const char *filename) {
    BMP.SaveBMP(filename);
}
