//Catherine Stringfellow and Christian Norfleet
//prog3a1.cpp
//This program will create a Tree from infile and 
//print structure of tree

#include <cstdio>
#include <iostream>
#include <fstream>

#include "btree.h"
using namespace std;

void DoPrintInOrder(BTree    & B);

void CreateExampleTree(BTree   & B);

int main()
{
	BTree B;
	BTree B2;
	int I;

	//Test AddLeft, AddRight, ShiftRight, ShiftUp, and ShiftToRoot
	cout << "Now create a simple tree B." << endl;  cout << endl;
	CreateExampleTree(B);

	//test HasParent
	if (!B.HasParent())
		cout << "Now cursor is at root node" << endl << endl;
	else
		cout << "Something wrong in HasParent or ShiftToRoot!" << endl;

	//print out the tree in inorder
	//this call tests HasNoChildren and RetrieveItem
	cout << "The tree B after CreateSampletree (inorder):  " << endl;
	B.ShiftToRoot();
	DoPrintInOrder(B);
	cout << endl;
	cout << "Hit enter to continue" << endl;
	cin.get();

	//test SwapTrees
	B.SwapTrees(B2);
	cout << "The tree B2 after swapping it with B - should be";
	cout << " same as above:  " << endl;
	B.ShiftToRoot();
	DoPrintInOrder(B2);
	cout << endl;
	cout << "Hit enter to continue" << endl;
	cin.get();
	B.SwapTrees(B2);

	//test RetrieveItem and change
	B.ShiftToRoot();
	B.ShiftLeft();
	B.ShiftRight();
	I = 5;
	B.ChangeItem(I);

	//print out the entire tree
	cout << "The Tree B after change:        " << endl;
	B.ShiftToRoot();
	DoPrintInOrder(B);
	cout << endl;
	cout << "Hit enter to continue" << endl;
	cin.get();

	//test HasLeftChild and RemoveLeft
	B.ShiftToRoot();
	while (B.HasLeftChild())
		B.ShiftLeft();
	B.ShiftUp();
	B.RemoveLeft();

	//output the entire tree
	cout << "The tree B after removing the leftmost node" << endl;
	B.ShiftToRoot();
	DoPrintInOrder(B);
	cout << endl;
	cout << "Hit enter to continue" << endl;
	cin.get();

	//test copy constructor
	cout << "The tree B3 after copying it from one just above: " << endl;
	BTree B3(B);
	B3.ShiftToRoot();
	DoPrintInOrder(B3);
	cout << endl;
	cout << "Hit enter to continue" << endl;
	cin.get();

	//now print out B2
	cout << "The tree B2 before swapping it with B's left subtree";
	cout << "- It should be empty:  " << endl;
	B2.ShiftToRoot();
	DoPrintInOrder(B2);
	cout << endl;
	cout << "Hit enter to continue" << endl;
	cin.get();

	//now print out B
	cout << "The tree B before SwapSubTrees:  " << endl;
	B.ShiftToRoot();
	DoPrintInOrder(B);
	cout << endl;
	cout << "Hit enter to continue" << endl;
	cin.get();

	//test SwapSubTrees
	B.ShiftToRoot();
	B.ShiftLeft();
	B2.SwapSubTrees(B);

	//now print out B2
	cout << "The tree B2 after swapping it with B's left subtree:  " << endl;
	B2.ShiftToRoot();
	DoPrintInOrder(B2);
	cout << endl;
	cout << "Hit enter to continue" << endl;
	cin.get();

	//now print out B
	cout << "The tree B after SwapSubTrees:  " << endl;
	B.ShiftToRoot();
	DoPrintInOrder(B);
	cout << endl;
	cout << "Hit enter to continue" << endl;
	cin.get();

	//now test destructors
	cout << "Dispose binary trees" << endl;

	system("pause");

	return 0;
}


void DoPrintInOrder(BTree   & B)
{
	int I;

	if (!B.IsEmpty())
	{
		//print left subtree
		if (B.HasLeftChild())
		{
			B.ShiftLeft();
			DoPrintInOrder(B);
			B.ShiftUp();
		}

		//write current node
		B.RetrieveItem(I);
		if (!B.HasNoChildren())
			cout << "Interior:   ";
		else
			cout << "Leaf:     ";
		cout << I << endl;

		//print right subtree
		if (B.HasRightChild())
		{
			B.ShiftRight();
			DoPrintInOrder(B);
			B.ShiftUp();
		}
	}
}


void CreateExampleTree(BTree   & B)
{

	int I;

	//make up a bunch of nodes}
	I = 9;
	B.CreateFirstNode(I);

	I = -5;
	B.AddRight(I);

	I = 2;
	B.AddLeft(I);
	B.ShiftLeft();

	I = -3;
	B.AddLeft(I);

	I = -9;
	B.AddRight(I);

	B.ShiftToRoot();
}