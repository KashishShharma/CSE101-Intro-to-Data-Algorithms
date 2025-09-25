//LIST HEADER FILE 

#ifndef LIST_H
#define LIST_H
#include "node.h"


class List {
	public:
	Node *head;
	List();
	void deleteList(); 
	Node* find(int, int);
	void insert(int, int);
	void sort();
	string print(string);
	Node* getNext(Node*);
	List blockList(int, int);
	Node* getNode(int);
	int lengthCol(int);
	int length();
	void insertList(List);
	Node* deleteNode(int, int);
	
};
#endif