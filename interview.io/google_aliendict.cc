/*

https://www.youtube.com/watch?v=7-7YeWgL5bs&ab_channel=interviewing.io

Given a list of lists in a lexigraphic ordering, return the ordering of the characters in the language.

i.e. given a list of "sorted" alien words, determine the lexigraphic ordering of letters

words = ["pbb", "bpku", "bpkb", "kbp", "kbu" ]
output = ['p', 'u', 'b', 'k']

1st: parse words_list into tree, each node contains a letter
2nd: BFS to generate array list of ordering on each level of nodes
3rd: merge all the list of orderings

i dont want to debug lol
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ChildrenNodes {
    char letter;
    Node* node_addr;
};

class Node{
    char letter;
    std::vector<ChildrenNodes> children_ordering;

    Node(char letter){
        this->letter = letter;
    }

    Node(char letter, char next_letter){
        this->letter = letter;
        next_node = new Node(next_letter);
    }

    void addChildrenNodes(char letter){

        Node* n = new Node(letter);
        children_ordering.push_back(n);
    };
};


class AlienDictTree {
    Node* starting_node = new Node;

    void add_letter_to_alien_tree(std::vector<string> words_list ){
        for (size_t i = 0; i < string.length(); i++) // each letter within word
        {            
            parent_nodes_list = next_parent_nodes_list;
            for (size_t j = 0; j < words_list.size();  j++) // each word
            {
                current_node = parent_nodes_list[j]; // node p 
                current_node.addChildrenNodes(words_list[j][i]); // node p add letter b
                next_parent_nodes_list.push_back(current_node); // cache parent nodes
            }
        }
    }


    // expected: [ ["p", "b", "k"], ["b"], ["p"], ["b"], ["b"], ["k"], ["p", "u"], ["u", "b"] ]
    void retrieve_ordered_letters(Node* starting_node, std::vector<std::vector<char>> results){

        for (size_t i = 0; i < starting_node.children_ordering.size(); i++)
        {
            results.push_back(starting_node.children_ordering[i]);
            child_node = starting_node.children_ordering[i].node_addr;
            retrieve_ordered_letters(child_node, results);
        }
    }
    

};



int main(){
    std::vector<string> words = ["pbb", "bpku", "bpkb", "kbp", "kbu" ];


}
