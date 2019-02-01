#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
  //return 0;
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  return adjList.at(v.key()).size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  vertexMap.insert({key, v});
  adjList.insert({key, std::list<edgeListIter>()});
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  vertexMap.erase(key);
  // stores iterators to all the adjacent edges
  std::list<edgeListIter> adj = adjList.at(key);
  while(!adjList.at(key).empty())
  {
	  removeEdge(adjList.at(key).front());
  }
  adjList.erase(key);

}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  edgeList.push_front(e);
  adjList.at(v1.key()).push_back(edgeListIter(edgeList.begin())); // MIGHT BE THE INCORRECT ITERATOR
  //adjList.at(v2.key()).push_back(edgeListIter(edgeList.begin())); // MIGHT BE THE INCORRECT ITERATOR

  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {  
  // TODO: Part 2
  for (edgeListIter it = edgeList.begin(); it != edgeList.end(); ++it)
  {
	  if(it -> get().source().key() == key1 && it -> get().dest().key() == key2)
	  {
		  removeEdge(it);
	  }
  }
  
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
	std::string key1 = it -> get().source().key();
	std::string key2 = it -> get().dest().key();

	for (typename std::list<edgeListIter>::iterator iter = adjList.at(key1).begin(); iter != adjList.at(key1).end(); ++iter)
	{
		if (*iter == it)
			adjList.at(key1).erase(iter);
	}

	if (!it -> get().directed())
	{
		for (typename std::list<edgeListIter>::iterator iter = adjList.at(key2).begin(); iter != adjList.at(key2).end(); ++iter)
		{
			if (*iter == it)
				adjList.at(key2).erase(iter);
		}
	//	for (unsigned i = 0; i < adjList.at(key2).size(); i++)
	//	{
	//		if (adjList.at(key2)[i] == it)
	//			adjList.at(key2).erase(adjList.begin() + i);
	//	}
	}

	edgeList.erase(it);

}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>  
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
	//std::cout << "ran incidentEdges" << std::endl;
  std::list<std::reference_wrapper<E>> edges;

    for (auto it : edgeList)
	{
		if (it.get().source() == key || it.get().dest() == key)
			edges.push_back(it);
	}
//  for (auto it : adjList.at(key))
//  {
//	  edges.push_back(*it);
//  }

  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  
	bool result = false;
	int deg1 = degree(vertexMap.at(key1));
	int deg2 = degree(vertexMap.at(key2));

	//if (deg1 <= deg2)
	{
		for (auto it : adjList.at(key1))
		{
			if (!(*it).get().directed() && ((*it).get().source().key() == key2 || (*it).get().dest().key() == key2))
			{
				result = true;
			}

			if ((*it).get().directed() && (*it).get().dest().key() == key2)
			{
				result = true;
			}
		}
	}

	//if (deg2 < deg1)
	{
		for (auto it : adjList.at(key2))
		{
			if (!(*it).get().directed() && ((*it).get().source().key() == key1 || (*it).get().dest().key() == key1))
			{
				result = true;
			}

			if ((*it).get().directed() && (*it).get().dest().key() == key1)
			{
				//result = true;
			}
		}
	}

  return result;
}
