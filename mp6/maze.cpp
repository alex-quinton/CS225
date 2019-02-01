/* Your code here! */
#include "maze.h"
#include <time.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <chrono>
#include <cmath>

using std::queue;
using std::pair;

bool hasInitialized = false;

/**
 * basic constructor, initializes srand
 */
SquareMaze::SquareMaze()
{
	h = 0;
	w = 0;
    if (!hasInitialized)
    {
        srand(time(NULL));
        hasInitialized = true;
    }
}

/**
 * FOR DIRECTIONS:
 * 0 = right
 * 1 = down
 * 2 = left
 * 3 = up
 */

/**
 * creates a random maze using disjoint sets to check for cycles
 */
void SquareMaze::makeMaze(int width, int height)
{
	w = width;
	h = height;

	tree.addelements(width * height);

    // Fill the cells vector with vectors of size 4
    // Each element in the inner vector represents whether you can travel in the direction represented by that index
    // i.e. if index 1 is 0, you can travel down, if index 2 is 0 you cant travel left
    for (int i = 0; i < (width * height); i++)
    {
        cells.push_back({false, false, false, false});
    }

    // Create and shuffle a vector of edges so that we can remove them randomly without checking the same edge twice
    vector<pair<int, int>> edges;
    for (unsigned i = 0; i < tree.set.size(); i++)
    {
        edges.push_back(pair<int, int>(i, 0));
        edges.push_back(pair<int, int>(i, 1));
    }

    std::random_shuffle(edges.begin(), edges.end());

	// continuously remove walls until all elements are in the same disjoint set
    for (unsigned i = 0; i < edges.size(); i++)
	{

		// since the edges vector is shuffled, we can effectively choose a random wall by selecting the next element in the vector
		int randIdx = edges[i].first;
		unsigned randDir = edges[i].second;

		int rightCell = randIdx + 1;
		int downCell = randIdx + w;
		int leftCell = randIdx - 1;
		int upCell = randIdx - w;

		if ((randDir == 0 && ((randIdx + 1) % w == 0 || rightCell >= (int)tree.set.size()))
				|| (randDir == 1 && downCell >= (int)tree.set.size())
				|| (randDir == 2 && ((leftCell + 1) % w == 0 || (leftCell) < 0))
				|| (randDir == 3 && upCell < 0))
		{
			randDir = (randDir + 2) % 4;
		}

		//check whether cells on either side of the wall are in different disjoint sets. If so, union and remove wall.
		if (randDir == 0 && tree.find(randIdx) != tree.find(rightCell))
		{
			tree.setunion(randIdx, rightCell);
            cells[randIdx][randDir] = true;
            cells[rightCell][(randDir + 2) % 4] = true;
		}

		if (randDir == 1 && tree.find(randIdx) != tree.find(downCell))
		{
			tree.setunion(randIdx, downCell);
            cells[randIdx][randDir] = true;
            cells[downCell][(randDir + 2) % 4] = true;
		}

		if (randDir == 2 && tree.find(randIdx) != tree.find(leftCell))
		{
			tree.setunion(randIdx, leftCell);
            cells[randIdx][randDir] = true;
            cells[leftCell][(randDir + 2) % 4] = true;
		}

		if ( randDir == 3 && tree.find(randIdx) != tree.find(upCell))
		{
			tree.setunion(randIdx, upCell);
            cells[randIdx][randDir] = true;
            cells[upCell][(randDir + 2) % 4] = true;
		}
	}
}

/**
 * returns true if you can travel in the given direction from the given cell
 */
bool SquareMaze::canTravel(int x, int y, int dir) const
{
    return cells[x + y * w][dir];
}

/**
 * sets whether the given wall exists
 */
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
    exists = !exists;
    int idx = x + y * w;
    int rightCell = idx + 1;
    int downCell = idx + w;
    int leftCell = idx - 1;
    int upCell = idx - w;

    //boundary check
    if (!(((unsigned)x == 0 && dir == 2)
                || (((unsigned)x == w - 1) && dir == 0)
                || (((unsigned)y == 0)  && dir == 3)
                || (((unsigned)y == h - 1) &&  dir == 1)))
            {
              cells[idx][dir] = exists;

              if (dir == 0)
              {
                  cells[rightCell][2] = exists;
              }

              if (dir == 1)
              {
                  cells[downCell][3] = exists;
              }

              if (dir == 2)
              {
                  cells[leftCell][0] = exists;
              }

              if (dir == 3)
              {
                  cells[upCell][1] = exists;
              }
            }

}

/**
 * generates a vector of directions from the origin that leads to the end of the generated maze
 */
