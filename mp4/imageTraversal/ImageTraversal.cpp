#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal = NULL;
  current = Point();
  image = NULL;
  startPoint = Point();
}

ImageTraversal::Iterator::Iterator(ImageTraversal& t) 
{
  /** @todo [Part 1] */
  traversal = &t;
  current = traversal -> peek();
  image = &(traversal -> getImage());
  startPoint = traversal -> getStartPoint();
  for (unsigned i = 0; i < image -> width(); i++)
  {
      for (unsigned j = 0; j < image -> height(); j++)
      {
            visited[std::pair<int, int>(i, j)] = false;
      }
  }

  //traversal -> add(startPoint);
  //visited.at(std::pair<int, int>(startPoint.x, startPoint.y)) = true; 
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
    if (traversal == NULL)
    {
        return *this;
    }

    if (!traversal -> empty()) 
    {
        current = traversal->pop();

        Point r(current.x + 1, current.y);
        Point b(current.x, current.y + 1);
        Point l(0, current.y);
        Point u(current.x, 0);

        if (current.x != 0)
        {
            l.x = current.x - 1;
        }

        if (current.y != 0)
        {
            u.y = current.y - 1;
        }

        //std::pair<int, int> cur_pair(current.x, current.y);
        //visited.at(cur_pair) = true; 

        if (r.x < image -> width()
                && calculateDelta(traversal -> getPixel(r), traversal -> getPixel(startPoint)) < traversal -> getTolerance()
                && !hasVisited(r))            
        {
          traversal -> add(r);
 //           visited.at(std::pair<int, int>(r.x, r.y)) = true; 
        }else
        {
        //    if (r.x >= image.width()) std::cout << "out of bounds for " << r << ", width is " << image.width() << " height is " << image.height() << std::endl;
        //    if (!(calculateDelta(traversal -> getPixel(r), traversal -> getPixel(startPoint)) < traversal -> getTolerance())) std::cout << "delta too high to visit " << r << std::endl;
        //    if (hasVisited(r)) std::cout << "already visited " << r << std::endl;
        }

        if (b.y < image -> height()
                && calculateDelta(traversal -> getPixel(b), traversal -> getPixel(startPoint)) < traversal -> getTolerance()
                && !hasVisited(b))            
        {
          traversal -> add(b);
  //          visited.at(std::pair<int, int>(b.x, b.y)) = true; 
          //visited.push_back(b);
        } else
        {
        //    if (b.y >= image.height()) std::cout << "out of bounds for " << b << ", width is " << image.width() << " height is " << image.height() << std::endl;
        //    if (!(calculateDelta(traversal -> getPixel(b), traversal -> getPixel(startPoint)) < traversal -> getTolerance())) std::cout << "delta too highi to visit" << b << std::endl;
        //    if (hasVisited(r)) std::cout << "already visited " << b << std::endl;
        } 

        if (current.x != 0
                && calculateDelta(traversal -> getPixel(l), traversal -> getPixel(startPoint)) < traversal -> getTolerance()
                && !hasVisited(l))            
        {
          traversal -> add(l);
  //          visited.at(std::pair<int, int>(l.x, l.y)) = true; 
          //visited.push_back(l);
        }else
        {
        //    if (current.x == 0) std::cout << "out of bounds for " << l << ", width is " << image.width() << " height is " << image.height() << std::endl;
        //    if (!(calculateDelta(traversal -> getPixel(l), traversal -> getPixel(startPoint)) < traversal -> getTolerance())) std::cout << "delta too high to visit " << l << std::endl;
        //    if (hasVisited(l)) std::cout << "already visited " << l << std::endl;
        }

        if (current.y != 0
                && calculateDelta(traversal -> getPixel(u), traversal -> getPixel(startPoint)) < traversal -> getTolerance()
                && !hasVisited(u))
        {
          traversal -> add(u);
  //          visited.at(std::pair<int, int>(u.x, u.y)) = true; 
          //visited.push_back(u);
        }else
        {
        //    if (u.y == 0) std::cout << "out of bounds for " << u << ", width is " << image.width() << " height is " << image.height() << std::endl;
        //    if (!(calculateDelta(traversal -> getPixel(u), traversal -> getPixel(startPoint)) < traversal -> getTolerance())) std::cout << "delta too high to visit " << u << std::endl;
        //    if (hasVisited(r)) std::cout << "already visited " << u << std::endl;
        }


        //std::map<std::pair<int, int>, bool>::iterator cur = visited.find(cur_pair);
        //cur -> second = true;
        visited.at(std::pair<int, int>(current.x, current.y)) = true;
        
        
        //if (cur != visited.end()) cur -> second = true;
        //traversal -> visit(current);

        if (!traversal -> empty())
        {
            current = traversal -> peek();
        }else
        {
            traversal = NULL;
        }
    }

    //flush out duplicates on the top
    if (traversal != NULL && !traversal -> empty())
    {
        Point temp = traversal -> peek();
    //    while(hasVisited(temp) && !traversal -> empty())
        {
            //temp = traversal -> pop();
        }
    }

    if (traversal != NULL && traversal -> empty())
    {
        traversal = NULL;
    }

    return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  //while(hasVisited(current) && !traversal -> empty())
  {
      //current = traversal -> pop();
  }

  if (traversal -> empty())
  {
      //traversal -> add(current);
  }

  return current;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
    bool this_empty = false;
    bool other_empty = false;

    if (traversal == NULL) { this_empty = true; }
    if (other.traversal == NULL) { other_empty = true; }

    if (!this_empty)  { this_empty = traversal->empty(); }
    if (!other_empty) { other_empty = other.traversal->empty(); }

    if (this_empty && other_empty) return false; // both empty then the traversals are equal, return true
    else if ((!this_empty)&&(!other_empty)) return (traversal != other.traversal); //both not empty then compare the traversals
    else return true; // one is empty while the other is not, return true
}

bool ImageTraversal::Iterator::hasVisited(Point p)
{
    if (visited.find(std::pair<int, int>(p.x, p.y)) == visited.end())
    {
        std::cout << "using default value of hasVisited(), something has gone wrong" << std::endl;
    }
    return visited.at(std::pair<int, int>(p.x, p.y));
}
