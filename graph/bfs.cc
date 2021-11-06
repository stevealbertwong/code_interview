/*
author: steven wong

BFS == shortest path
graph construction + for loop graph traversal + queue to store order of adj nodes to BFS

g++ -std=c++14 -Wsizeof-array-argument bfs.cc -o bfs
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph{
public:
	Graph(int V); // Constructor
	void addEdge(int node, int linked_node);	
	bool BFS(int start_node, int dest_node);
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

// loop through adj list + store in queue
bool Graph::BFS(int start_node, int dest_node){
	
	bool *visited = new bool(6);
	for (int i = 0; i < 6; ++i)
	{
		visited[i] = false;
	}

	queue<int> adj_nodes_queue;
	adj_nodes_queue.push(start_node);

	while(!adj_nodes_queue.empty()){
		 
		// evaluate each adj node
		int current_node = adj_nodes_queue.front();
		adj_nodes_queue.pop();
		cout << current_node << " "; // debug	
		if (current_node == dest_node){			
			cout << endl << "found!! ";
			for (int i = 0; i < 6; ++i) {cout << visited[i] << " ";}
			cout << endl;
			return true;
		}
		// enqueue current node's all adj nodes -> if current node not dest node
		std::vector<int>::const_iterator i;	// i: each adj node of current node
		for (i = adj[current_node].begin(); i != adj[current_node].end(); ++i){ 
			if (!visited[*i]){
				visited[*i] = true;
				adj_nodes_queue.push(*i);
			}		
		}
	}
	cout << endl << "not found!! " ;
	for (int i = 0; i < 6; ++i) {cout << visited[i] << " ";}
	cout << endl;
	return false; // after for loop thru all adj list nodes
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
    g.BFS(5,0);
    g.BFS(5,1);
    g.BFS(5,4);

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