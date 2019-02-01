/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <vector>
#include <queue>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();
  
  void add(const Point & point);
  Point pop();
  Point peek(); //******************* WARNING: THIS FUNCTION WAS MARKED CONST BUT I CHANGED IT *******************************
  bool empty() const;

  HSLAPixel getPixel(Point p);
  double getTolerance();
  Point& getStartPoint();
  bool hasVisited(Point p);
  void visit(Point p);
  PNG& getImage();

private:
    /** @todo [Part 1] */
    /** add private members here*/
    std::list<Point> q;
    PNG image;
    double tol;
    Point startPoint;
    std::vector<Point> visited;
};
