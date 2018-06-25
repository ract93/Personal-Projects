#ifndef _RENTAL_SLIST
#define _RENTAL_SLIST

#include <iostream>
#include <cstdlib>
#include "Book.h"
#include "Periodical.h"
#include "Fiction.h"
#include "Childrens.h"

// ---------------------- LibrarySList.h ------------------------- 
// Ricardo Carrillo
// Lab 4
// ---------------------------------------------------------------- 
// Purpose: template skip list class that stores any type of 
//	rental object.
// ----------------------------------------------------------------
// Special Algorithms:
// - Insertions use a probability based approach to promoting
//	nodes to higher levels on the skip list.
// - Insertions and deletions must pay careful attention that all
//	links in the chain are appropriately established after an 
//	operation.
// ----------------------------------------------------------------
#define NUM_LEVELS 6
using namespace std;

//Structure used for nodes of skip list
struct LibraryNode
{
	Book  *c;
	LibraryNode *prev;
	LibraryNode *next;
	LibraryNode *up;
	LibraryNode *down;
};


class LibrarySList {

public:
	LibrarySList();	//default constructor
	~LibrarySList();	//destructor
					//inserts a rental object into list. Uses a 50%
					//probability to determine whether or not to promote
					//a rental object to a higher level linked list.
	void insert(Book  *r);
	//removes a rental object in the list

	//searches for a rental object within the list.

	//returns a formatted string of all rentals
	//within the list.



	void clear();
	//prints out the contents of the slist
	void print(char type);
	//searches through to find a specific type of book from the slist
	bool searchPeriodical(char mediaType, int releaseMonth, int releaseYear, Periodical *&m);
	bool searchFiction(char mediaType, string author, string title, Fiction *&m);
	bool searchChildren(char mediaType, string title, string author, Childrens *&m);
private:
	//skip list full of rental items w/ NUM_LEVELS
	LibraryNode *SList[NUM_LEVELS];
protected:
	LibraryNode *header[NUM_LEVELS]; // header
	void init();                     // called from the above two constructors
	LibraryNode *searchPointer(Book  &r); // used by find
};

#endif