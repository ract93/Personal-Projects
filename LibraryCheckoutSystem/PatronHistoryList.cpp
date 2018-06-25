//Ricardo Carrillo
//Lab 4
#include "PatronHistoryList.h"
//---------------------------------------------------------------------------
// PatronHistoryList()
// creates a patronhistorylist object
// Preconditions: NONE
// Postconditions: created patronhistorylist object
// ---------------------------------------------------------------------------
PatronHistoryList::PatronHistoryList()
{
	this->head = NULL;
	this->tail = NULL;
}
//---------------------------------------------------------------------------
// ~PatronHistoryList()
// deletes a patronhistorylist object
// Preconditions: full patronhistorylist object
// Postconditions: deleted patronhistorylist object
// ---------------------------------------------------------------------------
PatronHistoryList::~PatronHistoryList()
{
	this->deleteList();

}
//---------------------------------------------------------------------------
// insertFront()
// inserts a string object into the front of the linked list
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
void PatronHistoryList::insertFront(string book)
{
	HistoryNode *h = new HistoryNode(book);

	if (head != NULL)
		head->prev = h;

	h->next = head;
	h->prev = NULL;

	head = h;
}
//---------------------------------------------------------------------------
// insertBack()
// inserts a string object into the back of the linked list
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
void PatronHistoryList::insertBack(string book)
{
	HistoryNode *h = new HistoryNode(book);

	if (tail != NULL)
		tail->next = h;

	h->prev = tail;
	h->next = NULL;
	tail = h;
}
//---------------------------------------------------------------------------
// printList()
// prints out the contents of the patronhistorylist
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
void PatronHistoryList::printList()
{
	HistoryNode *srch = head;

	if (srch == NULL)
		return;
	else
		cout << srch->book << endl;

	while (head->next != NULL)
	{
		head = head->next;
		cout << head->book << endl;
	}
}
//---------------------------------------------------------------------------
// deleteList()
// destructor helper for patronhistorylist objects
// Preconditions: full list
// Postconditions: empty and deleted list
// ---------------------------------------------------------------------------
void PatronHistoryList::deleteList()
{
	if (head == NULL)
		return;
	else
	{
		while (head->next != NULL)
		{
			head = head->next;
			delete head->prev;
		}
		delete head;
	}
}