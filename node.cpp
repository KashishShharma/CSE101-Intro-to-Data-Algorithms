#include "node.h"
#include <cstdlib>
#include <string>
using namespace std;

Node :: Node(){
	x = 0;
	y = 0;
	next = NULL;
}

Node :: Node(int xcoor, int ycoor){
	x = xcoor;
	y = ycoor;
	next = NULL;
}