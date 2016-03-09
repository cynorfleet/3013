//  Christian Norfleet
//  Program 3A
//  prog3a2.cpp
//  This program will read in data from a file and process it 
//  to to a tree. Functions will then traverse the tree

#include <iostream>
#include <string>
#include <fstream>
#include "BTree.h"

using namespace std;

struct EquationType
{
	int term1 = 0;
	int term2 = 0;
	char Opert = NULL;
	int answer = 0;
};

struct ReductionType
{
	char term1 = NULL;
	char term2 = NULL;
	bool flag = NULL;
};

void DoBuildTree(BTree  & T, ifstream & infile, char dir);
/*precond: T is created and infile is open for reading and
		   file is in "correct" format
postcond:  Reads the file and builds up the data in the subtree
		   referenced by the cursor in preOrder
		   dir is the left or right child position the next
		   item goes into
checks:	   none  */

void BuildTree(BTree  & T, ifstream & infile);
/*precond: T is created and infile is open for reading
		   and file is in "correct" format
postcond:  Reads the file and builds up the data in the Tree
		   in preOrder
checks:	   none  */

void DoInOrder(BTree  & T);
/*precond:  T is created
postcond:   Traverses the binary subtree referenced by T's cursor
			in inorder.
			Visit a node means print out its data to monitor.  T = #T.
checks:     none */

void Inorder(BTree  & T);
/*precond:  T is created
postcond:   Traverses the binary tree T in inorder.
			Visit a node means print out its data to monitor.
			T = #T, except T's cursor is referencing the root
checks:     none */

// DECLARE AND SPECIFY ADDITIONAL NON-MEMBER FUNCTIONS HERE

void Preorder(BTree & T);
/*precond:  T is created
postcond:   Traverses the binary tree T in preorder.
			Visit a node means print out its data to monitor.
			T = #T, except T's cursor is referencing the root
checks:     none */

void DoPreorder(BTree & T);
/*precond:  T is created
postcond:   Traverses the binary tree T in preorder.
			Visit a node means print out its data to monitor.
			T = #T, except T's cursor is referencing the root
checks:     none */

void Postorder(BTree & T);
/*precond:  T is created
postcond:   Traverses the binary tree T in postorder.
			Visit a node means print out its data to monitor.
			T = #T, except T's cursor is referencing the root
checks:     none */

void DoPostorder(BTree & T);
/*precond:  T is created
postcond:	Traverses the binary tree T in postorder.
		    Visit a node means print out its data to monitor.
		    T = #T, except T's cursor is referencing the root
checks:		none */


void SumTree(BTree & T, int & acounter);
/*precond:  T is created, counter is initialized
postcond:   Traverses the binary tree T in inorder.
			Visit a node means print out its data to monitor.
			T = #T, except T's cursor is referencing the root,
			while incrementing counter by value of node;
checks:     none */

void DoSumTree(BTree & T, int & acounter);
/*precond:  T is created, counter is initialized
postcond:   Traverses the binary tree T in inorder.
			Visit a node means print out its data to monitor.
			T = #T, except T's cursor is referencing the root,
			while incrementing counter by value of node;
checks:     none */

int ord(char item);
/*precond:  a valid char is passed in
postcond:   Converts the char to an int
checks:     none */

void welcome(ifstream & infile, int& expcounter);
/*precond:  a valid infile is passed in
postcond:   displays welcome msg and reads number of expressions
checks:     none */

void closeing(ifstream & infile);
/*precond:  a valid infile is passed in
postcond:   displays closing msg and closes infile
checks:     none */

bool AllConsts(BTree& T);
/*precond:	a initialized tree
postcond:   if tree contains all constants and operators,
			true is returned
checks:     none */

bool DoAllConsts(BTree& T, bool& flag);
/*precond:  a initialized tree
postcond:	Traverses the binary tree T in Preorder.
			If tree contains all constants and operators,
			true is returned
checks:     none */

int EvalTree(BTree& T);
/*precond:  a initialized tree
postcond:	Calls DoEvalTree for evaluation of terms
checks:     none */

int DoEvalTree(BTree& T);
/*precond:  a initialized tree
postcond:	Traverses the binary tree T in Inorder.
			It will then perform algebraic evaluation of leaf nodes
			refrencing operator at subroot node
checks:     none */

void ReduceTree(BTree &T);
void DoReduceTree(BTree &T);

int main()
{
	BTree T;
	ifstream infile;
	int treecounter = 0;
	int expcounter = 0;

	//read number of expressions
	welcome(infile, expcounter);

	//Do specified number of tress
	for (int x = 0; x < expcounter; x++)
	{
		//Build the tree 
		BuildTree(T, infile);

		if (AllConsts(T))
			EvalTree(T);
		else
			ReduceTree(T);

		//print it out in InOrder
		cout << "The inorder traversal of the tree " << endl;
		Inorder(T);
/*
		// print it out in PreOrder
		cout << "The Preorder traversal of the tree " << endl;
		Preorder(T);

		// print it out in PostOrder
		cout << "The postorder traversal of the tree " << endl;
		Postorder(T);

		// print Item Sum
		cout << "The Sum of Items in tree " << endl;
		cout << "The Sum is: ";
		SumTree(T, treecounter);
		cout << treecounter << endl;
*/
	}
		//close input file
		closeing(infile);

	system("pause");

	return 0;
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

		else if (dir == 'L') //means building left subtree so need
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
			//if i just read any of these im building left subtree
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

	cout << endl << endl;
}

