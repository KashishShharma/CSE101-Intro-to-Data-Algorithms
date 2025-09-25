#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstring> //For manipulating arrays 
#include <cstdlib>

using namespace std;



typedef struct Node {
  char *word;
  int frequency;
  struct Node*next;

} Node;

int allocateddNodes = 0;
//Declaring all the functions 
//Node* createNode(const char* word);
//void readingTheFile(Node** wordList, const char* filename);
//void ModifyList(Node** head, const char*word);
//Node* JoiningLists(Node* left, Node*right);
//Node* SplitingList(Node* head);
//void finalList(Node** head);
//void handleInputOutput(Node** wordList, const char*inputfilename, const char*outputFile);


//Create a New node 
Node* createNode(char* word){
  Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode){
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}

  //strcpy(newNode->word, word);
  newNode->word = strdup(word);
  //free(word);
	if (!newNode->word){
		perror("failed to allocate memory");
		free(newNode);
		exit(EXIT_FAILURE);
	}
  newNode->frequency = 1;
  newNode->next = NULL;
	allocateddNodes++;
  return newNode;
}





void ModifyList(Node** head,char*word){
	Node*current = *head;
	Node*prev = NULL;
	while ( current != NULL && strcmp(current->word, word) !=0){
		prev = current;
		current = current->next;
	}
	if (current == NULL){
		Node* newNode = createNode(word);
		if(prev == NULL){
			*head = newNode;
		} else {
			prev->next = newNode;
		}
	} else {
		current->frequency++;
	}
}


//copied from the same box,
//I wrote the code at bottom and pasted it above

// I ALSO TTOOK HELP FRROM GEEKS FOR GEEKS 
//IN UNDERSTANDING HOW TO PROCESS THE FILE 
void readingTheFile(Node** wordList, const char* filename){
  //opening the file 
  FILE*file = fopen(filename, "r");
  //checking if the file was opened or not 
  if (file == NULL){
    perror("Error: could not open the file ");
    exit(EXIT_FAILURE);
  }
  char word[256];
  while (fscanf(file, "%s", word) != EOF){
    int length = strlen(word);
		if (length < 100){
    	ModifyList(&wordList[length], word);
  //reading words from the file and adding them to Linked Lists
  }
	}
  fclose(file);
  //closed the file 
}

//using same concept as one of the test. questions - Palindrome
Node* JoiningLists(Node* left, Node* right){
  //checking if the left list is empty
  if (!left) return right;
  if (!right) return left;

  //comapring nodes 
  if (left->frequency > right->frequency || (left->frequency == right->frequency && strcmp(left->word, right->word)< 0)) {
    
      left->next = JoiningLists(left->next, right);

      return left;
} else { 
  //if(right != NULL){
      right->next = JoiningLists(left, right->next);

      return right;

  }
}


Node * SplitingList(Node* head){
  //if the list is empty
  if ( !head || !head->next) return head;
  
  //Initialising pointers 
  Node* slow = head;
  Node*fast = head->next;
  //if (slow != NULL && fast != NULL){
    //Now slpiting in halves 
  while (fast && fast->next){
      
      //if (slow != NULL && fast->next != NULL){
    slow = slow->next;
    fast = fast->next->next;
  }
  Node* midhalf = slow->next;
  slow->next = NULL;
  //merging the sorted halves 
  //if (midhalf != NULL){
  return JoiningLists(SplitingList(head), SplitingList(midhalf)) ;
}

void finalList(Node** head){
  
    *head = SplitingList(*head);
  
}



void handleInputOutput(Node** wordList, const char*inputfilename, const char* outputfilename){
  FILE* inputFile = fopen(inputfilename, "r");
	if (inputFile == NULL){
		fprintf(stderr, " cant open %s: %s\n", inputfilename, strerror(errno));
		return;
	}
  FILE* outputFile = fopen(outputfilename, "w");
  if (outputFile == NULL ){
		fprintf(stderr, " cant open %s: %s\n", outputfilename,  strerror(errno));
		fclose(inputFile);
    //perror ("Could not open the file");
    return;
    
  }
  int length, rank;
  while (fscanf(inputFile, "%d %d", &length, &rank) != EOF) {
		if(length < 100){
			Node* current = wordList[length];
			int count = 0;
		
    //Node* current = wordList[length];
  	//int count = 0;
    	while (current != NULL && count < rank){
      	current = current->next;
      	count++;
    }
    if (current == NULL){
      fprintf(outputFile, "-\n");

    } 
    else {
      fprintf(outputFile, "%s\n", current->word);
    }
  } else {
		fprintf(outputFile, "-\n");
	}
	}

  fclose(inputFile);
  fclose(outputFile);
}



//void freeNode(Node** head){
	//Node* current = *head;
	//while (current){
		//Node* next = current->next;
		//free(current->word);
		//free(current);
		//current = next;

	//}
	//*head = NULL;
//}






//FOR FREEING UP MEMORY

void freeNode(Node** head){
	Node* current = *head;
	Node* nextNode;
	while (current!= NULL){
		nextNode = current->next;
		free(current->word);
		free(current);
		current = nextNode;
		
	}
	*head = NULL;
}









//Main 
int main(int argc, char* argv[]) {
  //checking the no. of arguments are provided
  if (argc < 3){
    fprintf(stderr, "Usage: %s <INPUT FILE> <OUTPUT FILE>\n", argv[0]);
    return 1;

  }
	//FILE* inputFile = fopen(argv[1], "r");
	//if (!inputFile) {
		//perror("Failed to open the input file");
	//	return 1;
	//}
	//FILE* outputFile = fopen(argv[2], "w");
	//if (!outputFile){
		//perror("Failed to open the output file");
		//fclose(inputFile);
		//return 1;
	//}
  //Inittialising an array 


	Node* head = NULL;
  Node* wordList[100]={NULL};
	readingTheFile(wordList, "shakespeare-cleaned5.txt");
  for (int i = 0; i < 100; i++){
    if (wordList[i] != NULL){
      finalList(&wordList[i]);

    }
  }
  handleInputOutput(wordList, argv[1], argv[2]);	


	//for memory
	//for(int i = 0; i < 100; i++){
		//freeNode(&wordList[i]);
	//}



	//Freeing all nodes 
	freeNode(&head);
  for (int i = 0; i < 100; i++){
    freeNode(&wordList[i]);
  }
  return 0;
  

}
