//  Christian Norfleet
//  Binary Expression Tree
//  prog3b2.cpp
//  This program will read in data from a file and process it 
//  to to a tree. Functions will then traverse the tree displaying,
//  evaluating, and reducing it.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "BTree.h"

using namespace std;

//Create a template for storing player entires to tree 
typedef vector<int> PlayerLog;

//Tree depth constraints
const int MAX_DEPTH = 100;
const int MIN_DEPTH = 1;

struct GameParamaters
{
	int depth = 0;
	int turns = 0;
};

void DoBuildTree(BTree  & T, ifstream & infile, char dir);
/*precond: T is created and infile is open for reading and
		   file is in "correct" format
postcond:  Reads the file and builds up the data in the subtree
		   referenced by the cursor in preOrder
		   dir is the left or right child position the next
		   item goes into
checks:	   NONE  */

void BuildTree(BTree  & T, ifstream & infile);
/*precond: T is created and infile is open for reading
		   and file is in "correct" format
postcond:  Reads the file and builds up the data in the Tree
		   in preOrder
checks:	   NONE  */

void DoInOrder(BTree  & T);
/*precond:  T is created
postcond:   Traverses the binary subtree referenced by T's cursor
			in inorder.
			Visit a node means print out its data to monitor.  T = #T.
checks:     NONE */

void Inorder(BTree  & T);
/*precond:  T is created
postcond:   Traverses the binary tree T in inorder.
			Visit a node means print out its data to monitor.
			T = #T, except T's cursor is referencing the root
checks:     NONE */

// DECLARE AND SPECIFY ADDITIONAL NON-MEMBER FUNCTIONS HERE

int ord(char item);
/*precond:  a valid char is passed in
postcond:   Converts the char to an int
checks:     NONE */

void Welcome(int& depth);
/*precond:  a valid infile is passed in
postcond:   displays welcome msg and reads number of depth
checks:     NONE */

void InputTurn(GameParamaters parmtr, PlayerLog& p_1, PlayerLog& p_2);
/*precond:  the player logs are initiated
postcond:   enters the players' entry into log
checks:     the entry is between the values of 1-100 */

void PrintEntries(GameParamaters parmtr, PlayerLog& p_1, PlayerLog& p_2);
/*precond:  the player logs are initiated
postcond:   prints out list entries for each player
checks:     NONE */

int DepthSummation(int depth);
/*precond:  a integer of depth > 0 is passed in 
postcond:   will convert tree depth to number of total turns
checks:     NONE */

void Closing();
/*precond:  NONE
postcond:   displays closing msg and closes infile
checks:     NONE */

int main()
{

	BTree T;
	PlayerLog player_1(10);
	PlayerLog player_2(10);
	GameParamaters gameconfig;

	//get depth of tree
	Welcome(gameconfig.depth);

	//process depth to derive turns needed
	gameconfig.turns = DepthSummation(gameconfig.depth);

	//enters the players' entry into log
	InputTurn(gameconfig, player_1, player_2);

	//Print player 1 moves
	//Print plaer 2 moves

	//Calculate winner

	//close input file
	Closing();

	//Clear Tree

	system("pause");

	return 0;
}

int DepthSummation(int depth)
{
	int turns = 0;
	for (int i = depth; i--; i>=0)
	{
		turns+= pow(2, i);
	}
	return turns + 1;
}

