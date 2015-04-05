//
//  Scene.h
//  CSE168Project1
//
//  Created by Mona Liu on 4/4/14.
//
//

#ifndef __CSE168Project1__Scene__
#define __CSE168Project1__Scene__

#include "Bitmap.h"
#include "Color.h"
#include "Texture.h"

class Scene {
    
public:
    Scene();
    void SetResolution(int,int);
    
    void Render();
    void SaveBitmap(const char*);
    
    void setColor(const Color c);
    void setTexture(Texture *t);
    
private:
    int XRes,YRes;
    
    Color baseColor;
    Texture *myTexture;
    
    Bitmap BMP;
};


#endif /* defined(__CSE168Project1__Scene__) */
