#include <iostream>
#include "BSTree.h"
using namespace std;

void main(){
	BSTree MyTree;

	for (int i = 0; i < 16; i++){
		int num = rand() % 1000;
		cout << num << " ";
		MyTree.Insert(num);
	}
	cout << endl << endl;

	MyTree.PrintTree();

	cout << "\n\nHeight of binary search tree is " << MyTree.Height() << "\n\n";

	if (MyTree.findItem(467))
		cout << "467 is in the tree.\n\n";
	else
		cout << "467 is not in the tree\n\n";

	//delete a leaf
	//MyTree.deleteItem(281);
	//MyTree.PrintTree();
	//cout << endl << endl;

	//delete a node with only right subtree
	//MyTree.deleteItem(358);
	//MyTree.PrintTree();
	//cout << endl << endl;

	//delete a node with only left subtree
	//MyTree.deleteItem(169);
	//MyTree.PrintTree();
	//cout << endl << endl;

	MyTree.deleteItem(334);
    MyTree.PrintTree();
	cout << endl << endl;

	system("pause");

}
