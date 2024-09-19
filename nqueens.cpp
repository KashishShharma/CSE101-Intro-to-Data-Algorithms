//Taking all of this from previously provided asgns 
//wrapper file
//using built in lib



#include <iostream>
#include "list.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
using namespace std;

class Pair{
	public:
		Node *queen;
		List blockout;
};


//attempt to find a sol to N-queens problem 
//given: initial set of queen placementts 
//should return a list of queen posiitions 
List find_queens(string user_input){
	stack<class Pair> queenStack;

	char *dup, *ttok, *temp;//stack to manage the state of board
	dup = strdup(user_input.c_str());
	ttok = strtok(dup, " \t");
	//strtok to tokenise the input string
	//ttok will represent the board size
	int size; //converts the token to an integer. 
	size = strtol(ttok, &temp, 10);
	List open;
	List queens;
	int queens_status[size];
	//List initialising 
	//open positions initialising 
	//every position is insertedd into open list 
	for (int i = 1; i < size + 1; i = i + 1){
		for (int j = 1; j < size + 1; j = j + 1){
			open.insert(i, j);
			queens_status[i]=0;
		}
	}
	int x, y;
	char *x_tok, *y_tok;
	x_tok = strtok(NULL, " \t");
	y_tok = strtok(NULL, " \t");






	//loop to iterate through the input string 
	//should have the following condition 
	//the loop should continue until both corrdinates !=NULL
	//initialise pair

	while (x_tok != NULL && y_tok != NULL){
		Pair init;
		x = strtol(x_tok, &temp, 10);
		y = strtol(y_tok, &temp, 10);

		if (open.find(x,y) == NULL){
			List empty;
			return empty;
		}
		//insert queen position intto list 
		//update column status. 
		//column numbers are 1- based 
		//x - 1 to 1 marks the column occupied by initial queen. 

		queens.insert(x, y);
		queens_status[x-1] = 1;
		open.blockList(x, y);
		//updating open positions 
		//and maybe get next cordddinates 
		x_tok = strtok(NULL, " \t");
		y_tok = strtok(NULL, " \t");
		
	}

	int curr_col = 1;
	open.sort();
	while (curr_col <= size){
		if (queens_status[curr_col-1]==1){
			curr_col = curr_col + 1;
		} else if (open.lengthCol(curr_col) == 0){
			Pair to_add;
			bool yes_found = false;
			while (yes_found == false){
				Pair removed = queenStack.top();
				open.insertList(removed.blockout);
				open.sort();
				curr_col = removed.queen->x;
				queens_status[curr_col-1] = 0;
				to_add.queen = open.getNext(removed.queen);
				queenStack.pop();


				if (to_add.queen != NULL){
					to_add.blockout = open.blockList(to_add.queen->x, to_add.queen->y);
					queens_status[curr_col-1]=2;
					queenStack.push(to_add);
					yes_found = true;
				}
				if (queenStack.size() == 0){
					return List();
				}
			}
			curr_col = curr_col + 1;
		} else {
			Pair to_add;
			to_add.queen = open.getNode(curr_col);
			to_add.blockout = open.blockList((to_add.queen)->x, (to_add.queen)->y);
			queenStack.push(to_add);
			queens_status[curr_col - 1] = 2;
			curr_col = curr_col + 1;
		}
	}




	open.sort();
	while (queenStack.size()>0){
		Node *removed = queenStack.top().queen;
		queenStack.pop();
		queens.insert(removed->x, removed->y);

	}
	return queens;

}



//Taking help from already provided main in shakespear
int main(int argc, char** argv){
	if (argc < 3){
		throw std::invalid_argument("Usage: ./hello <INPUT FILE> OUTPUT FILE>");
	}
	ifstream input;
	ofstream output;
	input.open(argv[1]);
	output.open(argv[2]);

	string user_input;

	while (getline(input, user_input)){
		if (user_input.length() == 0)
			continue;


		List queen_list = find_queens(user_input);

		if (queen_list.length() == 0){
			output << "No solution\n";

		}else{
			output << queen_list.print(" ") << endl;
		}
		queen_list.deleteList();
	}
	input.close();
	output.close();
}