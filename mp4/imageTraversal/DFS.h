/**
 * @file DFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <vector>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);
  
  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek(); //*****WARNING: THIS FUNCTION WAS MARKED CONST, BUT I CHANGED IT***************
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
    std::list<Point> s;
    PNG image;
    Point startPoint;
    double tol;
    std::vector<Point> visited;
};
