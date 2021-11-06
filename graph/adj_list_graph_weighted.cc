/*
adjacency list graph implementation

	Test graph :

	(0) <--(weight 9)--(4)--(weight 0)-->(1)
	^ 									  ^
	|									  |
(weight 8)								(weight 1)
	|									  |
    (5)--(weight 2)-->(2)--(weight 1)--->(3) 


g++ -std=c++14 adj_list_graph_weighted.cc -o adj_list_graph_weighted

*/

#include <iostream>
#include <vector>
using namespace std;

class Graph{
public:
	struct weighted_connection{	
		int linked_node;
		int weight;
		weighted_connection(int ln, int w) : linked_node(ln), weight(w){};
	};

	Graph(int V); // Constructor
	void addEdge(int node, int linked_node, int weight);
	int V;	// number of vertices
	vector<vector<weighted_connection> > adj;  // weighted adjacency list 
};

Graph::Graph(int V)
{
	this->V=V;
	vector<vector<weighted_connection> > adj(V); // init 1D
	this->adj = adj;
	// init 2D -> 6 nodes, each node could link to 6 node
	// vector<vector<weighted_connection> > adj(V, vector<weighted_connection>(V));
}

void Graph::addEdge(int node, int linked_node, int weight){
	weighted_connection wc = weighted_connection(linked_node, weight);
	adj[node].push_back(wc);
}

// i.e. cout << graph; -> necessary since printing struct m_var
std::ostream& operator<<(std::ostream & stream, const Graph& graph){
	for (int j = 0; j < 6; ++j)	{ // j: vertice ID
		std::vector<Graph::weighted_connection>::const_iterator i;	// i: link to other node
		for (i = graph.adj[j].begin(); i != graph.adj[j].end(); ++i){
			stream << "links/points to node " << i->linked_node << " with weight " << i->weight << ' ';
		}
		stream << "      from node " << j << '\n';
	}
	return stream;
}

int main(){
	
    Graph g(6);	
    g.addEdge(5, 2, 2);  // 5th node links to 2nd node
    g.addEdge(5, 0, 8);  // 5th node links to 0th node
    g.addEdge(4, 0, 9);
    g.addEdge(4, 1, 0);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 1, 1);

/*	
	Test graph :

	(0) <--(weight 9)--(4)--(weight 0)-->(1)
	^ 									  ^
	|									  |
(weight 8)								(weight 1)
	|									  |
    (5)--(weight 2)-->(2)--(weight 1)--->(3) 

*/
    cout << g;

    return 0;
}