//DEFINE ADDITIONAL NON-MEMBER FUNCTIONS HERE

void Preorder(BTree  & T)
{
	T.ShiftToRoot();

	if (T.IsEmpty())
		cout << "Tree is empty" << endl;
	else
	{
		cout << "Tree contains: " << endl;
		DoPreorder(T);
	}

	cout << endl << endl;
}

//called by PreOrder
void DoPreorder(BTree & T)
{
	ItemType Item;

	//2 base cases: empty tree or subtree is a leaf
	if (!T.IsEmpty())
	{
		//display root of subtree
		T.RetrieveItem(Item);
		cout << Item << "  ";

		//not a leaf, has a left child, traverse left subtree
		//of subtree in PreOrder
		if (T.HasLeftChild())
		{
			T.ShiftLeft();
			DoPreorder(T);
			T.ShiftUp();
		}

		//not a leaf, has a right child, traverse right subtree of
		//subtree in PreOrder
		if (T.HasRightChild())
		{
			T.ShiftRight();
			DoPreorder(T);
			T.ShiftUp();
		}
	}
}

void Postorder(BTree  & T)
{
	T.ShiftToRoot();

	if (T.IsEmpty())
		cout << "Tree is empty" << endl;
	else
	{
		cout << "Tree contains: " << endl;
		DoPostorder(T);
	}

	cout << endl << endl;
}

//called by Postorder
void DoPostorder(BTree  & T)
{
	ItemType Item;

	//2 base cases: empty tree or subtree is a leaf
	if (!T.IsEmpty())
	{
		//not a leaf, has a left child, traverse left subtree
		//of subtree in InOrder
		if (T.HasLeftChild())
		{
			T.ShiftLeft();
			DoPostorder(T);
			T.ShiftUp();
		}

		//not a leaf, has a right child, traverse right subtree
		//of subtree in InOrder
		if (T.HasRightChild())
		{
			T.ShiftRight();
			DoPostorder(T);
			T.ShiftUp();
		}

		//display root of subtree
		T.RetrieveItem(Item);
		cout << Item << "  ";
	}
}

void SumTree(BTree  & T, int & counter)
{
	T.ShiftToRoot();

	if (T.IsEmpty())
		cout << "Tree is empty" << endl;
	else
	{
		DoSumTree(T, counter);
	}
}

//called by SumTree
void DoSumTree(BTree  & T, int & acounter)
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
			DoSumTree(T, acounter);
			T.ShiftUp();
		}

		//display root of subtree
		T.RetrieveItem(Item);
		acounter += Item;

		//not a leaf, has a right child, traverse right subtree of subtree
		//in InOrder
		if (T.HasRightChild())
		{
			T.ShiftRight();
			DoSumTree(T, acounter);
			T.ShiftUp();
		}
	}
}

int ord(char item)
{
	int digit = int(item);
	return digit - 48;
}

void welcome(ifstream & infile, int& expcounter)
{
	char infilename[40];
	do
	{
		//open input file
		cout << "Please enter name of input file:  ";
		cin >> infilename;
		cout << endl;
		infile.open(infilename);

		if (!infile)
			cout << "Invalid path. Please reenter.\n\n";
	}
	//loop until valid infile
	while (!infile);

	cout << "This program will read in a determined amount of\n";
	cout << "expressions, reduce, and evaluate them.\n\n";
	infile >> expcounter;
	infile.get();
}

void closeing(ifstream & infile)
{
	cout << "\n\nTHANK YOU\n";
	//close infile
	infile.close();
}

bool AllConsts(BTree& T)
{
	bool flag = NULL;
	//start at root of tree
	T.ShiftToRoot();

	if (T.IsEmpty())
		return false;
	else
	{
		flag = (DoAllConsts(T, flag));
	}
	return flag;
}

//called by AllConsts
bool DoAllConsts(BTree& T, bool& flag)
{
	//will return true as default value
	ItemType Item;

	//2 base cases: empty tree or subtree is a leaf
	if (!T.IsEmpty())
	{
		//read contents of root of the subtree
		T.RetrieveItem(Item);
		//if item is not a number between 0 and 9
		if ((ord(Item) < 0) || (ord(Item) > 9)) 
		{
			//if its not an opperator return false
			if ((Item != '+') && (Item != '-') &&
				(Item != '*') && (Item != '/'))
			{
				flag = false;
				return flag;
			}
			//if valid char return true
			else
				flag = true;
		}

		//not a leaf, has a left child, traverse left subtree
		//of subtree in PreOrder
		if (T.HasLeftChild())
		{
			T.ShiftLeft();
			DoAllConsts(T, flag);
			T.ShiftUp();
		}

		//not a leaf, has a right child, traverse right subtree of
		//subtree in PreOrder
		if (T.HasRightChild())
		{
			T.ShiftRight();
			DoAllConsts(T, flag);
			T.ShiftUp();
		}
	}
	return flag;
}

