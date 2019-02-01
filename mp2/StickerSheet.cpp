#include "StickerSheet.h"
#include <iostream>

StickerSheet::StickerSheet(const Image & picture, unsigned max)
{
    base_image = picture;
    stickers = new Image*[max];
    arr_size = max;

    for (unsigned i = 0; i < max; i++)
    {
        stickers[i] = nullptr;
    }
}

StickerSheet::~StickerSheet()
{
    for (unsigned i = 0; i < arr_size; i++)
    {
        if (stickers[i] != nullptr)
        {
            delete stickers[i];
            stickers[i] = nullptr;
        }
    }

    delete[] stickers;

    stickers = nullptr;
}

StickerSheet::StickerSheet(const StickerSheet & other)
{
    base_image = other.base_image;
    arr_size = other.arr_size;
    stickers = new Image*[other.arr_size];
    coordinates = other.coordinates;

    for (unsigned i = 0; i < other.arr_size; i++)
    {
        if (other.stickers[i] != nullptr)
        {
            stickers[i] = new Image(*(other.stickers[i]));
        } else
        {
            stickers[i] = nullptr;
        }
    }
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other)
{
    for (unsigned i = 0; i < arr_size; i++)
    {
        delete stickers[i];
    }

    delete[] stickers;

    base_image = other.base_image;
    arr_size = other.arr_size;
    stickers = new Image*[arr_size];
    coordinates = other.coordinates;

    for (unsigned i = 0; i < arr_size; i++)
    {
        if (other.stickers[i] != nullptr)
        {
            stickers[i] = new Image(*(other.stickers[i]));
        } else
        {
            stickers[i] = nullptr;
        }
    }


    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max)
{
    Image **temp = new Image*[max];

    for (unsigned i = 0; i < max; i++)
    {
        if (i < arr_size && stickers[i] != nullptr)
        {
            temp[i] = new Image(*(stickers[i]));
        } 
        else
        {
            temp[i] = nullptr;
        }
    } 
    
    for (unsigned i = 0; i < arr_size; i++)
    {
        delete stickers[i];
    }

    delete[] stickers;

    stickers = temp;
    arr_size = max;
    
    // Delete extraneous coordinate entries
    while (coordinates.size() > max)
    {
        coordinates.pop_back();
    }
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y)
{
    pair <int, int> new_coords(x, y);
    
    for (unsigned i = 0; i < arr_size; i++)
    {
        if (stickers[i] == nullptr)
        {
            stickers[i] = new Image(sticker);
            coordinates.push_back(new_coords);
            return i;
        }
    }

    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
{
    if (index > arr_size || stickers[index] == nullptr)
    {
        return false;
    }

    coordinates[index].first = x;
    coordinates[index].second = y;
    
    return true;
}

bool StickerSheet::removeSticker(unsigned index)
{
    if (index >= arr_size)
    {
        return false;
    }

    Image **temp = new Image*[arr_size];

    for (unsigned i = 0; i < arr_size; i++)
    {
        if (i < index)
        {
            if (stickers[i] != nullptr)
            {
                temp[i] = new Image(*(stickers[i]));
            }
            else
            {
                temp[i] = nullptr;
            }
        }

        if (i > index)
        {
            if (stickers[i] != nullptr)
            {
                temp[i - 1] = new Image(*(stickers[i]));
            }
            else
            {
                temp[i - 1] = nullptr;
            }
        }
    }

    temp[arr_size - 1] = nullptr;
    
    for (unsigned i = 0; i < arr_size; i++)
    {
        if (stickers[i] != nullptr)
        {
            delete stickers[i];
        }
    }

    delete[] stickers;

    stickers = temp;
    coordinates.erase(coordinates.begin() + (index));

    return true;
}

Image* StickerSheet::getSticker(unsigned index) const
{
    if (index >= (unsigned)arr_size)
    {
        return nullptr;
    }

    return stickers[index];
}

Image StickerSheet::render() const
{
    Image result(base_image);

    // iterate over each pixel in each element of the stickers array
    // we use size of coordinates array to judge how many stickers there are
    for(unsigned i = 0; i < coordinates.size(); i++)
    {
        Image &sticker = *(stickers[i]);

        for (unsigned x = 0; x < sticker.width(); x++)
        {
            for (unsigned y = 0; y < sticker.height(); y++)
            {
                if (x + coordinates[i].first < result.width()
                        && y + coordinates[i].second < result.height()
                        && sticker.getPixel(x, y).a > 0)
                {
                    result.getPixel(x + coordinates[i].first, y + coordinates[i].second) = sticker.getPixel(x, y);
                }
            }
        }
    }

    return result;
}
