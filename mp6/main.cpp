#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    SquareMaze h;
    h.makeMaze(50, 50);
    h.drawCreativeMaze() -> writeToFile("creative.png");
    return 0;
}
