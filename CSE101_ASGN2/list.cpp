//Taking some part of the code already given 
//in different assignments 

//Pasting the. below code from shakespear 
#include "list.h"
#include "node.h"
#include "cstdlib"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

List :: List(){
  head = NULL;
}



//check for existing position in the LinkedList by calling find 
//if yes, then do notthing 
//if no, creating a new node that represents the chessboard position 
//Insert the new node at begining of the list 
void List :: insert(int xcoor, int ycoor){
  if (find(xcoor, ycoor)!= NULL){ 
    return;
  }
  Node *latest = new Node(xcoor, ycoor);
  latest->next = head;
  head = latest;
  return;
}




//Find the next Noode in the LL that represents 
//a pos in the same column as the given previous node 
//prev = pointer to a node represents current position 
//if position found, found pointer should point to the next node 
//Compare x cordinate of found and prev?

Node* List :: getNext(Node*prev){
	Node *found = find(prev->x, prev->y);
	if (found == NULL || found->next == NULL){
		return NULL;
	}
	found = found->next;

	if (found->x == prev->x){
		return found;
	}
	return NULL;
}








//to search for a specific position 
//returns a pointer to the node in the LL 
//that contains the x and y cordinates 
//initiialise current to point to head 
//create a loop to iterate over each node in the LL 
//check if either of the cordinate matches
// Move to the the next code, if doesnt match 
Node* List :: find(int xcoor, int ycoor){
	Node *curr = head;
	while (curr != NULL){
		if (curr->x == xcoor && curr->y == ycoor){
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}








//create a new list of positions that are unreachable/blocked 
//curr is initialised to point to head. 
//loop until curr is !NULL. 
//confirmation statement if the current node is in a position 
//that is blocked by a queen 
//If true, block curr 
//remove the current List 

List List :: blockList(int x, int y){
	List blockout = List();
	Node *curr = head;
	while (curr != NULL){
		if (curr->x == x || curr->y == y || x-curr->x == y-curr->y || x-curr->x == curr->y - y){
			blockout.insert(curr->x, curr->y);
			deleteNode(curr->x, curr->y);
		}
		curr = curr->next;
	}
	blockout.insert(x, y);
	return blockout;
}









//this function would check for if col is 0 and if the list != 0
//if col = 0, function will remove the head node regdless of its column
//call delete function 
//loop until curr != NULL
//make sure you crosscheck the condition (curr->x == col)
//remove the node, return the pointer

Node* List :: getNode(int col){
	Node *curr = head;
	if (col == 0 && curr != NULL){
		return deleteNode(curr->x, curr->y);
	}
	while (curr != NULL){
		if (curr->x == col){
			return deleteNode(curr->x, curr->y);
		}
		curr = curr->next;
	}
	return NULL;
}










//basically make a function that determines 
//number of potential or placed queen positions exist in specific col
//I need this function to decide weather I can place new queen 
//or i have. tto backtrack 
int List :: lengthCol (int col){
	int count = 0;
	Node *curr = head;
	while (curr != NULL){
		if (curr->x == col){
			count++;
			//count = count + 1;
		}
		curr = curr->next;
	}
	return count;
}







//make a function to 
//get a total count of all nodes in the list 
int List :: length(){
	int length = 0;
	Node *curr = head;
	while (curr != NULL){
		length = length + 1;
		curr = curr->next;
	}
	return length;
}









//Function inseerts all nodes from the list 
//to current list 
void List :: insertList(List insertFrom){
	Node *to_add = insertFrom.getNode(0);
	//while (to_add->x, to_add->y){
	//to_add = insertFrom.getNode(0);
	while (to_add != NULL) {
		insert(to_add->x, to_add->y);
		to_add = insertFrom.getNode(0);
	}
	
	return;
}



//Taking help from already provided function 
void List :: sort(){
	Node *curr1 = head, *curr2 = head;
	Node *min;
	int tempx, tempy;
	while (curr1 != NULL){
		curr2 = curr1;
		min = curr2;
		while (curr2 != NULL){
			if (min->x > curr2->x || (min->x == curr2->x && min->y > curr2->y)){
				min = curr2;
			}
			curr2 = curr2->next;
		}
		tempx = curr1->x;
		tempy = curr1->y;
		curr1->x = min->x;
		curr1->y = min->y;
		min->x = tempx;
		min->y = tempy;

		curr1 = curr1->next;
	}
}





Node* List :: deleteNode(int x, int y){
	Node *prev = NULL;
	Node *curr = head;
	while (curr != NULL){
		if (curr->x == x && curr->y == y){
			break;
		}
		prev = curr;
		curr = curr->next;

	}
	if (curr == NULL){
		return NULL;
	}
	if (prev == NULL){
		head = head->next;
	} else {
		prev->next = curr->next;
	}
	return curr;
}



void List :: deleteList(){
	Node *curr = head;
	if(curr == NULL){
		return;
	}
	while (curr->next != NULL){
		Node *temp = curr->next;
		delete(curr);
		curr = temp;
	}
	delete(curr);
}


string List :: print(string delim){
	sort();
	if (head == NULL){
		return "";

	}
	string output = "";
	Node *curr = head;
	while (curr != NULL){
		output = output + to_string(curr->x) + delim + to_string(curr->y) + delim;
		curr = curr->next;
	}
	return output;

}