int EvalTree(BTree& T)
{
	EquationType equation;

	//start at root of tree
	T.ShiftToRoot();

	equation.answer = DoEvalTree(T);

	cout << "ANSWER IS:" << equation.answer <<endl;
	return equation.answer;
}

int DoEvalTree(BTree& T)
{
	ItemType Item;
	EquationType equation;

	//if its a leaf node
	if (T.HasNoChildren())
	{
		T.RetrieveItem(Item);
		return ord(Item);
	}

	else
	{
			T.ShiftLeft();
			equation.term1 = DoEvalTree(T);
			//go to subroot
			T.ShiftUp();

			T.ShiftRight();
			equation.term2 = DoEvalTree(T);
			//go to subroot
			T.ShiftUp();		
	}

	T.RetrieveItem(Item);

	//if its an opperator return false
	if ((Item == '+') || (Item == '-') ||
		(Item == '*') || (Item == '/'))
	{
		equation.Opert = Item;

		//perform arithmatic and store answer
		switch (equation.Opert)
		{
		case '+':
			return equation.term1 + equation.term2;
			break;
		case '-':
			return equation.term1 - equation.term2;
			break;
		case '/':
			return equation.term1 / equation.term2;
			break;
		case '*':
			return equation.term1 * equation.term2;
			break;
		default:
			break;
		}
	}
}

void ReduceTree(BTree &T)
{
	T.ShiftToRoot();

	DoReduceTree(T);
}

void DoReduceTree(BTree &T)
{
	BTree P;
	ItemType Item;
	ReductionType expr;

	if (!T.IsEmpty())
	{
		//if opperator w/ left child
		if (T.HasLeftChild())
		{
			T.ShiftLeft();
			T.RetrieveItem(Item);
			if ((Item != '+') && (Item != '-') && (Item != '*')
				&& (Item != '/'))
			{
				expr.term1 = Item;
				expr.flag = true;
				T.ShiftUp();
			}

			else
			{
				expr.flag = false;
				DoReduceTree(T);
				T.ShiftUp();
			}
		}

		//if opperator w/ right child
		if (T.HasRightChild())
		{
			T.ShiftRight();
			T.RetrieveItem(Item);

			if ((Item != '+') && (Item != '-') && (Item != '*')
				&& (Item != '/'))
			{
				expr.term2 = Item;
				expr.flag = true;
				T.ShiftUp();
			}

			else
			{
				expr.flag = false;
				DoReduceTree(T);
				T.ShiftUp();
			}
		}

		T.RetrieveItem(Item);

		if ((Item == '+') || (Item == '-') || (Item == '*') || (Item == '/') && (expr.flag))
		{
			switch (Item)
			{
				//Simplify addition by 0
			case '+':
				if (expr.term1 != 0 && expr.term2 != 0)
				{
					if (expr.term1 == '0')
					{
						T.ChangeItem(expr.term2);
						T.RemoveLeft();
						T.RemoveRight();
					}

					else if (expr.term2 == '0')
					{
						T.ChangeItem(expr.term1);
						T.RemoveLeft();
						T.RemoveRight();
					}

				}

				break;
				//Simplify subtraction by 0
			case '-':
				if (expr.term1 == '0')
				{
					T.ChangeItem(expr.term2);
					T.RemoveLeft();
					T.RemoveRight();
				}
				else if (expr.term2 == '0')
				{
					T.ChangeItem(expr.term1);
					T.RemoveLeft();
					T.RemoveRight();
				}
				break;
				//Simplify multiplication by 0 and 1
			case'*':
				if ((expr.term1 == '0') || (expr.term2 == '0'))
				{
					T.ChangeItem('0');
					T.RemoveLeft();
					T.RemoveRight();
				}
				else if (expr.term1 == '1')
				{
					T.ChangeItem(expr.term2);
					T.RemoveLeft();
					T.RemoveRight();
				}
				else if (expr.term2 == '1')
				{
					T.ChangeItem(expr.term1);
					T.RemoveLeft();
					T.RemoveRight();
				}
				break;
				//Simplify division by 0 and 1
			case '/':
				if (expr.term2 == '0')
				{
					cout << endl << "Division by zero." << endl;
				}

				if (expr.term2 == '1')
				{
					T.ChangeItem(expr.term1);
					T.RemoveLeft();
					T.RemoveRight();
				}
			default:
				break;
			}
			T.ShiftUp();
		}
	}
}