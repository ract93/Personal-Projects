#include "Patron.h"
#include "PatronHashTable.h"
#include "Periodical.h"
#include "Childrens.h"
#include "Fiction.h"
#include "Book.h"
#include "LibrarySList.h"
#include <fstream>
#include <sstream>


// ---------------------- Library.h ------------------------- 
// Ricardo Carrillo
// Lab 4
// ---------------------------------------------------------------- 
// Purpose: This class is an abstract data type for a library.
//	Its responsiblity for managing inventory and patron information.
// ----------------------------------------------------------------
// Special Algorithms:
// - Skip list is used for inserting different rentals into a sorted 
//	linked list.
// ----------------------------------------------------------------
// Assumptions:
// - If a user of this program wishes to extend its design for new
//	kinds of rentals, they will have to create a new hashtable
//	and a new skip list for the new rental.
// - Invalid inputs are not parsed. The user is notified of
//	invalid inputs when they occur.
// - A skip list is used to store different types of rentals in
//	sorted order (skip list offers quicker access
//	for insertions and deletions). 
// ----------------------------------------------------------------
using namespace std;
class Library {
public:
	//Default constructor.
	Library();
	//Default destructor.
	~Library();
	////Initializes all rentals from a formatted text file
	void initRentals(ifstream& input);
	////Initializes all customers from a formatted text file
	void initPatrons(ifstream& input);
	void initCommands(ifstream& input);


private:
	int numPatrons;
	////open address hash table for patron objects.

	////open address hash table for rental type objects.
	PatronHashTable patrons;
	////Skip list of Periodicals. Used to print periodicals in sorted order.
	LibrarySList PeriodicalsList;
	//////Skip list of Fiction. Used to print Fictions in sorted order.
	LibrarySList FictionList;
	//////Skip list of Childrens books. Used to print Childrens in sorted order.
	LibrarySList ChildrensList;
};