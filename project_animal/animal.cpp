/*
	animal.cpp

	author: Gazi Morshed
	date:   

	Animal/20 questions program for CSCI 262, Spring 2018. 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include<vector>
using namespace std;




class node {
public:
    string data;
    node* left;
    node* right;
};
// function prototypes. 
node* read_game_tree();
void read_preorder(node*tree, ifstream &fin);
void play_game(node* root,vector<string> &game_log);
void save_game_tree(node* root);
void delete_game_tree(node* root);
void write_tree(node *tree, ofstream &fout);

int main() {
	node* root = read_game_tree();
	if (root == NULL) return -1;
	while (true) {
		vector<string> game_log; //a new game_log everytime
		string tmp;
		int choice;
		cout << "Welcome to 20 questions!" << endl;
		cout << "  1) Play the game" << endl;
		cout << "  2) Save the game file" << endl;
		cout << "  3) Quit" << endl;
		cout << "Please make your selection: ";
		cin>>tmp;
		choice = atoi(tmp.c_str());

		switch (choice) {
		case 1:
			play_game(root, game_log);
			break;
		case 2:
			save_game_tree(root);
			break;
		case 3:
			break;
		default:
			cout << "Sorry, I don't understand." << endl << endl;
		}
		if (choice == 3) break;
	}
	
	delete_game_tree(root);
	return 0;
}

node* read_game_tree(){ //this function will read the game tree and return it's root
	node* root_of_tree = new node;
	ifstream fin("animal.txt");
	if(!fin){
		cerr<<"Error opening file"<<endl;
		return root_of_tree;
	}
	read_preorder(root_of_tree, fin);
	fin.close();
	return root_of_tree;
}
void read_preorder(node*tree, ifstream &fin){
	string identifier;
	fin>>identifier;
	string question; 
	fin.ignore(); //ignore the space; 
	getline(fin, question);
	if(identifier == "#A"){ //if the identifier is a leaf node, output the questions and recurse back
		tree->data = question;
	}
	else{  //as long as the identifer is a question, we'll do the followings. 
		tree->data = question;
		node *p1 = new node; //for the left recursive call
		node *p2  = new node; //for right recursive call
		tree->left= p1;
		tree->right =p2;
		read_preorder(tree->left, fin); //left child call
		read_preorder(tree->right, fin); //right child call;
	}
	
}


void play_game(node* tree, vector<string> &game_log) //This helps implement the game 
{	
	string answer;
	string answer1;
	
	cout << tree->data << endl;//Displays the tree question 

	game_log.push_back(tree->data);//We pushback into vector to store the question 

	cout << " (y/n)" << endl;
	cin >> answer;

	game_log.push_back(answer);

	if (tree->left == NULL && tree->right == NULL)
	{
		if (answer == "y") 
		{

			cout << "YAY! I guessed your animal " << endl;

		}
		else 
		{

			cout << "Boo! I don't know!" << endl;

			cout << "Would you like to expand the game tree (y/n)?";

			cin >> answer;
			
			cin.ignore();
			cout<<"I asked the following: "<<endl;

			if (answer == "y")
			{
			
				for (int i = 0; i < game_log.size();i++) //Displays the log 
				{	
					if (game_log[i] == "y"){
						cout<<"YES"<<endl;	
					}
					else if (game_log[i] =="n"){
						cout<<"NO"<<endl;
					}
					else {
						cout << game_log[i] << endl;	
					}
				}
				
				cout << "Enter a new animal in the form of a question, e.g., 'Is it a whale?': " << endl;
				getline(cin,answer);

				cout <<  "Now enter a question for which the answer is 'yes' for your new"<<endl;
		        cout << "animal, and which does not contradict your previous answers: " << endl;
				getline(cin, answer1);

				tree->right = new node;
				tree->right->data = tree->data;//We transfer the root data to the right branch 

				tree->left = new node;
				tree->left->data = answer; //We assign the question to the left 
				tree->data = answer1;
				
				//setting the leaf nodes pointer to be NULL.
				tree->left->left = NULL;
				tree->left->right = NULL;
				tree->right->left=NULL;
				tree->right->right=NULL;
			}

			else
				return;//nothing happens here 

		}
	}


	else if (answer == "y") //If the user answers yes we go the left branch and recurse
	{

		tree = tree->left;
		play_game(tree, game_log);
		game_log.push_back(tree->data);
		game_log.push_back(answer);
		
	}

	else if (answer == "n")
	{

		tree = tree->right;
		play_game(tree, game_log);
		game_log.push_back(tree->data);
		game_log.push_back(answer);
		
	}

}

void save_game_tree(node* tree){
	ofstream fout("animal.txt"); //open the file for writing. 
	if(!fout){
		cerr<<"Error opening file."<<endl;
	}
	write_tree(tree, fout); //calling the function that will write the file
	fout.close();
}

void write_tree(node *tree, ofstream &fout){
	if(tree->left==NULL && tree->right == NULL){  //check for leaf condition. 
		fout<<"#A "<<tree->data<<endl; //write to the file. 
	}
	else{
		fout<<"#Q "<<tree->data<<endl; //write the internal node
		write_tree(tree->left, fout); //recurse on the left subtree
		write_tree(tree->right, fout); //recurse on the right subtree
	}
}


void delete_game_tree(node* tree){
	if(tree->left==NULL && tree->right == NULL){  //check for leaf condition. 
		delete tree; 
	}
	else{
		delete_game_tree(tree->left);
		delete_game_tree(tree->right);
		delete tree; //to delete the root
	}
}
