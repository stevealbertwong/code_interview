/*
adjacency list graph implementation

	Test graph :

	(0) <--(weight 9)--(4)--(weight 0)-->(1)
	^ 									  ^
	|									  |
(weight 8)								(weight 1)
	|									  |
    (5)--(weight 2)-->(2)--(weight 1)--->(3) 


g++ -std=c++14 dijkstra.cc -o dijkstra


tricky parts:

1. use current_path_cost to update lowest cost from start node to that node at each round

2. construct priority_queue 
	
	-> do not init other nodes to 999, otherwise bug: any nodes will be connected to each other
	-> store path that leads to min cost

3. implement priority_queue contains() n updates() as pq has no such API
	
	HACK: update pq cost as BST/Heap is not designed to "random get/set"
	-> enqueue duplicate node into priority queue, lower cost will pop first, 
	-> ignore duplicate that comes out later 

4. reconstuct path

	-> min node from priority queue is NOT path!!!!
	-> path is stored in priority queue node
	-> think of dijkstra as pq of "min path", each round explore 1 layer of adj node to update path until reach dest node

*/

#define SIZE 6

#include <iostream>
#include <numeric>
#include <list>
#include <vector>
#include <queue>
#include <set>
#include <cstdlib>
using namespace std;

// hacked way to print priority queue without popping all elements
template <class T, class S, class C>
S& Container(priority_queue<T, S, C>& q) {
    struct HackedQueue : private priority_queue<T, S, C> {
        static S& Container(priority_queue<T, S, C>& q) {
            return q.*&HackedQueue::c;
        }
    };
    return HackedQueue::Container(q);
}

class Graph{
public:
	struct weighted_connection{	
		int linked_node;
		int weight;
		weighted_connection(int ln, int w) : linked_node(ln), weight(w){};
	};

	struct adjacent_node {
		int node_id;
		int cost;
		vector<int> path; // store path that leads to min cost
		bool operator>(const adjacent_node& rhs) const { return cost > rhs.cost; }
	};

	// priority queue default is max heap -> comparison changes it to min heap
	class comparison {
	public:
		bool operator() (adjacent_node p1, adjacent_node p2) const {
			return (p1 > p2);
		}
	};

	Graph(int V); // Constructor
	void addEdge(int node, int linked_node, int weight);
	bool Dijkstra(int start_node, int dest_node);
	bool set_contains(int node_id, set<int> visited);
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

// helper -> whether node has been visited
bool Graph::set_contains(int node_id, set<int> visited){
	std::set<int>::iterator it;
	it = visited.find(node_id);

	if(it != visited.end()){
		return true; // found, visited
	}else{
		return false; // not found
	}	
}

bool Graph::Dijkstra(int start_node, int dest_node){

	vector<int> path(SIZE);	// store choosen path
	set<int> visited;	// set -> efficient n easy interface	
	int current_path_cost;	// update lowest cost from start node to that node

	// only init start node's cost to 0 -> if init other node to 999 -> any node will be connected to each other
	priority_queue<adjacent_node,vector<adjacent_node>,comparison> pq; // min heap
	adjacent_node pq_node;
	pq_node.node_id = start_node;
	pq_node.cost = 0;
	pq.push(pq_node);

	// hacked print pq
	vector<adjacent_node> &tasks = Container(pq);
    for(vector<adjacent_node>::iterator i=tasks.begin();i!=tasks.end();i++){    	
        cout << "node " << i->node_id << " cost is : " << i->cost <<endl;
    }

	while(!pq.empty()){
		 		
		int current_node = pq.top().node_id; // min cost node dequeued as lowest path
		int current_node_cost = pq.top().cost;
		vector<int> current_path = pq.top().path;
		pq.pop();

		if(set_contains(current_node, visited)){
			break; // hack since pq cannot update cost
		}		

		cout << "current node : " << current_node << endl;		
		visited.insert(current_node);
		current_path_cost += current_node_cost;

		// if found
		if(current_node == dest_node){
			for (int i = 0; i < current_path.size(); ++i)
			{
				cout << current_path[i] << endl;
			}
			return true;
		}

		// current node's all unvisited adj nodes -> updates newest cost in priority queue 
		std::vector<Graph::weighted_connection>::const_iterator i;
		for (i = adj[current_node].begin(); i != adj[current_node].end(); ++i){			
			if(!set_contains(i->linked_node, visited)){ // if node not yet "becomes lowest path"				
				// if node's newest cost lower than node's pq cost -> update pq
				int updated_node_cost = current_path_cost + i->weight;
				
				// hack -> instead of update, creates new node in pq
				adjacent_node pq_node;
				pq_node.path = current_path;
				pq_node.path.push_back(current_node);
				pq_node.node_id = i->linked_node;
				pq_node.cost = updated_node_cost;
				pq.push(pq_node);
			}
		}
	}

	return false;
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
    // bool res = g.Dijkstra(5, 1);
    // bool res = g.Dijkstra(5, 0);
    bool res = g.Dijkstra(5, 3);
    // bool res = g.Dijkstra(5, 4);
    if(res){
    	cout << "found " << endl;
    }else{
    	cout << "not found " << endl;
    }
    
/*	
	Test graph :

	(0) <--(weight 9)--(4)--(weight 0)-->(1)
	^ 									  ^
	|									  |
(weight 8)								(weight 1)
	|									  |
    (5)--(weight 2)-->(2)--(weight 1)--->(3) 

*/
    // cout << g;

    return 0;
}