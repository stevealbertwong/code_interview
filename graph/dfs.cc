/*
author: steven wong

DFS/maze == node connectivity
graph construction + recursion graph traversal + global vector for call stack to “backtrack”
adj list graph is used as the data structure to "backtrack"

g++ -std=c++14 -Wsizeof-array-argument dfs.cc -o dfs
*/

#define SIZE 6

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

class Graph{
public:
	Graph(int V); // Constructor
	void addEdge(int node, int linked_node);	
	bool DFS(int start_node, int dest_node);
	bool DFS_recurse(int start_node, int dest_node, bool visited[]);
	int V;	// number of vertices
	vector<vector<int> > adj;  // weightless adjacency list 
};

Graph::Graph(int V)
{
	this->V=V;
	vector<vector<int> > adj(V); // init 1D
	this->adj = adj;
	// init 2D -> 6 nodes, each node could link to 6 node
	// vector<vector<int> > adj(V, vector<int>(V));
}

void Graph::addEdge(int node, int linked_node){
	adj[node].push_back(linked_node);
}

// if reachable, return found_path <- user interface
bool Graph::DFS(int start_node, int dest_node){
	// init visited to all false
	bool *visited = new bool(SIZE);
	for (int i = 0; i < SIZE; ++i){
			visited[i] = false;}	

	return DFS_recurse(start_node, dest_node, visited);
}

// each recursion, update start node n visited
bool Graph::DFS_recurse(int start_node, int dest_node, bool visited[]){	
	// debug recursive function
	cout << "start node : " << start_node  << " ";
	cout << "visited : " ;
	for (int i = 0; i<SIZE; ++i) {
    	std::cout << visited[i] << " ";}
	cout << endl;


	visited[start_node] = true;

	if(start_node == dest_node){ // found -> yes, node connectivity		
		return true;
	} else {
		std::vector<int>::const_iterator i;	// i: link to other node 
		for (i = adj[start_node].begin(); i != adj[start_node].end(); ++i){
			if(!visited[*i]){ // if visited -> already recursive call stack on that node				
				bool finished = DFS_recurse(*i, dest_node, visited);	
				if(finished){ // hack -> all call stack tree return true
					return true; 
				}
			}			
		}
		return false;
	}				
}

// i.e. cout << graph; -> necessary since printing struct m_var
std::ostream& operator<<(std::ostream & stream, const Graph& graph){
	for (int j = 0; j < SIZE; ++j)	{ // j: vertice ID
		std::vector<int>::const_iterator i;	// i: link to other node
		for (i = graph.adj[j].begin(); i != graph.adj[j].end(); ++i){
			stream << "links/points to node " << *i << ' ';
		}
		stream << "      from node " << j << '\n';
	}
	return stream;
}

int main(){
	
    Graph g(SIZE);	// 6 nodes
    g.addEdge(5, 0);  // 5th node links to 0th node
    g.addEdge(5, 2);  // 5th node links to 2nd node    
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    bool res = g.DFS(5,1);    
    cout << res << endl;    

/*	
	Test graph :

	0 <---4---->1
	^ 			^
	|			|
	|			|
    5---->2---->3 

	5 -> 1 Yes,  
	5 -> 4 No

*/
    cout << g << endl;

    return 0;
}