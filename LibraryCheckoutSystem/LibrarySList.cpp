//Ricardo Carrillo
//Lab 4
#include "LibrarySList.h"
//---------------------------------------------------------------------------
// LibrarySList()
// creates the library skip list object
// Preconditions: libraryslist object does not exist
// Postconditions: librarylist object is created
// --------------------------------------------------------------------------
LibrarySList::LibrarySList()
{
	init();
}
//---------------------------------------------------------------------------
// ~LibrarySList()
// deletes the librarylist object
// Preconditions: librarylist object does not exist
// Postconditions: librarylist object is created
// --------------------------------------------------------------------------
LibrarySList::~LibrarySList()
{
	clear();                                      // delete items starting 1st
	for (int i = 0; i < NUM_LEVELS; i++)
	{
		delete header[i]->next;                      // delete the right most dummy
		delete header[i];                            // delete the left most dummy
	}
}
//---------------------------------------------------------------------------
// init()
// initialization helper for librarylist objects
// Preconditions: empty librarylist object
// Postconditions: librarylist object is created
// --------------------------------------------------------------------------
void LibrarySList::init()
{
	for (int i = 0; i < NUM_LEVELS; i++)
	{  // for each level
	   // create the left most dummy nodes;
		header[i] = new LibraryNode;
		header[i]->prev = NULL;
		header[i]->down = (i > 0) ? header[i - 1] : NULL;
		header[i]->up = NULL;
		if (i > 0)
			header[i - 1]->up = header[i];

		// create the right most dummy nodes
		header[i]->next = new LibraryNode;
		header[i]->next->next = NULL;
		header[i]->next->prev = header[i];
		header[i]->next->down = (i > 0) ? header[i - 1]->next : NULL;
		header[i]->next->up = NULL;
		if (i > 0)
			header[i - 1]->next->up = header[i]->next;
	}
}

//---------------------------------------------------------------------------
// clear()
// destructor helper for libraryslist objects
// Preconditions: full libraryslist object
// Postconditions: empty libraryslist object
// --------------------------------------------------------------------------
void LibrarySList::clear()
{
	for (int i = 0; i < NUM_LEVELS; i++)
	{        // for each level
		LibraryNode *p = header[i]->next;  // get the 1st c 
		while (p->next != NULL)
		{              // if this is not the left most
			LibraryNode *del = p;
			p = p->next;                           // get the next c
			delete del;                            // delete the current c
		}

		header[i]->next = p;                     // p now points to the left most 
	}                                          // let the right most point to it
}
//---------------------------------------------------------------------------
// insert()
// inserts book objects into the skip list
// 50% chance to increase the nodes height by 1
// Preconditions: NONE
// Postconditions: NONE
// --------------------------------------------------------------------------
void LibrarySList::insert(Book  *r) {
	// right points to the level-0 c before which a new object is inserted.
	static int counter = 1;
	LibraryNode *right = searchPointer(*r);
	LibraryNode *upper = NULL;
	LibraryNode *lower = NULL;
	if (right->next != NULL && right->c == r)
		// there is an identical object
		return;

	LibraryNode *newPtr = new LibraryNode;
	//insert node
	newPtr->up = NULL;
	newPtr->down = NULL;
	newPtr->c = r;
	newPtr->next = right;
	newPtr->prev = right->prev;
	right->prev = newPtr;
	newPtr->prev->next = newPtr;
	upper = newPtr;

	//flip coin to see if we need upper values
	int random = rand() % 2;
	int counter1 = 0;
	while (random == 1)
	{
		lower = upper;
		right = upper->prev;
		while (right->up == NULL) //find a node with an upper level
		{
			right = right->prev;
		}
		right = right->up;
		if (right->next != NULL)
			right = right->next;
		//insert node
		upper->up = new LibraryNode;
		upper = upper->up;
		upper->up = NULL;
		upper->c = r;
		upper->next = right;
		upper->prev = right->prev;
		right->prev = upper;
		upper->prev->next = upper; //test
		upper->down = lower;
		random = rand() % 2;
		//checks to see if the node is at the max level
		if (counter1 == 4)
		{
			random = 0;
			newPtr->up = NULL;
		}
		counter1++;
	}
}

//---------------------------------------------------------------------------
// searchPointer()
// return a pointer to the c whose value == obj or return
//  a pointer to the first c whose value > obj if we can't find  the exact
// Preconditions: NONE
// Postconditions: NONE
// --------------------------------------------------------------------------