std::vector<int> SquareMaze::solveMaze()
{
    // For each cell in the grid, this will store the direction that was taken to reach that cell
    vector<int> cell_markings;
    for (unsigned i = 0; i < tree.set.size();  i++)
    {
        cell_markings.push_back(-1);
    }

    int min_sol_x = 0;
    unsigned max_sol_length = 0;
    vector<int> result;

    queue<pair<int, int>> path;
    path.push(pair<int, int>(0, 0));

    while(!path.empty())
    {
        pair<int, int> cur = path.front();
        path.pop();
        
        if (cur.second + 1 == (int)h)
        {
            // backtrack the path taken to get here and set that path to the result if it's the longest
            int cur_cell = cur.first + cur.second * w;
            vector<int> sol;
            int sol_x = cur.first;

            while(cur_cell != 0)
            {    
                int dir = cell_markings[cur_cell]; // dir is the direction we took to get to this cell
                sol.push_back(dir); // add the direction we took to get to cur_cell to the solution vector

                if (dir == -1)  std::cout <<  "problem" << std::endl;
                if (dir == 0)  cur_cell = cur_cell - 1;
                if (dir == 1) cur_cell = cur_cell - w;
                if (dir == 2)  cur_cell = cur_cell + 1;
                if (dir == 3) cur_cell = cur_cell + w;
            }

            std::reverse(sol.begin(), sol.end());
            if (sol.size() > max_sol_length || (sol.size() == max_sol_length && sol_x <= min_sol_x))
            {
                max_sol_length = sol.size();
                min_sol_x = sol_x;
                result = sol;
            }

        }//else // If we aren't at the bottom row
        {
            if (canTravel(cur.first, cur.second, 0) && cell_markings[cur.first + 1 + cur.second * w] < 0) 
            {
                path.push(pair<int, int>(cur.first + 1, cur.second));
                cell_markings[cur.first + 1 + w * cur.second] = 0;
            }

            if (canTravel(cur.first, cur.second, 1) && cell_markings[cur.first + w * (cur.second + 1)] < 0) 
            {
                path.push(pair<int, int>(cur.first, cur.second + 1));
                cell_markings[cur.first + w * (cur.second + 1)] = 1;
            }

            if (canTravel(cur.first, cur.second, 2) && cell_markings[cur.first - 1 + w * cur.second] < 0) 
            {
                path.push(pair<int, int>(cur.first- 1, cur.second));
                cell_markings[cur.first - 1 + w * cur.second] = 2;
            }

            if (canTravel(cur.first, cur.second, 3) && cell_markings[cur.first + w * (cur.second - 1)] < 0) 
            {
                path.push(pair<int, int>(cur.first, cur.second - 1));
                cell_markings[cur.first + w * (cur.second- 1)] = 3;
            }
        }
    }

    return result;
}

/**
 * draws the currently generated maze
 */
PNG* SquareMaze::drawMaze() const
{
    PNG* maze = new PNG(w * 10 + 1, h * 10 + 1);

    for (unsigned i = 0; i < maze->width(); i++)
    {
        if (i < 1 || i > 9) maze->getPixel(i, 0).l = 0;
    }

    for (unsigned i = 0; i < maze->height(); i++)
    {
        maze->getPixel(0, i).l = 0;
    }

    for (unsigned x = 0; x < w; x++)
    {
        for (unsigned y = 0; y < h; y++)
        {
            // If right wall exists
            if (!cells[x + y * w][0])
            {
                for (unsigned k = 0; k <= 10; k++)
                {
                    maze->getPixel(((x+1) * 10), (y * 10 + k)).l = 0;
                }
            }

            // If bottom wall exists
            if (!cells[x + y * w][1])
            {
                for (unsigned k = 0; k <= 10; k++)
                {
                    maze->getPixel((x * 10 + k), ((y+1)*10)).l = 0;
                }
            }
        }
    }

    return maze;
}

/**
 * draws the currently generated maze with a red line showing the solution
 */
PNG* SquareMaze::drawMazeWithSolution()
{
  PNG* maze_with_solution = drawMaze();
  std::vector<int> solution = solveMaze();

  int x = 5;
  int y = 5;
  //put red pixel at 5,5
  maze_with_solution->getPixel(x, y).s = 1;
  maze_with_solution->getPixel(x, y).l = 0.5;
  for (unsigned i = 0; i < solution.size(); i++)
  {
    int dir = solution[i];

    for(int j = 0 ; j < 10 ;j++) {
      if (dir == 0)
      {
        x++;
      } else if(dir == 1)
      {
        y++;
      } else if(dir == 2)
      {
        x--;
      } else if(dir == 3)
      {
        y--;
      }

      maze_with_solution->getPixel(x, y).s = 1;
      maze_with_solution->getPixel(x, y).l = 0.5;
    }

    if (i == solution.size() - 1){

      y = maze_with_solution -> height() - 1;
      x -= 4;
      for (unsigned k = 0; k < 9; k++)
      {
          maze_with_solution->getPixel(x, y).l = 1;
          x++;
      }
    }
  }
  return maze_with_solution;
}

/**
 * draws a maze and cuts a circle out of it
 */
PNG* SquareMaze::drawCreativeMaze()
{
  PNG* maze_with_solution = drawMaze();
  std::vector<int> solution = solveMaze();

  int x = 5;
  int y = 5;
  //put red pixel at 5,5
  maze_with_solution->getPixel(x, y).s = 1;
  maze_with_solution->getPixel(x, y).l = 0.5;
  for (unsigned i = 0; i < solution.size(); i++)
  {
    int dir = solution[i];

    for(int j = 0 ; j < 10 ;j++) {
      if (dir == 0)
      {
        x++;
      } else if(dir == 1)
      {
        y++;
      } else if(dir == 2)
      {
        x--;
      } else if(dir == 3)
      {
        y--;
      }

      maze_with_solution->getPixel(x, y).s = 1;
      maze_with_solution->getPixel(x, y).l = 0.5;
    }

    if (i == solution.size() - 1){

      y = maze_with_solution -> height() - 1;
      x -= 4;
      for (unsigned k = 0; k < 9; k++)
      {
          maze_with_solution->getPixel(x, y).l = 1;
          x++;
      }
    }
  }

for (int x = 0; x < (int)maze_with_solution -> width(); x++)
{
    for (int y = 0; y < (int)maze_with_solution -> height(); y++)
    {
        if (std::sqrt(std::pow((x - (int)maze_with_solution -> width() / 2), 2) + std::pow((y - (int)maze_with_solution -> height() / 2), 2)) > 200) maze_with_solution -> getPixel(x, y).l = 1;
    }
}

  return maze_with_solution;
}
