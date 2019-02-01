#include "Image.h"
#include <cmath>

using cs225::PNG;
using cs225::HSLAPixel;

const double kDefaultIncrease = 0.1;
const double kIlliniBlue = 216.0;
const double kIlliniOrange = 11.0;

void Image::lighten()
{
    for (int i = 0; i < (int)width(); i++)
    {
        for(int j = 0; j < (int)height(); j++)
        {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.l += kDefaultIncrease;

            if (pixel.l > 1.0)
            {
                pixel.l = 1.0;
            }
        }
    }
}

void Image::lighten(double amount)
{ 
    for (int i = 0; i < (int)width(); i++)
    {
        for(int j = 0; j < (int)height(); j++)
        {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.l += amount;

            if (pixel.l > 1.0)
            {
                pixel.l = 1.0;
            }
        }
    }
}

void Image::darken()
{
    for (int i = 0; i < (int)width(); i++)
    {
        for(int j = 0; j < (int)height(); j++)
        {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.l -= kDefaultIncrease;

            if (pixel.l < 0.0)
            {
                pixel.l = 0.0;
            }
        }
    }
}

void Image::darken(double amount)
{ 
    for (int i = 0; i < (int)width(); i++)
    {
        for(int j = 0; j < (int)height(); j++)
        {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.l -= amount;

            if (pixel.l < 0.0)
            {
                pixel.l = 0.0;
            }
        }
    }
}

void Image::saturate()
{
    for (int i = 0; i < (int)width(); i++)
    {
        for(int j = 0; j < (int)height(); j++)
        {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.s += kDefaultIncrease;

            if (pixel.s > 1.0)
            {
                pixel.s = 1.0;
            }
        }
    }
}

void Image::saturate(double amount)
{ 
    for (int i = 0; i < (int)width(); i++)
    {
        for(int j = 0; j < (int)height(); j++)
        {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.s += amount;

            if (pixel.s > 1.0)
            {
                pixel.s = 1.0;
            }
        }
    } 
}

void Image::desaturate()
{
    for (int i = 0; i < (int)width(); i++)
    {
        for(int j = 0; j < (int)height(); j++)
        {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.s -= kDefaultIncrease;

            if (pixel.s < 0.0)
            {
                pixel.s = 0.0;
            }
        }
    }
}

void Image::desaturate(double amount)
{ 
    for (int i = 0; i < (int)width(); i++)
    {
        for(int j = 0; j < (int)height(); j++)
        {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.s -= amount;

            if (pixel.s < 0.0)
            {
                pixel.s = 0.0;
            }
        }
    }
}

void Image::grayscale()
{
    for (int i = 0; i < (int)width(); i++)
    {
        for(int j = 0; j < (int)height(); j++)
        {
            HSLAPixel & pixel = getPixel(i, j);
            pixel.s = 0; 
        }
    }
}

void Image::rotateColor(double degrees)
{ 
    // might need to account for the fact that we're truncating the amount to rotate by
    if (degrees > 0)
    {
        degrees = (int)degrees % 360;
    } else
    {
        degrees = (int)degrees % -360;
    }

    for (int i = 0; i < (int)width(); i++)
    {
        for(int j = 0; j < (int)height(); j++)
        {
            HSLAPixel & pixel = getPixel(i, j);
            if (pixel.h + degrees < 0)
            {
                pixel.h += 360;
            }
            pixel.h += degrees;
            pixel.h = (int)(pixel.h) % 360;
        }
    }
}

void Image::illinify() {
    for (int i = 0; i < (int)width(); i++) {
        for (int j = 0; j < (int)height(); j++) {

            HSLAPixel & pixel = getPixel(i, j);
            double blue_distance = fabs(kIlliniBlue - pixel.h);
            double orange_distance = fabs(kIlliniOrange - pixel.h);

            if (blue_distance > 180)
            {
                 blue_distance = 360 - blue_distance;
            }

            if (orange_distance > 180)
            {
              orange_distance = 360 - orange_distance;
            }

            if (blue_distance <= orange_distance)
            {
              pixel.h = kIlliniBlue;
            } else {
              pixel.h = kIlliniOrange;
            }
        }           
    }
}

void Image::scale(double factor)
{
    Image scaled_image;
    scaled_image.resize(width() * factor, height() * factor);

    for (int i = 0; i < (int)scaled_image.width(); i++)
    {
        for(int j = 0; j < (int)scaled_image.height(); j++)
        {
            HSLAPixel & scale_pixel = scaled_image.getPixel(i, j);
            HSLAPixel & pixel = getPixel(i / factor, j / factor);
            
            scale_pixel.h = pixel.h;
            scale_pixel.s = pixel.s;
            scale_pixel.l = pixel.l;
            scale_pixel.a = pixel.a;

        }
    }

    *this = scaled_image;
}

void Image::scale(unsigned w, unsigned h)
{
    double xfactor = w/width();
    double yfactor = h/height();

    Image scaled_image;
    scaled_image.resize(w, h);
    
    for (int i = 0; i < (int)scaled_image.width(); i++)
    {
        for(int j = 0; j < (int)scaled_image.height(); j++)
        {
            HSLAPixel & scale_pixel = scaled_image.getPixel(i, j);
            HSLAPixel & pixel = getPixel(i / xfactor, j / yfactor);
            
            scale_pixel.h = pixel.h;
            scale_pixel.s = pixel.s;
            scale_pixel.l = pixel.l;
            scale_pixel.a = pixel.a;

        }
    }

    *this = scaled_image;
}

