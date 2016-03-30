//  Christian Norfleet
//  Binary Expression Tree
//  BTree.cpp
//  This file contains necessary files for Tree creation and traversal

#include "BTree.h"
using namespace std;

BTree::BTree()
{
	//set root and cursor
	root = NULL;
	cursor = NULL;
	parent = NULL;
}  //Constructor


void BTree::CopySubTree(TreeNode * parent, TreeNode *& p, TreeNode *& otherp)
{
	//if other subtree is empty, no subtree to copy
	if (otherp == NULL)
	{
		return;
	}
	else
	{
		//create new node at p and copy the item's value and 
		//set pointers to null
		p = new TreeNode;
		p->parent = parent;
		p->Item = otherp->Item;
		p->left = NULL;
		p->right = NULL;

		//copy the left subtree
		CopySubTree(parent, p->left, otherp->left);

		//copy the right subtree
		CopySubTree(parent, p->right, otherp->right);
	}
}


BTree::BTree(BTree & other)
{
	TreeNode * p;

	//set root and cursor to start
	root = NULL;
	cursor = NULL;

	//check if other tree is not empty
	if (other.root != NULL)
	{
		//create root node
		CreateFirstNode(other.root->Item);

		//start at roots
		p = root;
		other.cursor = other.root;

		//copy left and right subtrees
		CopySubTree(p, p->left, other.cursor->left);
		CopySubTree(p, p->right, other.cursor->right);
	}

}  //Copy Constructor


void BTree::CreateFirstNode(const ItemType & Item)
{
	//allocate first node (root)
	root = new TreeNode;

	//put value in it
	root->Item = Item;

	//initialize children pointers and parent pointer to NIL
	root->left = NULL;
	root->right = NULL;

	//set cursor to root
	cursor = root;
}


void BTree::DisposeSubTree(TreeNode *& p)
{
	//if subtree is empty, no subtree to dispose
	if (p != NULL)
	{
		DisposeSubTree(p->left);
		DisposeSubTree(p->right);
		delete p;
		p = NULL;
	}
}


BTree ::~BTree()
{
	//dispose of tree nodes
	DisposeSubTree(root);

	//make sure cursor is set to NULL as well
	cursor = NULL;
}


void BTree::ClearTree()
{
	cursor = root;

	//dispose of tree nodes
	DisposeSubTree(cursor);

	//make sure cursor is set to NULL as well
	root = NULL;
	cursor = root;

}


void  BTree::SwapTrees(BTree  & T2)
{
	TreeNode * tempRoot;
	TreeNode * tempCursor;
	int tempCount;

	//swap root pointers
	tempRoot = root;
	root = T2.root;
	T2.root = tempRoot;

	//swap cursor pointers
	tempCursor = cursor;
	cursor = T2.cursor;
	T2.cursor = tempCursor;
}


bool BTree::IsEmpty()
{
	return(root == NULL);
}


bool BTree::HasParent()
{
	return((cursor != NULL) && (cursor->parent != NULL) && (cursor != root));
}


bool BTree::HasNoChildren()
{
	return((cursor != NULL) && (cursor->left == NULL) && (cursor->right == NULL));
}


bool BTree::HasLeftChild()
{
	return((cursor != NULL) && (cursor->left != NULL));
}


bool BTree::HasRightChild()
{
	return ((cursor != NULL) && (cursor->right != NULL));
}


void BTree::ShiftToRoot()
{
	if (cursor == root)
		return;

	else if ((cursor == root) || (cursor->parent == NULL))
		cout << "ERROR:  T's cursor cannot advance to root" << endl;
	else
	{
		//move the actual cursor
		cursor = root;
	}
}


void BTree::ShiftLeft()
{
	if ((cursor == NULL) || (cursor->left == NULL))
		cout << "ERROR:  T's cursor cannot advance left" << endl;
	else
	{
		//move the actual cursor
		cursor = cursor->left;
	}
}


void BTree::ShiftRight()
{
	if ((cursor == NULL) || (cursor->right == NULL))
		cout << "ERROR:  T's cursor cannot advance right" << endl;
	else
	{
		//move the actual cursor
		cursor = cursor->right;
	}
}