LibraryNode *LibrarySList::searchPointer(Book  &r)
{
	LibraryNode *p = header[NUM_LEVELS - 1];     // start from the top left
	while (p->down != NULL)
	{                   // toward level 0
		p = p->down;                                // shift down once

		if (p->prev == NULL)
		{                    // at the left most c
			if (p->next->next == NULL)              // no intermediate items
				continue;
			else
			{                                    // some intermadiate items
				if (r >= *p->next->c)             // if 1st c <= obj
					p = p->next;                          // shift right to c 1
			}
		}
		while (p->next->next != NULL && r >= *p->next->c)
		{
			// shift right through intermediate items as far as the c value <= obj
			p = p->next;
		}
	}
	// now reached the bottom. shift right once if the current c < obj
	if (p->prev == NULL || r > *p->c)
	{
		p = p->next;
	}
	return p; // return the pointer to an c >= a given object.
}
//---------------------------------------------------------------------------
// searchFiction()
// returns true if the drama movie is found and adds the book to the 
// variable m
// assumptions- if the book doesnt have enough any stock, the system will say 
// that the book does not exist.
// Preconditions: NONE
// Postconditions: NONE
// --------------------------------------------------------------------------
bool LibrarySList::searchFiction(char mediaType, string author, string title, Fiction *&m)
{
	LibraryNode *p = header[0]->next; // at least the right most dummy
	for (; p->next != NULL; p = p->next)
	{
		if (p->c->inStock(mediaType))
		{
			if (p->c->getAuthor() == author &&
				p->c->getTitle() == title)
			{
				m = dynamic_cast<Fiction*>(p->c);
				return true;
			}
		}
	}
	cout << "Not found" << endl;
	return false;
}
//---------------------------------------------------------------------------
// searchPeriodical()
// returns true if the classic movie is found and adds the book to the 
// variable m
// assumptions- if the book doesnt have enough any stock, the system will say 
// that the book does not exist.
// Preconditions: NONE
// Postconditions: NONE
// --------------------------------------------------------------------------
bool LibrarySList::searchPeriodical(char mediaType, int releaseMonth, int releaseYear, Periodical *&m)
{
	LibraryNode *p = header[0]->next; // at least the right most dummy
	for (; p->next != NULL; p = p->next)
	{
		if (p->c->inStock(mediaType))
		{
			Periodical *tmp = dynamic_cast<Periodical*>(p->c);
			if (tmp->getReleaseMonth() == releaseMonth &&
				tmp->getReleaseYear() == releaseYear)
			{
				m = dynamic_cast<Periodical*>(p->c);
				return true;
			}
		}
	}
	cout << "Not found" << endl;
	return false;
}
//---------------------------------------------------------------------------
// searchChildren()
// returns true if the Childrens book is found and adds the movie to the 
// variable m
// assumptions- if the movie doesnt have enough any stock, the system will say 
// that the book does not exist.
// Preconditions: NONE
// Postconditions: NONE
// --------------------------------------------------------------------------
bool LibrarySList::searchChildren(char mediaType, string title, string author, Childrens *&m)
{
	LibraryNode *p = header[0]->next; // at least the right most dummy
	for (; p->next != NULL; p = p->next)
	{
		if (p->c->inStock(mediaType))
		{
			if (p->c->getAuthor() == author &&
				p->c->getTitle() == title)
			{
				m = dynamic_cast<Childrens*>(p->c);
				return true;
			}
		}
	}
	cout << "Not found" << endl;
	return false;
}


//---------------------------------------------------------------------------
// print()
// prints out the contents of the librarylist objects
// Preconditions: NONE
// Postconditions: NONE
// --------------------------------------------------------------------------
void LibrarySList::print(char type)
{
	if (type == 'Y')
	{
		cout << "-----------------------------------Childrens-----------------------------------" << endl <<
			"Type AVAIL Title		    Author			 Year  " << endl;
	}
	else if (type == 'F')
	{
		cout << "-----------------------------------Fiction-----------------------------------" << endl <<
			"Type AVAIL Author		    Title			 Year  " << endl;
	}
	else if (type == 'P')
	{
		cout << "-----------------------------------Periodicals-----------------------------------" << endl <<
			"Type AVAIL  YEAR		MO	    Title                  "  << endl;
	}
	else
		cout << "bad book type" << endl;

	LibraryNode *p = header[0]->next; // at least the right most dummy
	for (; p->next != NULL; p = p->next)
	{
		p->c->print();
	}

}