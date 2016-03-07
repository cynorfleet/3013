#include <iostream>
#include "BSTree.h"
using namespace std;

BSTree::BSTree(){
	root = NULL;
	cursor = NULL;
}

void BSTree::Insert(int x){
	Node * p = NULL;
	if (root == NULL){
		root = new Node();
		root->data = x;
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		cursor = root;
	}
	else{
		__Insert(p, root, x);
	}
}

int BSTree::Height(){
	return __Height(root);
}

void BSTree::PrintTree(){
	__Print(root);
}

bool BSTree::findItem(int x) {
	bool found = false;
	Node * p;

	//set p to root
	p = root;

	while (!found && (p != NULL)) {
		if (p->data == x)
			found = true;
		else if (x < p->data)
			p = p->left;
		else  if (x > p->data)
			p = p->right;
	}

	//if found, make cursor point to it; might want to do something with it?
	if (found)
		cursor = p;

	return found;
}

void BSTree::deleteItem(int x){
	bool found = findItem(x);

	if (!found)
		cout << "ERROR: Cannot remove item, item is not in tree.\n";
	//item found and cursor is at the node that contains the item
	else {
		__deleteItem();
	}
}

void BSTree::__deleteItem() {
	Node * p;
	Node * q;

	//case 1:  interior node
	if ((cursor->left != NULL) && (cursor->right != NULL)){
		p = cursor;

		//move q to right most node in left subtree
		q = cursor;
		q = q->left;
		while (q->right != NULL)
			q = q->right;

		//copy value in q to the node p
		p->data = q->data;
		cursor = q;
		//delete q which could be a leaf or node that has left subtree
		__deleteItem();

		cursor = p->parent;
	}
	//case 2: has only left subtree
	else if (cursor->left != NULL) {
		p = cursor;
		cursor = p->parent;
		cursor->left = p->left;
		p->left->parent = cursor;
		delete p;
	}
	//case 3: has only right subtree
	else if (cursor->right != NULL) {
		p = cursor;
		cursor = p->parent;
		cursor->right = p->right;
		p->right->parent = cursor;
		delete p;
	}
	//case 4: cursor is at leaf, because both left and right are NULL
	else {
		p = cursor;
		cursor = p->parent;
		if (p->parent->left == p)
			p->parent->left = NULL;
		else
			p->parent->right = NULL;
		delete p;
	}

}


void BSTree::__Insert(Node *& parent, Node *&subroot, int data){
	if (subroot == NULL){
		subroot = new Node();
		subroot->data = data;
		subroot->left = NULL;
		subroot->right = NULL;
		subroot->parent = parent;
		cursor = suboot;
	}
	else{
		if (data < subroot->data){
			__Insert(subroot, subroot->left, data);
		}
		else{
			__Insert(subroot, subroot->right, data);
		}
	}
}

void BSTree::__Print(Node *subroot){
	if (subroot == NULL){
		return;
	}
	else{
		//cout << subroot->data << " ";	//Preorder
		__Print(subroot->left);
		cout << subroot->data << " "; //Inorder
		__Print(subroot->right);
		//cout << subroot->data << " "; //Postorder
	}
}

int BSTree::__Height(Node *subroot){
	if (subroot == NULL){
		return 0;
	}
	else{
		int ldepth = __Height(subroot->left);
		int rdepth = __Height(subroot->right);

		if (ldepth > rdepth){
			return 1 + ldepth;
		}
		else{
			return 1 + rdepth;
		}
	}
}


