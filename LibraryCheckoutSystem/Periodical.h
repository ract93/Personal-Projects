#ifndef _PERIODICAL
#define _PERIODICAL

#include "Rental.h"
#include "Book.h"
// ---------------------- Periodical.h ------------------------- 
// Ricardo Carrillo
// Lab 4
// ---------------------------------------------------------------- 
// Purpose: Class for Periodicals. Inherits from class Book which
//	inherits from class Rental. This class supports all operations
//	expected of a Rental object.
// ----------------------------------------------------------------
// Special Algorithms:
// - Hashing functions.
// ----------------------------------------------------------------
class Periodical : public Book
{
public:
	Periodical(int stock, string title, string Author, int releaseMonth, int releaseYear);		//default constructor
	~Periodical();	//destructor
						//returns information about the classic as formatted output.
						// this includes stock counts
	virtual void print();
	virtual bool operator>(const Book  &m) const;
	virtual bool operator>=(const Book  &m) const;
	virtual bool operator==(const Book  &m) const;
	int getReleaseMonth();
protected:
	int releaseMonth;
};

#endif