#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;
class Node{
	public:
	int x;
	int y;
	Node *next;
	Node();
	Node(int, int);
};
#endif