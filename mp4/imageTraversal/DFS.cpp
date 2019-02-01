#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  startPoint = start;
  image = png;
  s.push_front(startPoint);
  tol = tolerance;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal* traversal = new DFS(image, startPoint, tol);
  return ImageTraversal::Iterator(*traversal);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
    std::list<Point>::iterator it = s.begin();
    while(it != s.end())
    {
        if (*it == point)
        {
            s.erase(it++);
        }else
        {
            ++it;
        }
    }
    s.push_front(point);
    //std::cout << "Pushed " << point << std::endl;
//
//  Point r(point.x + 1, point.y);
//  Point b(point.x, point.y + 1);
//  Point l(0, 0);
//  Point u(0, 0);
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
//  if (point.x < image.width() - 1 && !hasVisited(r))
//  {
//    s.push(r);
//    //std::cout << "pushed " << r << " to the traversal" << std::endl;
//  }
//  if (point.y < image.height() - 1 && !hasVisited(b))
//  {
//    s.push(b);
//    //std::cout << "pushed " << b << " to the traversal" << std::endl;
//  }  
//  if (point.x != 0 && !hasVisited(l)) 
//  {
//    s.push(l);
//    //std::cout << "pushed " << l << " to the traversal" << std::endl;
//  }
//  if (point.y != 0 && !hasVisited(u)) 
//  {
//    s.push(u);
//    //std::cout << "pushed " << u << " to the traversal" << std::endl;
//  }
//
//  Point temp = s.top();
//  while(hasVisited(temp))
//  {
//      s.pop();
//      temp = s.top();
//  }
//
//  if (!hasVisited(point)) s.push(point);

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */

  Point p = s.front();
  s.pop_front();
  //std::cout << "Popped " << p << std::endl;
  return p;

//  Point result; 
//  if (!s.empty())
//  {
//    result = s.top();
//  }
//  while(hasPopped(result))
//  {
//      s.pop();
//      if (s.empty())
//      {
//          result.x = 0;
//          result.y = 0;
//      }else{
//          result = s.top();
//      }
//  }
//  //std::cout << "popped " << s.top().x << ", " << s.top().y << std::endl;
//  s.pop();
//  visited.push_back(result);
//  return result;
}

/**
 * Returns the current Point in the traversal.
 */
// *************************WARNING: THIS FUNCTION WAS MARKED CONST, BUT I CHANGED IT************************************8
Point DFS::peek() {

  return s.front();

  ///** @todo [Part 1] */
  //Point result;

  //if (!s.empty())
  //{
  //    result = s.top();
  //} 
  //// if this runs infinitely, there might be an entry of point() in visited
  //while(hasPopped(result))
  //{
  //    s.pop();
  //    if (s.empty())
  //    {
  //      result.x = 0;
  //      result.y = 0;
  //    }else
  //    {
  //        result = s.top();
  //    }
  //}
  //return result;
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return s.empty();
}

HSLAPixel DFS::getPixel(Point p)
{
    return image.getPixel(p.x, p.y);
}

double DFS::getTolerance()
{
    return tol;
}

Point& DFS::getStartPoint()
{
    return startPoint;
}

bool DFS::hasVisited(Point p)
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

void DFS::visit(Point p)
{
    std::cout << "ERRONEOUSLY CALLED VISIT()" << std::endl;
    visited.push_back(p);
}

PNG& DFS::getImage()
{
    return image;
}
