/* Your code here! */
#pragma once
#include "dsets.h"
#include "cs225/PNG.h"
#include <vector>
using namespace cs225;
using std::vector;

class SquareMaze
{

	public:
		SquareMaze();
		void makeMaze(int width, int height);
		bool canTravel(int x, int y, int dir) const;
		void setWall(int x, int y, int dir, bool exists);
		std::vector<int> solveMaze();
		PNG* drawMaze() const;
		PNG* drawMazeWithSolution();
		PNG* drawCreativeMaze();

	private:
		DisjointSets tree;
        vector<vector<bool>> cells;
		unsigned w;
		unsigned h;
};
