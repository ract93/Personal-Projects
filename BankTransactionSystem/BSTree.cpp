#include "BSTree.h"

BSTree::BSTree()
{
	//This creates the first node in the BSTree, dummy account is never used. 
	
	root = NULL;
}
BSTree::~BSTree() {}


//Returns true if account was succesfully inserted into the BSTree
bool BSTree::Insert(Account *account) 
{
	RecursiveInsert(root, account);
	return true;
}

//Technically, this is a way to return two expressions, the bool for success or fail, and linking the retrival by reference to a passed in account pointer. 
bool BSTree::Retrieve(const Account &target, Account *&retrieval) const 
{
	Account *temp = RecursiveSearch(root, target);

	if (temp == NULL)
	{
		return false;
	}
	
	else
	{
		retrieval = temp;
		return true;
	}
}

//TODO: Implement, span the tree while not empty, call the output overload for the account. 
void BSTree::Display()
{
	if (IsEmpty())
	{
		return;
	}

	else
	{
		RecursiveDisplay(root);
	}
}

void BSTree::Empty()
{
	if (IsEmpty()) 
	{
		return;
	}

	else
	{
		RecursiveEmpty(root);
	}


}

bool BSTree::IsEmpty()
{
	if (root == NULL)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

//Private
//===========================================================================================

//Helper functions
Account * BSTree::RecursiveSearch(Node *node, const Account &target) const //This returns an account within the tree
{
	if (node == NULL) return NULL;

	else if (target == *(node->pAccount))
	{
		return (node->pAccount);
	}

	else if (target < *(node->pAccount))
	{
		return RecursiveSearch(node->left, target);
	}

	else
	{
		return RecursiveSearch(node->right, target);
	}
}

void BSTree::RecursiveInsert(Node *&node, Account *target) //Inserts an account into the tree
{
	if (!node)
	{
		node = new Node();
		node->pAccount = target;
		return;
	}

	else if (*target < *node->pAccount)
	{
		RecursiveInsert(node->left, target);
	}
	
	else
	{
		RecursiveInsert(node->right, target);
	}
}

void BSTree::RecursiveDisplay(Node *&node)
{
	if (node == NULL)
	{
		return;
	}

	else
	{
		//In Order
		RecursiveDisplay(node->left);
		cout << node->pAccount->Print();
		RecursiveDisplay(node->right);
	}
}

void BSTree::RecursiveEmpty(Node *&node)
{
	if (node == NULL)
	{
		return;
	}

	else
	{
		//Post Order
		RecursiveEmpty(node->left);
		RecursiveEmpty(node->left);
		delete node->pAccount;
		delete node;

	}

}