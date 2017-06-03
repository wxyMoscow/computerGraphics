#ifndef IMAGE_H
#define IMAGE_H
#include "EasyBMP.h"
//This is the image generating library
#include "vec.h"
/*
The purpose of this class is to serve as an interface between the
main program and whichever image generating library we're using.
The pixel identified by (i, j) returns line i and column j
(0,0) (0,1) (0,2) (0,3) ...
(1,0) (1,1)
(2,0)        ...
(3,0)
...
*/

class Image
{
    public:
        Image(int w, int h);
		//This is a constructor of the image object with width w, height h, and bit depth 24
        Image(int w, int h, int d);
		//Same as before, but dwith bit depth d
        void setColour(int i, int j, int r, int g, int b);
		//Sets the colour of pixel (i, j) as (r, g, b)
        void setColour(int i, int j, int c[3]);
		//Uses the integer triple c instead
        void setColour(int i, int j, Vec v);
		//Uses the vector v instead
        void setAlpha(int i, int j, int alpha);
		//Sets the alpha layer of pixel (i, j)
        int getHeight();
		//Returns image height
        int getWidth();
		//Returns image width
        void setHeight(int h);
		//Sets image height
        void setWidth(int w);
		//Sets image width
        void setSize(int w, int h);
		//Sets both
        void WriteToFile(char* s);
		//Writes to file named s
    protected:
    private:
        BMP _im;
};


#endif // IMAGE_H
