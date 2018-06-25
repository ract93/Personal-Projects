// ---------------------- Book.h ------------------------- 
// Ricardo Carrillo
// Lab 4
// ---------------------------------------------------------------- 
// Purpose: Abstract base class different types of movies. Movies
//	are derived from rentals.
// ----------------------------------------------------------------
// Special Algorithms:
// - Hashing functions.
// ----------------------------------------------------------------
//Current num types refers to number of different media types.

#ifndef _BOOK
#define _BOOK

#define CURRENT_NUM_TYPES 3
#define PRIME_MOD 31
#define COMMA_SPACE ",   "
#define WHITE_SPACE "  "

using namespace std;
#include "Rental.h"
#include <iostream>

class Book : public Rental
{
protected:
	//FORWARD DECLARATION OF ENUMS
	//enum types for stock
	enum MediaTypes { paperback, hardcover, audiobook };
	//enum for categories
	enum BookTypes { F, D, C };//UPDATE TO BOOK CODES
public:
	//enum type to store all types of media.
	Book();
	Book(int stock, char bookType, string title, string author, int releaseYear);	//default constructor
	~Book();	//destructor
				//subtracts one from inventory count of rental
	bool checkOut(char type);
	//adds one to inventory count of rental
	void returnRental(char type);
	//returns information about the rental as formatted output.
	// this includes stock counts
	virtual void printRental() {};
	virtual bool operator>(const Book &m)const { return false; };
	virtual bool operator>=(const Book &m)const { return false; };
	//bool operator<(const Movie &m) const;
	virtual bool operator==(const Book &m) const { return false; };

	virtual void print() {};
	char getType();
	string getAuthor();
	string getTitle();
	int getReleaseYear();
	bool inStock(char bookType);
protected:
	//keeps track of stock for all media types
	int inventory[CURRENT_NUM_TYPES];
	//category of book
	char bookType;
	//title of the book
	string title;
	//director of the book
	string author;
	//Year book was released
	int releaseYear;


	int compareTypes(const Book &m) const;
};

#endif // !_BOOK