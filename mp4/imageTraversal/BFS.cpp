#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  startPoint = start;
  image = png;
  q.push_back(startPoint);
  tol = tolerance;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal* traversal = new BFS(image, startPoint, tol);
  return ImageTraversal::Iterator(*traversal);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
    bool should_add = true;

    std::list<Point>::reverse_iterator it = q.rbegin();
    while(it != q.rend())
    {
        if (*it == point)
        {
            //q.erase( --(it.base()));
            should_add = false;
            ++it;
        }else
        {
            ++it;
        }
    }
    if (should_add) q.push_back(point);

//    std::list<Point>::iterator it = q.begin();
//    while(it != q.end())
//    {
//        if (*it == point)
//        {
//            q.erase(it++);
//        }else
//        {
//            ++it;
//        }
//    }
//    q.push_front(point);



    //________________________________________________________________________________________
    //std::cout << "Pushed " << point << std::endl;
//  Point r(point.x + 1, point.y);
//  Point b(point.x, point.y + 1);
//  Point l(0, 0);
//  Point u(0, 0);
//
//  if (point.x != 0)
//  {
//      l.x = point.x - 1; 
//      l.y = point.y;
//  }
//
//  if (point.y != 0)
//  {
//      u.x = point.x;
//      u.y = point.y - 1;
//  }
//
//  if (point.x < image.width() - 1)
//  {
//    q.push(r);
//    //std::cout << "pushed " << r << " to the traversal" << std::endl;
//  }
//  if (point.y < image.height() - 1)
//  {
//    q.push(b);
//    //std::cout << "pushed " << b << " to the traversal" << std::endl;
//  }  
//  if (point.x != 0) 
//  {
//    q.push(l);
//    //std::cout << "pushed " << l << " to the traversal" << std::endl;
//  }
//  if (point.y != 0) 
//  {
//    q.push(u);
//    //std::cout << "pushed " << u << " to the traversal" << std::endl;
//  }
//
//
//  Point temp = q.front();
//  while(hasVisited(temp))
//  {
//      q.pop();
//      temp = q.front();
//  }


//    if (point.x >= 1000)
//    {
//        std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl << std::endl;
//    }
//  Point r(point.x + 1, point.y);
//  Point b(point.x, point.y + 1);
//  Point l(0, 0);
//  Point u(0, 0);
//  if (point.x != 0)
//  { 
//      l.x = point.x - 1;
//      l.y = point.y;
//  }
//  if (point.y != 0) 
//  {
//      u.x = point.x;
//      u.y = point.y - 1;
//  }
//
//  if (r.x < image.width()
//          && calculateDelta(image.getPixel(point.x, point.y), image.getPixel(r.x, r.y)) < tol) 
//  {
//      q.push(r);
//  }
//
//  if (b.y < image.height()
//          && calculateDelta(image.getPixel(point.x, point.y), image.getPixel(b.x, b.y)) < tol)
//  {
//      q.push(b);
//  }
//
//  if (point.x != 0
//          && calculateDelta(image.getPixel(point.x, point.y), image.getPixel(l.x, l.y)) < tol) 
//  {
//      q.push(l);
//  }
//
//  if (point.y != 0
//          && calculateDelta(image.getPixel(point.x, point.y), image.getPixel(u.x, u.y)) < tol)
//  {
//      q.push(u);
//  }

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */

  Point p = q.front();
  //Point p = q.top();
  q.pop_front();
  //std::cout << "Popped " << p << std::endl;
  return p;
//  Point result;
//  if (!q.empty())
//  {
//      result = q.front();
//  }
//
//  while(hasPopped(result))
//  {
//      q.pop();
//      if (q.empty())
//      {
//          result.x = 0;
//          result.y = 0;
//          std::cout << "set to default value at line " << __LINE__ << std::endl;
//      }else
//      {
//          result = q.front();
//      }
//  }
//  q.pop();
//  visited.push_back(result);
//  return result;
}

/**
 * Returns the current Point in the traversal.
 */
//******************* WARNING: THIS FUNCTION WAS MARKED CONST BUT I CHANGED IT *******************************
Point BFS::peek() {
  /** @todo [Part 1] */

    return q.front();
    //return q.top();

//  Point result;
//  if (!q.empty())
//  {
//      result = q.front();
//  }
//  while(hasPopped(result))
//  {
//      q.pop();
//      if (q.empty())
//      {
//        result.x = 0;
//        result.y = 0;
//      }else
//      {
//          result = q.front();
//      }
//  }
//  return result;
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return q.empty();
}

HSLAPixel BFS::getPixel(Point p)
{
    return image.getPixel(p.x, p.y);
}

double BFS::getTolerance()
{
    return tol;
}

Point& BFS::getStartPoint()
{
    return startPoint;
}

bool BFS::hasVisited(Point p)
{
    std::cout << "ERRONEOUSLY CALLED HASVISITED()" << std::endl;
//    bool result = false;
//
//    for (unsigned i = 0; i < visited.size(); i++)
//    {
//        if (visited[i] == p)
//        {
//            result = true;
//        }
//    }
//
//    return result;
return true;
}

void BFS::visit(Point p)
{
    std::cout << "ERRONEOUSLY CALLED VISIT()" << std::endl;
    visited.push_back(p);
}

PNG& BFS::getImage()
{
    return image;
}
