/*
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

#include <stdlib.h>
#include <time.h>

using namespace std;

/**
 * returns true if first has a smaller value than second in the relevant dimension
 */
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first, 
								const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim])
    {
        return true;
    }else if (first[curDim] == second[curDim] && first < second)
    {
        return true;
    }

    return false;
}

// Given any 2 n-dimensional points, calculate and return their euclidean distance
template <int Dim>
double get_distance(Point <Dim> point1, Point<Dim> point2)
{
	double result = 0.0;
    for (int i = 0; i < Dim; i++)
    {
        result += pow((point1[i] - point2[i]), 2);
    }

	return sqrt(result);
}

/**
 * returns true if potential should replace target
 */
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    double cur = get_distance(currentBest, target);
    double pot = get_distance(potential, target);

    if (cur == pot)
    {
        return !(currentBest < potential);
    }

	return pot < cur;
}

/**
 * part of the quickselect algorithm, that pivots an array based on a specific value
 */
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, int left, int right, int pivotIndex, int dimension){

  Point<Dim> pivotValue = newPoints[pivotIndex];
  newPoints[pivotIndex] = newPoints[right];
  newPoints[right] = pivotValue;
  int storeIndex = left;

  for (int i = left; i <= right - 1; i++)   
  {
    if (newPoints[i][dimension] < pivotValue[dimension] || (newPoints[i][dimension] == pivotValue[dimension] && newPoints[i] < pivotValue))
	{
      Point<Dim> temp = newPoints[i];
      newPoints[i] = newPoints[storeIndex];
      newPoints[storeIndex] = temp;
      storeIndex++;
    }
  }

  Point<Dim> last = newPoints[right];
  newPoints[right] = newPoints[storeIndex];
  newPoints[storeIndex] = last;

  return storeIndex;
}

/**
 * Part of the quickselect algorithm that selects the kth value in an array
 */
template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& newPoints, int left, int right, int k, int dimension){

      if (left == right)
      {
        return newPoints[left];
      }

      int pivotIndex = (left + right)/2;
      pivotIndex = partition(newPoints, left, right, pivotIndex, dimension);

      if (k == pivotIndex)
      {
        return newPoints[k];
      } else if (k < pivotIndex)
      {
        return select(newPoints, left, pivotIndex - 1, k, dimension);
      } else 
      {
        return select(newPoints, pivotIndex + 1, right, k, dimension);
      }
}


/**
 * Creates a TreeNode* based on a section of an array of specially sorted points
 */
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::tree_creation(vector<Point<Dim>>& newPoints, int left, int right, int dimension){

  if (left > right) 
  {
    return NULL;
  }

  int middle = (left + right)/2;
  Point<Dim> val;

  val = select(newPoints, left, right, middle, dimension);

  // Allocate new root on the heap, and sets its children by making recursive calls that take in subsections of newPoints
  KDTreeNode* subroot = new KDTreeNode(val);
  subroot->left = tree_creation(newPoints, left, middle-1, (dimension + 1) % Dim);
  subroot->right = tree_creation(newPoints, middle+1, right, (dimension + 1) % Dim);

  return subroot;

}

/**
 * construct a kdtree based on a vector of points
 */
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     if (newPoints.empty()){
		 root = NULL;
		 return;
     }

	 vector<Point<Dim>> construction_vals(newPoints);

     //newPoints = sort_list(newPoints, 0, newPoints.size()-1);
     root = tree_creation(construction_vals, 0, construction_vals.size()-1, 0);
}

//template <int Dim>
//KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
//{
//    /**
//     * @todo Implement this function!
//     */
//}

/**
 * Recursive helper function that creates a duplicate of a KDTree passed in by pointer
 */
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(KDTreeNode* other)
{
	if (other == NULL) return NULL;

	KDTreeNode* subNode = new KDTreeNode();

	subNode -> point = other -> point;
	subNode -> left = copy(other -> left);
	subNode -> right = copy(other -> right);
	
	return subNode;
}	

/**
 *copy constructor
 */
template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */

	size = other.size;
	root = copy(other.root);
}

/**
 *copy assignment operator
 */
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
	if (&rhs != this)
	{
		destroy(root);
		root = copy(rhs.root);
		size = rhs.size;
	}

  return *this;
}

/**
 * recursive helper function for destructor
 */
template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode* subroot)
{
	if (subroot == NULL) return;

	destroy(subroot -> left);
	destroy(subroot -> right);
	delete subroot;
	subroot = NULL;
}

/**
 * basic constructor that calls a recursive helper function
 */
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
	destroy(root);
	size = 0;
}

/**
 * given a query point, returns the closest point in the tree to that query point
 */
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return _findNearestNeighbor(query, root, 0);
}


/**
 * recursive helper function for findNearestNeighbor
 */
template <int Dim>
Point<Dim> KDTree<Dim>::_findNearestNeighbor(const Point<Dim>& query, const KDTreeNode* subroot, int splitDim) const
{

    if (subroot -> left == NULL && subroot -> right == NULL)
    {
        return subroot -> point;
    }

    // We first set best to be the nearest node in the relevant plane?
    Point<Dim> best;

    // We store this as a temporary variable in order to tell which plane to check in case we intersect the current closest radius
    bool leftIsCloser = smallerDimVal(query, subroot -> point, splitDim % Dim);    

    if (subroot -> right == NULL || (leftIsCloser && subroot -> left != NULL))
    {
        best = _findNearestNeighbor(query, subroot -> left, splitDim + 1);
    }else // If subroot -> left is null, then we know subroot right must not be null
    {
        // problem here is that if right is closer, we assume right isn't null
        best = _findNearestNeighbor(query, subroot -> right, splitDim + 1);
    }


	// Check if subroot is the closest point
    if (shouldReplace(query, best, subroot -> point))
    { 
        best = subroot -> point;
	}

	// Checking if we need to make the extra recursive call (we only make the extra recursive call if the current node has 2 children)
    
    // We use this point to determine whether we need to make an extra recursive call
    Point<Dim> testPoint;
    for (int i = 0; i < Dim; i++)
    {
        if(i == splitDim)
        {
            testPoint[i] = subroot -> point[i];
        }else
        {
            testPoint[i] = query[i];
        }
    }

    double testDistance = get_distance(testPoint, query);
    double bestDistance = get_distance(best, query);

	if (testDistance <= bestDistance && (subroot -> left != NULL && subroot -> right != NULL))//line is intersecting our current radius
	{
        if (leftIsCloser && subroot -> right != NULL)
        {
            Point<Dim> potential = _findNearestNeighbor(query, subroot -> right, splitDim + 1);
            if (shouldReplace(query, best, potential))
            {
                best = potential;
            }
        }else
        {
            Point<Dim> potential = _findNearestNeighbor(query, subroot -> left, splitDim + 1);
            if (shouldReplace(query, best, potential))
            {
                best = potential;
            }
        }
    }

    // Now we have effectively checked both children and ourself for the closest point

    return best;

}

