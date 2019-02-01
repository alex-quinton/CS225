#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <map>
#include <utility>
#include <iostream>

using std::string;
using std::pair;
using std::queue;



//  given maps of labels,creates a map from every vertex to its predecessor
template <class V, class E>
std::map<string, string> BFS(Graph<V, E> G, std::map<string, string>& vLabels, std::map<pair<string, string>, string>& eLabels, string v)
{
	std::map<string, string> result;

	queue<string> q;
	vLabels.at(v) = "visited";
	q.push(v);
	result[v] = "end";

	/**
	 * REMEMBER THAT EDGES ARE ALWAYS UNDIRECTED
	 */
	while(!q.empty())
	{
		v = q.front();
		q.pop();

		for (auto it : G.incidentEdges(v))
		{
			// vertex that's adjacent to v
			string w;
			bool vSource = false; // tracks whether v is the source of this edge
			if (it.get().source().key() == v)
			{
				w = it.get().dest().key();
				vSource = true;
			}else
			{
				w = it.get().source().key();
			}	
			//std::cout << "v is " << v << ", source is " << it.get().source().key() << ", dest is " << it.get().dest().key() << std::endl;

			if (vLabels.find(w) == vLabels.end()) 
				std::cout << "h1" << std::endl;
			if (vLabels.at(w) == "unexplored")
			{
				if (vSource)
					eLabels.at(pair<string, string>(v, w)) = "discovery";
				if (!vSource)
					eLabels.at(pair<string, string>(w, v)) = "discovery";
				vLabels.at(w) = "visited";
				q.push(w);

				result[w] = v;
			}
			else if ((vSource && eLabels.find(pair<string, string>(v, w)) == eLabels.end()) || (!vSource && eLabels.find(pair<string, string>(w, v)) == eLabels.end())) 
				std::cout << "h2" << std::endl;
			else if(vSource && eLabels.at(pair<string, string>(v, w)) == "unexplored")
			{
				eLabels.at(pair<string, string>(v, w)) = "cross";
			}else if(!vSource && eLabels.at(pair<string, string>(w, v)) == "unexplored")
			{				
				eLabels.at(pair<string, string>(w ,v)) = "cross";
			}
		}
	}

	return result;
}


/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 * 
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 * 
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<string> Graph<V,E>::shortestPath(const string start, const string end) {
  std::list<string> path;
  
	std::map<string, string> vLabels;
	for (auto it : vertexMap)
	{
		vLabels[it.first] = "unexplored";
	}

	std::map<pair<string, string>, string> eLabels;
	for (auto it : edgeList)
	{
		eLabels[pair<string, string>(it.get().source().key(), it.get().dest().key())] = "unexplored";
	}

	std::map<string, string> preds = BFS(*this, vLabels, eLabels, start);
//	for (auto it : vLabels)
//	{
//		if (it.second == "unexplored")
//			BFS(*this, vLabels, eLabels, it.first);
//	}

	string cur = end;
	while(preds.at(cur) != "end")
	{
		path.push_front(cur);
		cur = preds.at(cur);
		if (preds.find(cur) == preds.end())
			std::cout << "h3" << std::endl;
	}
	path.push_front(cur);

  return path;
}

