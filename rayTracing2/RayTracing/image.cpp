#include "image.h"

Image::Image(int w, int h)
{
    _im.SetSize(w,h);
    _im.SetBitDepth(24);
}

Image::Image(int w, int h, int d)
{
    _im.SetSize(w,h);
    _im.SetBitDepth(d);
}

void Image::setColour(int i, int j, int r, int g, int b)
{
    int a[3] = {r, g, b};
    setColour(i, j, a);
}

void Image::setColour(int i, int j, int c[3])
{
    _im(j,i)->Red = c[0];
    _im(j,i)->Green = c[1];
    _im(j,i)->Blue = c[2];
}

void Image::setColour(int i, int j, Vec v)
{
    _im(j,i)->Red = v[0];
    _im(j,i)->Green = v[1];
    _im(j,i)->Blue = v[2];
}

void Image::setAlpha(int i, int j, int alpha)
{
    _im(j,i)->Alpha = alpha;
}

int Image::getHeight()
{
    return _im.TellHeight();
}

int Image::getWidth()
{
    return _im.TellWidth();
}

void Image::setHeight(int h)
{
    _im.SetSize(_im.TellWidth(), h);
}

void Image::setWidth(int w)
{
    _im.SetSize(w, _im.TellHeight());
}

void Image::setSize(int w, int h)
{
    _im.SetSize(w,h);
}

void Image::WriteToFile(char* s)
{
    _im.WriteToFile(s);
}
