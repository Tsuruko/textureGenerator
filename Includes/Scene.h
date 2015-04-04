////////////////////////////////////////
// Scene.h
////////////////////////////////////////

#ifndef CSE168_SCENE_H
#define CSE168_SCENE_H

#include "Color.h"
#include <vector>
#include "Texture.h"

////////////////////////////////////////////////////////////////////////////////

class Scene {
public:
	Scene()										{SkyColor.Set(0.2f,0.2f,0.5f);
                                                skyText = nullptr;}

	void SetSkyColor(const Color sky)			{SkyColor = sky;}
    void SetSkyTexture(Texture *t)               {skyText = t;}
    
	Color GetSkyColor()							{return SkyColor;}
    
    float getTexture(Vector3 pos) {
        if (skyText != nullptr)
            return skyText->getTexture(pos);
        return 1.0f;
    }

private:
	Color SkyColor;
    Texture *skyText;
};

////////////////////////////////////////////////////////////////////////////////

#endif
