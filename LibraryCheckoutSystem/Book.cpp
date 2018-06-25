//Ricardo Carrillo
//Lab 4

#include "Book.h"
//---------------------------------------------------------------------------
// inStock()
// checks if the book has inventory, returns true if it does
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool Book::inStock(char bookType)
{
	switch (bookType)
	{
	case 'P':
		if (inventory[paperback] <= 0)
			return false;
		else
			return true;
	case 'H':
		if (inventory[hardcover] <= 0)
			return false;
		else
			return true;
	case 'A':
		if (inventory[audiobook] <= 0)
			return false;
		else
			return true;
	default:
		return false; //invalid mediatype
	}
	return false;
}
//---------------------------------------------------------------------------
// Book()
// Default constructor for book objects
// Preconditions: NONE
// Postconditions: book object created
// ---------------------------------------------------------------------------
Book::Book()
{
	this->inventory[hardcover] = 0;
	this->inventory[audiobook] = 0;
	this->inventory[paperback] = 0;
	this->bookType = ' ';
	this->title = "";
	this->author = "";
	this->releaseYear = 0;
}
//---------------------------------------------------------------------------
// Movie()
// constructor for movie objects
// Preconditions: NONE
// Postconditions: Movie object created
// ---------------------------------------------------------------------------
Book::Book(int hardStock, char bookType, string title, string author, int releaseYear)
{
	if (hardStock > 0)
		this->inventory[hardcover] = hardStock;
	else
		this->inventory[hardcover] = 0;
	this->inventory[audiobook] = 0;
	this->inventory[paperback] = 0;

	this->bookType = bookType;
	this->title = title;
	this->author = author;
	this->releaseYear = releaseYear;
}
//---------------------------------------------------------------------------
// ~Movie()
// Destructor for movie objects
// Preconditions: Movie object exists
// Postconditions: Movie object deleted
// ---------------------------------------------------------------------------
Book::~Book()
{
	this->inventory[hardcover] = 0;
	this->inventory[audiobook] = 0;
	this->inventory[paperback] = 0;
	this->bookType = ' ';
	this->title = "";
	this->author = "";
	this->releaseYear = 0;
	delete this;
}
//---------------------------------------------------------------------------
// borrow()
// checks if the movie has stock, and borrows (-1 inventory) the movie
// Preconditions: NONE
// Postconditions: NONE
// Note: More mediaTypes can easily be added here
// ---------------------------------------------------------------------------
bool Book::checkOut(char type)
{
	switch (type) {
	case 'P':
		if (inventory[paperback] > 0) {
			inventory[paperback] -= 1;
			return true;
		}
		else
			return false;
	case 'H':
		if (inventory[hardcover] > 0) {
			inventory[hardcover] -= 1;
			return true;
		}
		else
			return false;
	case 'A':
		if (inventory[audiobook] > 0) {
			inventory[audiobook] -= 1;
			return true;
		}
		else
			return false;
	default:
		cout << "Bad input or book out of stock.";
		return false; //bad input
	}
}
//---------------------------------------------------------------------------
// returnRental()
// checks if the movie has stock, and borrows (-1 inventory) the movie
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
void Book::returnRental(char type)
{
	switch (type)
	{
	case 'P':
		inventory[paperback] += 1;
	case 'H':
		inventory[hardcover] += 1;
	case 'A':
		inventory[audiobook] += 1;
	default:
		cout << "Bad input.";
	}
}
//---------------------------------------------------------------------------
// compareTypes()
// return negative if less than
// return 0 if equal
// return positive if greater than
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
int Book::compareTypes(const Book & m) const
{
	int lhs = BookTypes(this->bookType);
	int rhs = BookTypes(m.bookType);

	if (lhs > rhs)
		return 1;
	else if (lhs < rhs)
		return -1;
	else
		return 0;
}
//---------------------------------------------------------------------------
// getType()
// returns the type of the movie
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
char Book::getType()
{
	return this->bookType;
}
//---------------------------------------------------------------------------
// getDirector()
// returns the director of the movie
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
string Book::getAuthor()
{
	return this->author;
}
//---------------------------------------------------------------------------
// getTitle()
// returns the title of the movie
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
string Book::getTitle()
{
	return this->title;
}
//---------------------------------------------------------------------------
// getReleaseYear()
// returns the release year of the movie
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
int Book::getReleaseYear()
{
	return releaseYear;
}