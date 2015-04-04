////////////////////////////////////////
// Main.cpp
////////////////////////////////////////

#include "Camera.h"
#include "Scene.h"
#include "WoodTexture.h"
#include "MarbleTexture.h"
#include "CellTexture.h"
#include "CloudTexture.h"

#include <iostream>
#include <string>

#ifdef _WIN32
#define FILE_SEP    0
#else
#define FILE_SEP    1
#endif

using namespace std;

string fSEP = "/";
string APP_PATH = "";
string concat = "";

void usage() {
    cout << "Usage: texture [-option [arg ...] ...]" << endl;
    cout << "--help" << endl;
    cout << "valid texture arguments:" << endl;
    cout << "cloud" << endl;
    cout << "wood" << endl;
    cout << "marble" << endl;
    cout << "lava" << endl;
    cout << "<texture>" << endl;
    cout << "<texture> <xsize> <ysize>" << endl;

    exit(0);
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc,char **argv) {
    if (FILE_SEP == 0) fSEP = "\\";
    APP_PATH = argv[0];
    
    string::size_type i = APP_PATH.find_last_of(fSEP);
    if (i != string::npos) APP_PATH.erase(i+1);
    
    if (argc < 2) {
        usage();
    }
    
    // Create scene
    Scene scn;
    // used photoshop color spectrum to select colors
    Color c;
    
    if (strcmp(argv[1], "cloud") == 0) {
        CloudTexture cloud = CloudTexture();
        scn.SetSkyColor(Color(0.8f, 0.9f, 1.0f));
        scn.SetSkyTexture(&cloud);
    } else if (strcmp(argv[1], "wood") == 0) {
        c.FromInt(0x7906131);
        WoodTexture wood = WoodTexture();
        scn.SetSkyColor(c);
        scn.SetSkyTexture(&wood);
    } else if (strcmp(argv[1], "marble") == 0) {
        c.FromInt(0xb2daed);
        MarbleTexture marble = MarbleTexture(40.0f);
        scn.SetSkyColor(c);
        scn.SetSkyTexture(&marble);
    } else if (strcmp(argv[1], "lava") == 0) {
        c.FromInt(0x8e1b1b);
        CellTexture latex = CellTexture(10.0f, 5550, WorleyNoise::MANHATTAN, WorleyNoise::D3);
        scn.SetSkyColor(c);
        scn.SetSkyTexture(&latex);
    } else {
        usage();
    }
    
    int xSize = 800;
    int ySize = 600;
    
    if (argc > 2) {
        if (argc != 4) usage();
        
        
        xSize = atoi(argv[2]);
        ySize = atoi(argv[3]);
        
    }

    ////////////// Camera ///////////////////
    // Create camera
    Camera cam;
    cam.SetSuperSample(10);
    cam.SetResolution(xSize,ySize);
    
    //Render image
    cam.Render(scn);
    concat = APP_PATH + "texture.bmp";
    cam.SaveBitmap(concat.c_str());
    
}

////////////////////////////////////////////////////////////////////////////////