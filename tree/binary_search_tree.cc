/*
Author: steven wong

BST == BT with slightly complex add n very complex delete
BST used to implement set and map

pass pointer by reference since need to swap node

g++ -std=c++11 binary_search_tree.cc -o binary_search_tree
*/
#include <iostream>
#include <math.h>
using namespace std;

template <class T>
struct TreeNode { // TreeNode<T> <- namespace

	TreeNode(T val, TreeNode<T> *left = NULL, TreeNode<T> *right = NULL) {
        this->value = val;
        this->left = left;
        this->right = right;
    }

    T value;
    TreeNode<T> *left;
    TreeNode<T> *right;
};

template <class T>
class BST{ // BST<T> <- namespace
	private:
		TreeNode<T> *root;
		void add_node_helper(TreeNode<T>*& node, T val);		
		void delete_all_nodes(TreeNode<T>*& node);
		void delete_node_helper(TreeNode<T>*& node, T val);
		void print_helper(TreeNode<T>* node);
	
	public:
		BST(){};
		~BST();	
		void add_node(T val);		
		void print();
		void node_count();
		void delete_node(T val);
		TreeNode<T>* getMin(TreeNode<T>* node);
};

template <class T>
BST<T>::~BST(){	
	delete_all_nodes(root);
};

template <class T>
void BST<T>::delete_all_nodes(TreeNode<T>*& node){
	if(node!=NULL){
		delete_all_nodes(node->left);
		delete_all_nodes(node->right);
		delete node;		
	}
}

template <class T>
void BST<T>::add_node_helper(TreeNode<T>*& node, T val){ // pointer by reference
	
	// does nothing if val == node->val
	if(node == NULL){ // base case: found empty spot
		node = new TreeNode<T>(val); // pointer by reference, else just local var
	
	} else if(val < node->value) { // goes left 
		add_node_helper(node->left, val);
	
	} else if(val > node->value) { // goes right 
		add_node_helper(node->right, val);
	} 
}

template <class T>
void BST<T>::add_node(T val){
	add_node_helper(root, val);
}

template <class T>
TreeNode<T>* BST<T>::getMin(TreeNode<T>* node){
	if (node->left == NULL){
		return node;		
	} else {
		getMin(node->left);
	}
}

template <class T>
void BST<T>::delete_node_helper(TreeNode<T>*& node, T val){ // pointer by reference
	
	// 1st: traverse to node 
	if(node == NULL){ // base case: failed to find such node
		return;	

	} else if(val < node->value) { // recurse left 
		delete_node_helper(node->left, val);
	
	} else if(val > node->value) { // recurse right 
		delete_node_helper(node->right, val);

	// 2nd: swap() to replace if no/single child
	// swap() w center(min right/max left) if both child	
	} else if(val == node->value){ // found that node !

		if(node->left && node->right == NULL){ // no child
			delete node;

		} else if (node->left == NULL){ // only right child
			TreeNode<T>* trash = node;
			node = node->right; // parent->left = parent->left->right
			delete trash;

		} else if (node->right == NULL){ // only left child
			TreeNode<T>* trash = node;
			node = node->left; // update parent's child addr -> SWAP ADDR
			delete trash;

		} else { // both children exist					
			TreeNode<T>* mr_node = getMin(node->right); // max left or min right -> 1 right all left
			node->value = mr_node->value;	// SWAP DATA
			// delete mr_node; // CANNOT -> since min node might have right child !!!!!!!
			delete_node_helper(node->right, mr_node->value); // delete min node 
		}
	}
}

template <class T>
void BST<T>::delete_node(T val){
	delete_node_helper(root, val);
}

template <class T>
void BST<T>::print_helper(TreeNode<T>* node){	
	if(node != NULL){		
		print_helper(node->left);
		cout << node->value << endl;
		print_helper(node->right);
	}
}

template <class T>
void BST<T>::print(){
	print_helper(root);
}


int main(int argc, char const *argv[]){
	
	// TreeNode<int> n = TreeNode<int>(10);
	TreeNode<int> *n = new TreeNode<int>(10);
	BST<int> bst = BST<int>();
	bst.add_node(10);
	bst.add_node(5);
	bst.add_node(1);
	bst.add_node(99);
	bst.add_node(16);
	bst.print();
	bst.delete_node(16);
	bst.delete_node(1);
	bst.add_node(2);	
	bst.print();



	return 0;
}