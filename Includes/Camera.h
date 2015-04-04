//
//  Camera.h
//  CSE168Project1
//
//  Created by Mona Liu on 4/4/14.
//
//

#ifndef __CSE168Project1__Camera__
#define __CSE168Project1__Camera__

#include "Bitmap.h"
#include "Scene.h"

class Camera {
    
public:
    Camera();
    void SetResolution(int,int);
    
    void Render(Scene&);
    void SaveBitmap(const char*);
    
    void SetSuperSample(int);
    
private:
    float numTri;
    
    int XRes,YRes, SuperSample;
    Bitmap BMP;
    
    //helper function
    void RenderPixel (int, int, Scene*);
};


#endif /* defined(__CSE168Project1__Camera__) */
