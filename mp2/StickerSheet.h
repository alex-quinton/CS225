/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

//Using vectors for the coordinates array because they're actually useful, unlike default arrays...
#include "Image.h"
#include <vector>
#include <utility>
using std::vector;
using std::pair;

class StickerSheet
{
    public:
        StickerSheet(const Image & picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet & other);
        const StickerSheet & operator=(const StickerSheet & other);
        
        void changeMaxStickers(unsigned max);
        int addSticker(Image & sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        bool removeSticker(unsigned index);
        Image* getSticker(unsigned index) const;
        Image render() const;

    private:
        Image base_image;
        Image **stickers;
        unsigned arr_size;
        vector<pair<int, int>> coordinates;
};
