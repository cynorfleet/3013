//Christian Norfleet
//Header file for BSTree.cpp

#include <iostream>
using namespace std;

struct Node{
	int data;
	Node *left;
	Node *right;
	Node *parent;
};

class BSTree{

public:
	BSTree();

	void Insert(int x);

	int Height();

	void PrintTree();

	bool findItem(int x);

	void deleteItem(int x);

private:
	Node *root;
	Node *cursor;

	void __Insert(Node *& parent, Node *&subroot, int data);
	int __Height(Node *subroot);
	void __Print(Node *subroot);
	void __deleteItem();

};