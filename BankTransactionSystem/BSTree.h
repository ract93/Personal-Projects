#ifndef BSTREE_H
#define BSTREE_H

#include "Account.h"

struct Node
{
	Account *pAccount;
	Node *left;
	Node *right;

	Node()
	{
		pAccount = NULL;
		left = NULL;
		right = NULL;

	}
};

class BSTree
{
public:
	BSTree::BSTree();
	BSTree::~BSTree();

	bool Insert(Account *accountToInsert);
	bool Retrieve(const Account &target, Account *&retrieval) const;

	void Display();
	void Empty();
	bool IsEmpty();

private:
	Node *root = NULL;
	Account * RecursiveSearch(Node *root, const Account &target) const;
	void BSTree::RecursiveInsert(Node *&root, Account *target);
	void BSTree::RecursiveDisplay(Node *&node);
	void BSTree::RecursiveEmpty(Node *&node);
};

#endif