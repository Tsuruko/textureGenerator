////////////////////////////////////////
// Main.cpp
////////////////////////////////////////

#include "Core.h"
#include "Scene.h"
#include "WoodTexture.h"
#include "MarbleTexture.h"
#include "CellTexture.h"
#include "CloudTexture.h"

#ifdef _WIN32
#define FILE_SEP    0
#else
#define FILE_SEP    1
#endif

string fSEP = "/";
string APP_PATH = "";
string concat = "";

void usage() {
    cout << "Usage: " << endl;
    cout << "texture --help" << endl;
    cout << "texture <texture>" << endl;
    cout << "texture <texture> <hex color>" << endl;
    cout << "texture <texture> <xsize> <ysize>" << endl;
    cout << "texture <texture> <hex color> <xsize> <ysize>" << endl;
    cout << endl;
    cout << "valid texture arguments:" << endl;
    cout << "cloud" << endl;
    cout << "wood" << endl;
    cout << "marble" << endl;
    cout << "lava" << endl;
    cout << "cell" << endl;
    cout << endl;
    cout << "valid color arguments:" << endl;
    cout << "0x0 to 0xFFFFFF" << endl;
    cout << "0 to FFFFFF" << endl;
    exit(0);
}

////////////////////////////////////////////////////////////////////////////////

bool isDecNum(const string& s)
{
    return !s.empty() && find_if(s.begin(),
                                      s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

bool isHexNum(const string& s)
{
    return !s.empty() && find_if(s.begin(),
                                 s.end(), [](char c) { return !isxdigit(c); }) == s.end();
}

int checkColor(const char * arg) {
    string check = arg;
    //can take format 0xNUMBER or NUMBER
    if (arg[0] == '0' && arg[1] == 'x') {
        check = check.substr(2);
    }
    
    if (! isHexNum(check) ) {
        cout << "color must be a postive hexadecimal number: [" << arg << "]" << endl;
        exit(1);
    }

    int color = (int) strtol(arg,NULL,16);
    if (color < 0 || color > 0xFFFFFF) {
        cout << "color must be a postitive integer between 0x0 and 0xFFFFFF: [" << arg << "]" << endl;
        exit(1);
    }
    return color;
}

int checkSize(const char * arg) {
    if (! isDecNum(arg) ) {
        cout << "size must be a positive integer: [" << arg << "]" << endl;
        exit(1);
    }
    return atoi(arg);
}

int main(int argc,char **argv) {
    if (FILE_SEP == 0) fSEP = "\\";
    APP_PATH = argv[0];
    
    string::size_type i = APP_PATH.find_last_of(fSEP);
    if (i != string::npos) APP_PATH.erase(i+1);
    
    if (argc < 2 || argc > 5) {
        usage();
    }
    
    // Create scene
    int color;
    int xSize = 80;
    int ySize = 60;
    Scene cam;
    
    // used photoshop color spectrum to select colors
    Color c = Color::BLACK;
    
    if (strcmp(argv[1], "cloud") == 0) {
        CloudTexture cloud = CloudTexture();
        c.FromInt(0xCCE5FF);
        cam.setTexture(&cloud);
    } else if (strcmp(argv[1], "wood") == 0) {
        c.FromInt(0x7906131);
        WoodTexture wood = WoodTexture();
        cam.setTexture(&wood);
    } else if (strcmp(argv[1], "marble") == 0) {
        c.FromInt(0xb2daed);
        MarbleTexture marble = MarbleTexture(40.0f);
        cam.setTexture(&marble);
    } else if (strcmp(argv[1], "lava") == 0) {
        c.FromInt(0x8e1b1b);
        CellTexture latex = CellTexture(10.0f, 5550, WorleyNoise::MANHATTAN, WorleyNoise::D3);
        cam.setTexture(&latex);
    } else if (strcmp(argv[1], "cell") == 0) {
        c.FromInt(0xc99968);
        CellTexture gro = CellTexture(1.0f, 1305, WorleyNoise::EUCLIDIAN, WorleyNoise::D1);
        cam.setTexture(&gro);
    } else {
        usage();
    }
    

    
    if (argc == 3) {
        color = checkColor(argv[2]);
        c.FromInt( color );
    } else if (argc == 4) {
        xSize = checkSize(argv[2]);
        ySize = checkSize(argv[3]);
    } else if (argc == 5) {
        color = checkColor(argv[2]);
        c.FromInt( color );
        xSize = checkSize(argv[3]);
        ySize = checkSize(argv[4]);
    }
    cam.setColor(c);
    
    //Render image
    cam.SetResolution(xSize,ySize);
    cam.Render();
    concat = APP_PATH + "texture.bmp";
    cam.SaveBitmap(concat.c_str());
    
}

////////////////////////////////////////////////////////////////////////////////