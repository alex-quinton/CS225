/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
    for (unsigned i = 0; i < startingGraph.getEdges().size(); i++)
    {
        flow_.insertEdge(startingGraph.getEdges()[i].source, startingGraph.getEdges()[i].dest);
        flow_.setEdgeWeight(startingGraph.getEdges()[i].source, startingGraph.getEdges()[i].dest, 0);
    }

    for (unsigned i = 0; i < startingGraph.getEdges().size(); i++)
    {
        residual_.insertEdge(startingGraph.getEdges()[i].source, startingGraph.getEdges()[i].dest);
        residual_.insertEdge(startingGraph.getEdges()[i].dest, startingGraph.getEdges()[i].source);
        residual_.setEdgeWeight(startingGraph.getEdges()[i].source, startingGraph.getEdges()[i].dest, startingGraph.getEdgeWeight(startingGraph.getEdges()[i].source, startingGraph.getEdges()[i].dest));
        residual_.setEdgeWeight(startingGraph.getEdges()[i].dest, startingGraph.getEdges()[i].source, 0);
    }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   * @@params: visited -- A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @@params: path   -- The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int min = 9999999;
  for (unsigned i = 0; i < path.size() - 1; i++)
  { 
      if (residual_.getEdgeWeight(path[i], path[i + 1]) <= min)
      {
          min = residual_.getEdgeWeight(path[i], path[i + 1]);
      }
  }
  return min;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @@outputs: The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  std::vector<Vertex> path;
  while(findAugmentingPath(source_, sink_, path))
  {
    int cap = pathCapacity(path);
    
    for (unsigned i = 0; i < path.size() - 1; i++)
    {
        // test to see if this edge exists. if not, then this edge goes in the opposite direction, so we subtract cap instead of add
        if (flow_.edgeExists(path[i], path[i + 1]))
        {
            flow_.setEdgeWeight(path[i], path[i + 1], flow_.getEdgeWeight(path[i], path[i + 1]) + cap);
        }else if (flow_.edgeExists(path[i + 1], path[i]))
        {
            flow_.setEdgeWeight(path[i + 1], path[i], flow_.getEdgeWeight(path[i + 1], path[i]) - cap); // NON EXISTENT EDGE HERE
        }

        residual_.setEdgeWeight(path[i], path[i + 1], residual_.getEdgeWeight(path[i], path[i + 1]) - cap);
        residual_.setEdgeWeight(path[i + 1], path[i], residual_.getEdgeWeight(path[i + 1], path[i]) + cap);
    }
  }
  int max = 0;
  for (unsigned i = 0; i < flow_.getAdjacent(source_).size(); i++)
  {
      max += flow_.getEdgeWeight(source_, flow_.getAdjacent(source_)[i]);
  }
  maxFlow_ = max;
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

