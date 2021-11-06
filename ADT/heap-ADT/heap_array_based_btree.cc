/*
binary/max/min heap -> always sorted binary tree

Array-based binary heap -> 
It’s a complete tree (All levels are completely filled except 
possibly the last level and the last level has all keys as left 
as possible). This property of Binary Heap makes them suitable to 
be stored in an array.
	
HEAP IS NOT A TREE since NOT DIRECTED, IMPLEMENTED IN LINKED NODES

Arr[(i-1)/2]	Returns the parent node (if odd, de)
Arr[(2*i)+1]	Returns the left child node
Arr[(2*i)+2]	Returns the right child node

https://www.geeksforgeeks.org/binary-heap/
https://www.cs.cmu.edu/~adamchik/15-121/lectures/Binary%20Heaps/heaps.html

TODO
1. init w random order array MinHeap(int* num_array); 
2. generic initiator from array -> heapSort(), just insertKey() on array

g++ -std=c++11 heap_array_based_btree.cc -o heap_array_based_btree
*/

#include <iostream>
#include <climits>
using namespace std;

void swap(int *x, int *y); // prototype -> alternative to private method
 
class MinHeap{
    int *heap_array; // pointer to array heap_array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap

    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }
    
    void swap(int *x, int *y);
    void bubbleUp(int i); // swap w parent node if smaller -> recrusion
    void iterative_bubbleUp(int i);
    void heapify(int i); // find smallest child, swap i.e. bubble down -> recrusion
    void iterative_heapify(int i); 

public:    
    MinHeap(int capacity);        
    
    void insertKey(int k); // append at end + bubble up
    int popMin(); // swap 1st w last node + delete 1st node + heapify()/bubble down
    void deleteKey(int k); // find n inf_min key + bubble up key + popMin()    
    void decreaseKey(int i, int new_val); // find n decrease key + bubble up key
    
    int getMin() { return heap_array[0]; } 
};

MinHeap::MinHeap(int cap){
    heap_size = 0;
    capacity = cap;
    heap_array = new int[cap];
}

// not real swap of addr, just swap data
void MinHeap::swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void MinHeap::bubbleUp(int i){
    if(i != 0 && heap_array[parent(i)] > heap_array[i]){
       swap(&heap_array[i], &heap_array[parent(i)]);
       i = parent(i);
       bubbleUp(i); // recursion
    }   
}

void MinHeap::iterative_bubbleUp(int i){
    while (i != 0 && heap_array[parent(i)] > heap_array[i]){
       swap(&heap_array[i], &heap_array[parent(i)]);
       i = parent(i);
    }
}

void MinHeap::insertKey(int k){
    if (heap_size == capacity){
        cout << "\nOverflow: Could not insertKey\n";
        return;}
 
    // 1st: insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    heap_array[i] = k;
 
    // 2nd
    bubbleUp(i);
}

/*
Decreases value of key. The time complexity of this operation is O(Logn). 
If the decreases key value of a node is greater than the parent of the 
node, then we don’t need to do anything. Otherwise, we need to traverse 
up to fix the violated heap property
*/
void MinHeap::decreaseKey(int i, int new_val){
    heap_array[i] = new_val;
    bubbleUp(i);
}
 

void MinHeap::deleteKey(int k)
{
    for (int i = 0; i < capacity; ++i){
        if(heap_array[i] == k){
            decreaseKey(i, INT_MIN); // minimum infinity
            popMin(); // delete key after bubbled up to top
            break;            
        }
    }
    cout << "key not found" << endl;
}

/*
Removes the minimum element from MinHeap.

Time Complexity of this Operation is O(Logn) as this operation 
needs to maintain the heap property (by calling heapify()) after 
removing root.
*/
int MinHeap::popMin(){

    // edge cases: 0 or 1 element
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1){
        heap_size--;
        return heap_array[0];}
 
    // Store the minimum value, and remove it from heap
    int root = heap_array[0];
    heap_array[0] = heap_array[heap_size-1]; // swap root w biggest/last 
    heap_size--;

    // heapify(0);
    iterative_heapify(0); // bubble down 1st element
 
    return root;
}

// bubble down
void MinHeap::heapify(int i){
    
    // 1st: find smallest child
    int l = left(i);
    int r = right(i);
    int smallest = i; // index of smaller child
    if (l < heap_size && heap_array[l] < heap_array[i]) // if left smaller
        smallest = l;
    if (r < heap_size && heap_array[r] < heap_array[smallest])
        smallest = r;

    // 2nd: recursively swap()
    if (smallest != i){ // base case, if any children smaller
        swap(&heap_array[i], &heap_array[smallest]);
        heapify(smallest); // recursion
    }
}

void MinHeap::iterative_heapify(int i){	
	int smallest = i;

	while(1){
		// 1st: find smallest child
        int l = left(i);
    	int r = right(i);    	    	
    	if (l < heap_size && heap_array[l] < heap_array[i])
	        smallest = l;
	    if (r < heap_size && heap_array[r] < heap_array[smallest])
	        smallest = r;

        // 2nd: swap with smallest child
	    if (smallest != i){ // base case	    
	        swap(&heap_array[i], &heap_array[smallest]);	        
	    } else {	    	
	    	break; // swapped heap_array bubble down
	    }
	    i = smallest;
	}
}
 
// Driver program to test above functions
int main()
{
    MinHeap h(11);
    h.insertKey(3);
    h.insertKey(2);
    h.deleteKey(1);
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);
    // cout << h.popMin() << " ";
    // cout << h.getMin() << " ";
    // h.decreaseKey(2, 1);
    // cout << h.getMin();
    return 0;
}