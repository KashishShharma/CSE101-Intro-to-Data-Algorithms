#ifndef BST_H
#define BST_H

#include <string>
#include "customstring.h"
using namespace std;


//Taking help from previous assignments header files that I wrote

//class Node{
	//public:
//	string key;
	//int height;
	//int subtree;
	//Node *left, *right, *parent;
	//Node(){
		//left = NULL;
		//right = NULL;
		//parent = NULL;

	//}
	//Node (string val){
		//key = val;
		//left = NULL;
		//right = NULL;
		//parent = NULL;
	//	height = 0;
		//subtree = 1;
	//}

//};
class Node {
public:
    CustomString key;
    int height;
    int subtree;
    Node* left;
    Node* right;
    Node* parent;

    Node() : left(NULL), right(NULL), parent(NULL), height(1), subtree(1) {}
    Node(const char* val) : key(val), left(NULL), right(NULL), parent(NULL), height(1), subtree(1) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node*, Node*);
    Node* rLeft(Node*);
    Node* rRight(Node*);
    Node* update(Node*, Node*);
    int minLeaf(const CustomString&, Node*);
    int maxleaf(const CustomString&, Node*);
    void printInOrder(Node*, CustomString&);
    void printPreOrder(Node*, CustomString&);
    void printPostOrder(Node*, CustomString&);
    Node* find(Node*, const CustomString&);
    Node* minNode(Node*);  // Add this declaration
    Node* maxNode(Node*);  // Add this declaration
    void deleteBST(Node*);  // Add this declaration

public:
    BST();
    void insert(const char*);
    Node* find(const char*);
    int find_range(const char*, const char*);
    void deleteBST();
    Node* deleteKey(const char*);
    Node* deleteNode(Node*);
    CustomString printInOrder();
    CustomString printPreOrder();
    CustomString printPostOrder();
};

#endif