void BTree::ShiftUp()
{
	if (cursor == root)
		return;

	else if ((cursor == NULL) || (cursor->parent == NULL))
		cout << "ERROR:  T's cursor cannot advance up" << endl;

	else
	{
		//move the actual cursor
		cursor = cursor->parent;
	}
}


void BTree::RetrieveItem(ItemType & Item)
{
	if ((cursor == NULL) || (root == NULL))
		cout << "ERROR:  T's cursor at end, cannot retireve item" << endl;
	else
		Item = cursor->Item;
}


void BTree::ChangeItem(const ItemType & Item)
{
	if (cursor == NULL)
		cout << "ERROR:  T's cursor at end, cannot update item" << endl;
	else
		cursor->Item = Item;
} //ChangeItem


void BTree::AddLeft(const ItemType & Item)
{
	//check if tree empty or left subtree not empty
	if (cursor == NULL)
		cout << "ERROR:  T's cursor at end, cannot add leaf" << endl;
	else if (cursor->left != NULL)
		cout << "ERROR:  Left subtree has a node, cannot add leaf" << endl;
	//add a left child
	else
	{
		//allocate a new node
		cursor->left = new TreeNode;

		//initialize the new node's item and pointer fields
		cursor->left->Item = Item;
		cursor->left->right = NULL;
		cursor->left->left = NULL;
		cursor->left->parent = cursor;
	}
}


void BTree::AddRight(const ItemType & Item)
{
	//check if tree empty or right subtree not empty
	if (cursor == NULL)
		cout << "ERROR:  T's cursor at end, cannot add leaf" << endl;
	else if (cursor->right != NULL)
		cout << "ERROR:  Right subtree has a node, cannot add leaf" << endl;
	//add a right child
	else
	{
		//allocate a new node
		cursor->right = new TreeNode;

		//initialize the new node's item and pointer fields
		cursor->right->Item = Item;
		cursor->right->left = NULL;
		cursor->right->right = NULL;
		cursor->right->parent = cursor;
	}
}


void BTree::RemoveLeft()
{
	//check if tree empty
	if (root == NULL)
	{
		return;
	}
	//check if left child
	if ((cursor->left->left != NULL) && (cursor->left->right != NULL))
	{
		return;
	}
	//else delete left child and set parent's left pointer
	else
	{
		delete cursor->left;
		cursor->left = NULL;
	}
}


void BTree::RemoveRight()
{
	//check if tree empty
	if (root == NULL)
	{
		return;
	}
	//check if left child
	if ((cursor->right->left != NULL) && (cursor->right->right != NULL))
	{
		return;
	}
	//else delete left child and set parent's left pointer
	else
	{
		delete cursor->right;
		cursor->right = NULL;
	}
}


void BTree::SwapSubTrees(BTree  & T)
{
	TreeNode * p;

	//if T not empty 
	if (T.cursor != NULL)
	{
		//if not at root, ChangeItem parent nodes' child pointers
		if (T.cursor->parent != NULL)
		{
			if (T.cursor->parent->left == T.cursor)
				T.cursor->parent->left = cursor;
			else
				T.cursor->parent->right = cursor;
		}
		else //at root
			T.root = cursor;
	}

	//if this not empty
	if (cursor != NULL)
	{
		if (cursor->parent != NULL)
		{
			if (cursor->parent->left == cursor)
				cursor->parent->left = T.cursor;
			else
				cursor->parent->right = T.cursor;
		}
		else
			root = T.cursor;
	}

	//reset parent pointers, if the swapped subtrees are not empty trees
	if (T.cursor != NULL)
	{
		if (cursor != NULL)
		{
			p = T.cursor->parent;
			T.cursor->parent = cursor->parent;
			cursor->parent = p;
		}
		else
			T.cursor->parent = NULL;
	}
	else if (cursor != NULL)
		cursor->parent = NULL;

	//swap two cursors
	p = T.cursor;
	T.cursor = cursor;
	cursor = p;

	//if we made the cursors point to an empty subtree because that was what
	//was swapped, set the cursors to the roots in their respective trees
	if (cursor == NULL)
		cursor = root;
	if (T.cursor == NULL)
		T.cursor = T.root;

	//if a root is NULL and cursor is not null, then root should be changed
	if (T.root == NULL)
		T.root = T.cursor;
	if (root == NULL)
		root = cursor;

} //SwapSubTrees

