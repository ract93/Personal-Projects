#ifndef _CHILDRENS
#define _CHILDRENS

#include "Rental.h"
#include "Book.h"
// ---------------------- Childrens.h ------------------------- 
// Ricardo Carrillo
// Lab 4
// ---------------------------------------------------------------- 
// Purpose: Class for Childrens books. Inherits from class Book which
//	inherits from class Rental. This class supports all operations
//	expected of a Rental object.
// ----------------------------------------------------------------
// Special Algorithms:
// - Hashing functions.
// ----------------------------------------------------------------
using namespace std;
class Childrens : public Book
{
	friend ostream & operator<<(ostream& out, const Childrens& r);
public:
	Childrens(int stock, string title, string director, int releaseYear);

	~Childrens();
	//returns information about the comedy as formatted output.
	// this includes stock counts
	virtual void print();

	virtual bool operator>(const Book &m) const;
	virtual bool operator>=(const Book  &m) const;
	virtual bool operator==(const Book  &m) const;
};

#endif