void DoBuildTree(BTree & T, ifstream & infile, char dir)
{
	ItemType item;

	//read one char
	item = infile.get();

	//if eof or eol
	if (infile.eof() || (item == '\n'))
		return;

	//if not eof and not eol
	if (!infile.eof() && (item != '\n'))
	{
		//CONSUME SPACES UNTIL I GET DATA
		while ((item == ' ') && (!infile.eof()))
		{
			item = infile.get();
		}
		//BUILD ROOT OF SUBTREE
		if (T.IsEmpty())
			T.CreateFirstNode(item);

		else if (dir == 'L') 
		//building left subtree so need
		//to add left child
		{
			T.AddLeft(item);
			T.ShiftLeft();
		}

		else //means its 'R' (right)
		{
			T.AddRight(item);
			T.ShiftRight();

		}

		//CHECK IF ITEM IS OPERATOR
		if ((item == '+') || (item == '-') || (item == '/')
			|| (item == '*'))
		{
			//building left subtree
			DoBuildTree(T, infile, 'L');
		}
		
		else
		{
			//GETBACK TO ROOT OF SUBTREE if its not operator
			if (T.HasParent())
				T.ShiftUp();

			//RETREAT UNTIL I GET TO A NODE W/ EMPTY RIGHT SUBTREE
			while (T.HasParent() && T.HasRightChild())
				T.ShiftUp();

			DoBuildTree(T, infile, 'R');
		} //end else
	}
}

//calls DoBuildTree
void BuildTree(BTree  & T, ifstream & infile)
{
	T.ClearTree();
	DoBuildTree(T, infile, 'L');
	T.ShiftToRoot();
}

//called by InOrder
void DoInOrder(BTree  & T)
{
	ItemType Item;

	//2 base cases: empty tree or subtree is a leaf
	if (!T.IsEmpty())
	{
		//not a leaf, has a left child, traverse left subtree of subtree
		//in InOrder
		if (T.HasLeftChild())
		{
			T.ShiftLeft();
			DoInOrder(T);
			T.ShiftUp();
		}

		//Display the item
		T.RetrieveItem(Item);
		cout << Item << "  ";

		//not a leaf, has a right child, traverse right subtree
		//of subtree in InOrder
		if (T.HasRightChild())
		{
			T.ShiftRight();
			DoInOrder(T);
			T.ShiftUp();
		}
	}
}

//Calls do InOrder
void Inorder(BTree  & T)
{
	T.ShiftToRoot();

	if (T.IsEmpty())
		cout << "Tree is empty" << endl;
	else
	{
		cout << "Tree contains: " << endl;
		DoInOrder(T);
	}
}

//Converts char to int
int ord(char item)
{
	int digit = int(item);
	return digit - 48;
}

//Displays welcome msg
void welcome(int& depth)
{
	char infilename[40];

	cout << "This game will ask for a number between 1-100. ";
	cout << "Players will then take depth entering unique values";
	cout << ", which in turn will be added to a Red Black Tree. ";
	cout << "The player with the greatest amount of leaf nodes wins!\n\n";
	do
	{
		cout << "Please enter depth of tree: ";
		cin >> depth;

		if (depth > MIN_DEPTH || depth < MAX_DEPTH)
			cout << "Invalid amount. Please reenter.\n\n";
	}
	//loop until valid infile
	while (depth > MIN_DEPTH || depth < MAX_DEPTH);
}

void InputTurn(GameParamaters parmtr, PlayerLog& p_1, PlayerLog& p_2)
{
	for (int i = (parmtr.turns / 2); i > 0; i--)
	{
		//Stores the player entry in log begining @ position 0
		cout << "Player 1? ";
		cin >> p_1[parmtr.turns / 2 - i];
			//if found
				//print error
			//if NOT IN RANGE
				//print error
		cout << "Player 2? ";
		cin >> p_2[parmtr.turns / 2 - i];
			//if found
				//print error
			//if NOT IN RANGE
				//print error
	}
}

void PrintEntries(GameParamaters parmtr, PlayerLog& p_1, PlayerLog& p_2)
{
	cout << "\n\nPlayer 1 entered: ";
	for (int i = 0; i <= p_1.size; i++)
	{
		cout << p_1[i] << " ";
	}

	cout << "\n\nPlayer 2 entered: ";
	for (int i = 0; i <= p_2.size; i++)
	{
		cout << p_2[i] << " ";
	}
}

//Displays closing msg
void closeing(ifstream & infile)
{
	cout << "\n\nTHANK YOU\n";
	//close infile
	infile.close();
}
