/Taking more than half of the code from 
//Shakespeare and 
//Nqueens assignment 


#include <iostream>
#include "BST.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {
        throw std::invalid_argument("Usage: ./wordrange <INPUT FILE> <OUTPUT FILE>");
    }

    ifstream input;
    ofstream output;

    input.open(argv[1]);
    output.open(argv[2]);

    if (!input.is_open() || !output.is_open()) {
        throw std::runtime_error("Error opening input or output file");
    }

    char *com, *valstr, *op;
    BST myWords;

    string command;
    while (getline(input, command)) {
        if (command.length() == 0)
            continue;

        com = strdup(command.c_str()); // Duplicate command to manipulate it
        op = strtok(com, " \t");        // Extract operation ("i" or "r")

        if (op == nullptr) {
            free(com); 
            continue; // In case of a malformed line
        }

        valstr = strtok(NULL, " \t");   // Get the first value (for both insert and range)
        if (valstr == nullptr) {
            free(com); 
            continue; // Skip if no value was provided
        }

        if (strcmp(op, "i") == 0) { // Insertion operation
            if (myWords.find(valstr) == NULL) {
                myWords.insert(valstr);
            }
        } 
        else if (strcmp(op, "r") == 0) { // Range query
            char* valtwo = strtok(NULL, " \t"); // Get the second value for range queries
            if (valtwo != nullptr) {
                output << myWords.find_range(valstr, valtwo) << endl;
            }
        }

        free(com); // Free the duplicated command string
    }

    input.close();
    output.close();

    return 0;
}