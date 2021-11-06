/*
CtCI 4.1 route between nodes

adjacency list graph implementation

	Test graph :

	0 <---4---->1
	^ 			^
	|			|
	|			|
    5---->2---->3 


g++ -std=c++14 adj_list_graph_weightless.cc -o adj_list_graph_weightless

*/

#include <iostream>
#include <vector>
using namespace std;

class Graph{
public:
	Graph(int V); // Constructor
	void addEdge(int node, int linked_node);	
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

// i.e. cout << graph; -> necessary since printing struct m_var
std::ostream& operator<<(std::ostream & stream, const Graph& graph){
	for (int j = 0; j < 6; ++j)	{ // j: vertice ID
		std::vector<int>::const_iterator i;	// i: link to other node
		for (i = graph.adj[j].begin(); i != graph.adj[j].end(); ++i){
			stream << "links/points to node " << *i << ' ';
		}
		stream << "      from node " << j << '\n';
	}
	return stream;
}

int main(){
	
    Graph g(6);	
    g.addEdge(5, 2);  // 5th node links to 2nd node
    g.addEdge(5, 0);  // 5th node links to 0th node
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

/*	
	Test graph :

	0 <---4---->1
	^ 			^
	|			|
	|			|
    5---->2---->3 

*/
    cout << g;

    return 0;
}