#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "DirectedEdge.h"

#include "CYOA.h"

#include <string>
#include <iostream>

int main() {
  CYOA cyoa;
  Graph<Vertex, DirectedEdge> g;
  g.insertVertex("a");
  g.insertVertex("b");
  g.insertVertex("c");
  g.insertVertex("d");
  g.insertVertex("e");
  g.insertVertex("f");
  std::cout << g << std::endl;
  g.insertEdge("a", "b");
  g.insertEdge("a", "c");
  g.insertEdge("b", "d");
  g.insertEdge("e", "f");
  std::cout << g << std::endl;

  if (g.size() != 6)
	  std::cout << "failed test on line " << __LINE__ << std::endl;

  if (g.degree(Vertex("a")) != 2)
	  std::cout << "failed test on line " << __LINE__ << std::endl;

  if (g.degree(Vertex("e")) != 1)
	  std::cout << "failed test on line " << __LINE__ << std::endl;


  std::cout << g.size() << std::endl;
  std::cout << g.degree(Vertex("a")) << std::endl;
  std::cout << g.isAdjacent("a", "b") << std::endl;
  std::cout << g.isAdjacent("b", "a") << std::endl;
  g.removeVertex("a");
  std::cout << g << std::endl;
  g.removeEdge("e", "f");
  std::cout << g << std::endl;
  g.removeVertex("e");
  std::cout << g << std::endl;

  // Modify the g.shortestPath call to find the shortest path to your story:
  /*
  std::list<std::string> path = g.shortestPath("waf-zoey", "waf-zoey-oak");
  for (std::string key : path) {
    std::cout << key << " -> ";
  }
  std::cout << "[THE END]" << std::endl;
  */

  return 0;
}
