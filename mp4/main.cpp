
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

//  PNG png;
//  png.readFromFile("eggg.png");
//  FloodFilledImage image(png);
//  DFS dfs(png, Point(1, 1), 0.05);
//  RainbowColorPicker rainbow(0.05);
//
//  image.addFloodFill(dfs, rainbow);
//  Animation animation = image.animate(4); 
  

    //MAKE SURE TO MEET THE REQUIREMENTS FOR PART 3, I.E. SEVERAL FLOODFILL OPERATIONS
  PNG png;       
  png.readFromFile("tests/i.png");

  FloodFilledImage image(png);
  DFS traversal(png, Point(40, 40), 0.76);
  MyColorPicker color_picker1;
  RainbowColorPicker rainbow(0.1);

  BFS eye1(png, Point(138, 115), 1);
  BFS eye2(png, Point(185, 105), 1);
  image.addFloodFill( traversal, color_picker1 );
  image.addFloodFill(eye1, rainbow);
  image.addFloodFill(eye2, rainbow);

  Animation animation = image.animate(1000);
  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  


  return 0;
}
