#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>
#include <cstdlib>
#include <iostream>
#include <cmath>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG* input = new PNG();
  input->readFromFile(inputFile);

    unsigned width = input->width();
    unsigned height = input->height();

	PNG* output = new PNG(width, height);

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            output->getPixel(x, y) = input->getPixel((width - 1) - x, (height - 1) - y);
        }
    }

	output->writeToFile(outputFile);
 	delete input;
    delete output;	
}

const int kRandAdd = 20;

void diamond(PNG & image, int x1, int x2, int y1, int y2)
{
	int x3 = fmin(x1, x2) + abs(x1 - x2)/2;
	int y3 = fmin(y1, y2) + abs(y2 - y1)/2;


	if(image.getPixel(x3, y3).a != 0)
	{
		return;
	}

	image.getPixel(x3, y3).h = (image.getPixel(x1, y1).h + image.getPixel(x1, y2).h + image.getPixel(x2, y1).h + image.getPixel(x2, y2).h)/4 + std::rand() % kRandAdd + 10;
	
	//std::cout << "Reached line " << __LINE__ << std::endl;
	// Square step
	image.getPixel(x3, y1).h = (image.getPixel(x3, y3).h + image.getPixel(x1, y1).h + image.getPixel(x2, y1).h)/3 + std::rand() % kRandAdd + kRandAdd/2;
	image.getPixel(x1, y3).h = (image.getPixel(x3, y3).h + image.getPixel(x1, y1).h + image.getPixel(x1, y2).h)/3 + std::rand() % kRandAdd + kRandAdd/2;
	image.getPixel(x2, y3).h = (image.getPixel(x3, y3).h + image.getPixel(x2, y1).h + image.getPixel(x2, y2).h)/3 + std::rand() % kRandAdd + kRandAdd/2;
	image.getPixel(x3, y2).h = (image.getPixel(x3, y3).h + image.getPixel(x1, y2).h + image.getPixel(x2, y2).h)/3 + std::rand() % kRandAdd + kRandAdd/2;
	
	//std::cout << image.getPixel(x3, y1).h << std::endl;

	// Set alphas to 1 so we know we've edited these pixels
	image.getPixel(x3, y3).a = 1;
	image.getPixel(x3, y1).a = 1;
	image.getPixel(x1, y3).a = 1;
	image.getPixel(x2, y3).a = 1;
	image.getPixel(x3, y2).a = 1;

	// Wrap all values above 360 around back to 0
	
	if (image.getPixel(x3, y3).h >= 360) image.getPixel(x3, y3).h -= 360;	
	if (image.getPixel(x3, y1).h >= 360) image.getPixel(x3, y1).h -= 360;	
	if (image.getPixel(x1, y3).h >= 360) image.getPixel(x1, y3).h -= 360;	
	if (image.getPixel(x2, y3).h >= 360) image.getPixel(x2, y3).h -= 360;	
	if (image.getPixel(x3, y2).h >= 360) image.getPixel(x3, y2).h -= 360;	

	// Recursive step
	diamond(image, x1, x3, y1, y3);
	diamond(image, x3, x2, y1, y3);
	diamond(image, x1, x3, y3, y2);
	diamond(image, x3, x2, y3, y2); 
}

PNG myArt(unsigned width, unsigned int height) {
  PNG png(width, height);	
  srand(time(NULL));

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            png.getPixel(x, y).a = 0;
            png.getPixel(x, y).l = 0.5;
            png.getPixel(x, y).s = 1;
        }
    }

  // TODO: Part 3
  if (width % 2 == 0) width --;
  if (height % 2 == 0) height --;
	
  // Randomize the pixel hues at each corner
  // This block makes it look more square-ish
  //png.getPixel(0, 0).h = std::rand() % 90;
  //png.getPixel(width, 0).h = std::rand() % 90 + 90;
  //png.getPixel(0, height).h = std::rand() % 90 + 180;
  //png.getPixel(width, height).h = std::rand() % 90 + 270;

  // This block makes it look much smoother
  png.getPixel(0, 0).h = std::rand() % 359;
  png.getPixel(width, 0).h = std::rand() % 359;
  png.getPixel(0, height).h = std::rand() % 359;
  png.getPixel(width, height).h = std::rand() % 359;

  png.getPixel(0, 0).a = 1;
  png.getPixel(width, 0).a = 1;
  png.getPixel(0, height).a = 1;
  png.getPixel(width, height).a = 1;

  diamond(png, 0, (int) (width), 0, (int) (height));

  return png;
}
