#ifndef _FICTION
#define _FICTION

#include "Rental.h"
#include "Book.h"
// ---------------------- Fiction.h ------------------------- 
// Ricardo Carrillo
// Lab 4
// ---------------------------------------------------------------- 
// Purpose: Class for Fiction books. Inherits from class Book which
//	inherits from class Rental. This class supports all operations
//	expected of a Rental object.
// ----------------------------------------------------------------
// Special Algorithms:
// - Hashing functions.
// ----------------------------------------------------------------
using namespace std;
class Fiction : public Book
{
public:
	Fiction(int stock, string title, string director, int releaseYear);

	~Fiction();
	//returns information about the comedy as formatted output.
	// this includes stock counts
	virtual void print();

	virtual bool operator>(const Book &m) const;
	virtual bool operator>=(const Book &m) const;
	virtual bool operator==(const Book &m) const;
private:
	//keeps track of stock for all media types

	//author and release date
};

#endif
