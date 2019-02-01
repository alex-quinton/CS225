#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

    Image base;
    Image s1;
    Image s2;
    Image s3;
    
    base.readFromFile("cats.png");
    s1.readFromFile("cat1.png");
    s2.readFromFile("cat2.png");
    s3.readFromFile("cat3.png");

    std::cout << "reached line " << __LINE__ << std::endl;

    StickerSheet stickers(base, 5);
    stickers.addSticker(s1, 0, 0);
    stickers.addSticker(s2, 100, 100);
    stickers.addSticker(s3, 200, 200);

    std::cout << "reached line " << __LINE__ << std::endl;

    // Segfaults here
    Image result = stickers.render();
    
    std::cout << "reached line " << __LINE__ << std::endl;

    result.writeToFile("myImage.png");

  return 0;
}
