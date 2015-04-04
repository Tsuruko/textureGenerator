////////////////////////////////////////
// Bitmap.cpp
////////////////////////////////////////

#include "Bitmap.h"

////////////////////////////////////////////////////////////////////////////////

struct BitmapHeader {
	int FileSize;
	int Reserved;
	int StartAddress;
	int HeaderSize;
	short Width;
	short Height;
	short ColorPlanes;
	short BitsPerPixel;
};

////////////////////////////////////////////////////////////////////////////////

Bitmap::Bitmap() {
  XRes=0;
  YRes=0;
  Pixel = new int[XRes*YRes];
}

Bitmap::~Bitmap() {
 //   delete []Pixel;
}

Bitmap::Bitmap(int x, int y) {
    XRes = x;
    YRes = y;
    Pixel = new int[XRes*YRes];
}

bool Bitmap::SaveBMP(const char *filename) {
	BitmapHeader head;
	head.FileSize=sizeof(BitmapHeader)+2+XRes*YRes*sizeof(int);
	head.Reserved=0;
	head.StartAddress=sizeof(BitmapHeader)+2;

	head.HeaderSize=12;
	head.Width=XRes;
	head.Height=YRes;
	head.ColorPlanes=1;
	head.BitsPerPixel=32;

	FILE * f;
	f = fopen(filename,"w");
	if(f == nullptr) {
		printf("Can't open '%s'\n",filename);
		return false;
	}
	short magic=19778;
	fwrite(&magic,sizeof(short),1,f);
	fwrite(&head,sizeof(BitmapHeader),1,f);
	fwrite(Pixel,sizeof(int),XRes*YRes,f);
	fclose(f);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
