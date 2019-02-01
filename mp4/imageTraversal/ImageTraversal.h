/**
 * @file ImageTraversal.h
 */
#pragma once

#include <iterator>
#include <vector>
#include <map>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

using namespace cs225;

/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 * 
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  class Iterator : std::iterator<std::forward_iterator_tag, Point> {
  public:
    Iterator();
    Iterator(ImageTraversal& t);

    Iterator & operator++();
    Point operator*();
    bool operator!=(const Iterator &other);

    private:
    /** @todo [Part 1] */
    /** add member functions if neccesary*/
        ImageTraversal* traversal;
        Point current;
        PNG* image;
        Point startPoint;
        std::map<std::pair<int, int>, bool> visited;
        bool hasVisited(Point p);

  };  
  virtual HSLAPixel getPixel(Point p) = 0;
  virtual double getTolerance() = 0;
  virtual Point& getStartPoint() = 0;
  virtual void visit(Point p) = 0;
  virtual PNG& getImage() = 0;

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new point to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const Point & t) = 0;
  /**
   * Remove and return the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point pop() = 0;
  /**
   * Return but not remove the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  // *********************WARNING: THIS FUNCTION WAS MARKED CONST BUT I CHANGED IT **********************************
  virtual Point peek() = 0;
  /**
   * To see if the traversal has no points left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() const = 0;

  //static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);  
private:
  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);  
  PNG image;
  Point startPoint;
};
