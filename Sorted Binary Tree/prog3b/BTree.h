#pragma once

#include <cstdlib>
#include <iostream>
using namespace std;

//A binary tree is a tree of items, together with a cursor indicating
//or referencing an item in the tree.  Each item has at most two 
//children.  The cursor can reference any item in the tree

typedef int ItemType;

class BTree
{
	struct TreeNode
	{
		ItemType Item;
		TreeNode * left;
		TreeNode * right;
		TreeNode * parent;
	};

public:
	//operations
	BTree();
	//precond:  Tree has not been created
	//postcond: Tree is created and is the empty tree
	//checks:   none

	BTree(BTree  & other);
	//precond:  Tree has not been created
	//postcond: Tree is created and is a copy of the other tree,
	//			other = #other, except 
	//          cursor reset
	//checks:   none

	~BTree();
	//precond:  Tree is created
	//postcond: Tree is no longer created
	//checks:   none

	void CreateFirstNode(const ItemType & Item);
	//precond:   tree is empty
	//postcond:  tree now has one node (a root node) , containing Item
	//           this new root node is now the current node
	//checks:    tree is empty

	void ClearTree();
	//precond:  this tree is created
	//postcond: this tree is empty
	//checks:   none

	void SwapTrees(BTree  & T2);
	//precond:  this tree and and T2 created
	//postcond: this tree = #T2 and T2 = #this tree
	//checks:   none

	bool IsEmpty();
	//precond:  none
	//postcond:  returns true iff tree is empty and false otherwise

	bool HasParent();
	//precond:  Tree is created
	//postcond: HasParent = TRUE iff the tree is not empty and the cursor is
	//          pointing at a node that has a parent.  this tree = #tree
	//checks:   none

	bool HasNoChildren();
	//precond:  Tree is created
	//postcond: HasNoChildren = TRUE iff the tree is not empty and the cursor is
	//          pointing at an node that has no children. tree =#tree.
	//checks:   none

	bool HasLeftChild();
	//precond:  Tree is created
	//postcond: HasLeftChild = TRUE iff the tree is not empty and the cursor is
	//          pointing at an node that has a left child. tree=#tree.
	//checks:   none

	bool HasRightChild();
	//precond:  Tree is created
	//postcond: HasRightChild = TRUE iff the tree is not empty and the cursor is
	//          pointing at an node that has a right child. tree=#tree.
	//checks:   none

	void ShiftToRoot();
	//precond:  this tree is created and not empty
	//postcond: this tree's cursor is pointing to the root of T,
	//			this tree unchanged otw.
	//checks:   none

	void ShiftLeft();
	//precond:  this tree has been created and this tree's cursor not at leaf
	//postcond: this tree's cursor is advanced so that it references the 
	//          left child of the item that this tree's #cursor,
	//          this tree is unChanged otherwise.
	//checks:   this tree's cursor not at leaf

	void ShiftRight();
	//precond:  this tree has been created and this tree's cursor not at leaf
	//postcond: this tree's cursor is advanced so that it references the 
	//          right child of the item that this tree's #cursor,
	//          this tree is unChanged otherwise.
	//checks:   this tree's cursor not at end

	void ShiftUp();
	//precond:  this tree is created and this tree's cursor not at root
	//postcond: this tree's cursor is moved back so that it references the
	//          parent of the item that this tree's #cursor, 
	//          this tree is unChanged otw.
	//checks:   this tree's cursor not referencing root

	void RetrieveItem(ItemType & Item);
	//precond:  this tree is created and this tree's cursor is referencing a node
	//postcond: the value of the item that this tree's cursor references is
	//          returned as the value of Item, this tree = #tree.
	//checks:   this tree's cursor is referencing a node

	void ChangeItem(const ItemType & Item);
	//precond:  this tree is created and this tree's cursor is referencing a node
	//postcond: the value of the item that this tree's cursor references is
	//           ChangeItemd to the value of Item, this tree is unchanged otw.
	//checks:   this tree's cursor is referencing a node

	void AddLeft(const ItemType & Item);
	//precond:  this tree is created and the node this tree's cursor
	//			is referencing has no
	//          left child
	//postcond: the left child of the node that this #tree's cursor references
	//			now points to
	//          a new node with value of Item, this tree is unchanged otherwise.
	//checks:   the node this tree's cursor references to has no left child

	void AddRight(const ItemType & Item);
	//precond:  this tree is created and the node this tree's cursor
	//			is referencing has no
	//          right child
	//postcond: the right child of the node that this #tree's cursor
	//			references now points to
	//          a new node with value of Item, this tree is unchanged otherwise.
	//checks:   the node this tree's cursor references to has no right child

	void RemoveLeft();
	//precond:  this tree is created and it's cursor references a node with
	//			a left leaf
	//postcond: the left leaf item of the node that this tree's #cursor
	//			references is removed
	//           from the tree, and this tree is unchanged otherwise.
	//checks:   this tree's cursor references a node with a left leaf

	void RemoveRight();
	//precond:  this tree is created and it's cursor references a node
	//			with a right leaf
	//postcond: the right leaf item of the node that this tree's 
	//			#cursor references is 
	//          removed from the tree, and this tree is unchanged otherwise.
	//checks:   this tree's cursor references a node with a left right

	void SwapSubTrees(BTree  & T);
	//precond:  this tree and T are created and the subtrees that both cursors are
	//          referencing are not empty.
	//postcond: the subtree of this tree whose root is the item that this
	//			tree's cursor
	//          references is swapped with the subtree of this whose root
	//          is the item that this tree's cursor references, the cursors are
	//          not moved, this tree and this tree are unchanged otherwise.
	//checks:   none


private:

	void CopySubTree(TreeNode * parent, TreeNode * & p, TreeNode *& otherp);
	//precond:  p is a pointer into the tree, parent is p's parent
	//postcond: The subtree pointed at by p is copied
	//checks:   none

	void DisposeSubTree(TreeNode *& p);
	//precond:  p is a pointer into the tree
	//postcond: The subtree pointed at by p is disposed
	//checks:   none

	TreeNode *  root;
	TreeNode * cursor;
	TreeNode * parent;
};


