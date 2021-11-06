/*
https://codereview.stackexchange.com/questions/78625/convert-an-array-to-a-binary-tree
*/
#include <iostream>
#include <cstdlib>
#include <cstdio>

template<class E>
struct TNode{
    E value;
    TNode<E>* leftChild;
    TNode<E>* rightChild;

    TNode<E>(){
        this->value = NULL;
        this->leftChild = NULL;
        this->rightChild = NULL;
    }

    TNode<E>(E value){
        this->value = value;
        this->leftChild = NULL;
        this->rightChild = NULL;
    }
};

template<class E>
class BTree{
private:
    TNode<E>* root;

    /**
        build and return the pointer to a binary tree for given array 'arr' and array         size 'len'
    */
    TNode<E>* build(E* arr, int len){

        TNode<E> *subRoot = new TNode<E>(arr[0]);
        if (len == 1){
            return subRoot;  // terminating function - at the leaf
        }
        E* elementsToLeft = new E[len];  // array to store the left subtree children
        E* elementsToRight = new E[len];  // array to store the right sub tree     children

        int counterLeft = 0;  
        int counterRight = 0;

        for (int i = 1; i < len; i = (i * 2) + 1){
            for (int j = i; j < i + ((i + 1) / 2); j++){
                elementsToLeft[counterLeft] = arr[j]; // appending the array which     has children of left sub tree
                counterLeft++;
                if ((j + (i + 1) / 2)<len){  // check whether there are childs to     store in the right sub tree....
                    elementsToRight[counterRight] = arr[j + (i + 1) / 2]; //   appending the array which has children of left sub tree
                    counterRight++;
                }

            }
        }
        subRoot->leftChild = build(elementsToLeft, counterLeft);  // recursive call>     array- left sub tree's children and size
        subRoot->rightChild = build(elementsToRight, counterRight); // recursive     call> array- right sub tree's children and size
        return subRoot;
    }

public:

    /**
    add the value specified by newvalueas the left child of the tree node specified     by parent,if the node does not have a left childalready.
    returns 1 if addition is successful and returns -1 in failure.
    */
    template <class E>
    int intaddLeftChild(TNode<E>* parent, E newvalue){
        if (parent->leftChild != NULL){ return -1; }
        TNode<E> *temp = new TNode<E>(newvalue);
        parent->leftChild = temp;
        return 1;
    }

    /**add the value specified by newvalueas the right child of the tree node     specified by parent, if the node does not have a right childalready.
    returns 1 if addition is successful and returns -1 in failure.
    */
    template <class E>
    int intaddRightChild(TNode<E>* parent, E newvalue){
        if (parent->rightChild != NULL){ return -1; }
        TNode<E> *temp = new TNode<E>(newvalue);
        parent->rightChild = temp;
        return 1;
    }

    /**
    function to create and return the pointer to a Binary tree from an array
    input an array. eg:- int i[] = {3,5,7} ; create_tree(i);
    */
    template<class E, int N>
    TNode<E>* create_tree(E(&elements)[N]){
        int length = N;
        return build(elements, N);
    }
};

int main(){
    //to demonstrate
    int nums[] = { 7,5,9,1,7,3};
    BTree<int> mal;

    TNode<int>* BinaryTree = mal.create_tree(nums); // store the made binary tree     from nums and point it by the pointer, BinaryTree.


}