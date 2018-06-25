//Ricardo Carrillo
//Lab 4
#include "Periodical.h"
//---------------------------------------------------------------------------
// Periodical()
// creates a Periodical object
// Preconditions: NONE
// Postconditions: created Periodical object
// ---------------------------------------------------------------------------
Periodical::Periodical(int stock, string title, string author, int releaseMonth, int releaseYear)

{
	this->releaseMonth = releaseMonth;
	this->inventory[hardcover] = stock;
	this->title = title;
	this->author = author;
	this->releaseYear = releaseYear;
	this->bookType = 'P';
}


//---------------------------------------------------------------------------
// ~Periodical()
// creates a Periodical object
// Preconditions: full Periodical object
// Postconditions: deleted Periodical object
// ---------------------------------------------------------------------------
Periodical::~Periodical()
{
	delete this;
}
//---------------------------------------------------------------------------
// print()
// prints the contents of a Periodical object
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
void Periodical::print()// Modify
{
	cout << "P" << WHITE_SPACE << WHITE_SPACE << inventory[hardcover] << WHITE_SPACE
		<< author << WHITE_SPACE << title << COMMA_SPACE
		<< releaseMonth << WHITE_SPACE << releaseYear << endl;
}
//---------------------------------------------------------------------------
// operator>()
// checks if a Periodical object is greater than another classicmovie object
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool Periodical::operator>(const Book &m)const
{
	//casts a movie object into a Periodical
	const Periodical& c = static_cast<const Periodical&>(m);

	if (this->releaseYear < c.releaseYear)
		return false;

	
	else if (this->releaseYear > c.releaseYear)
		return true;
	
	//Years are the same
	else
	{
		if (this->releaseMonth < c.releaseMonth)
			return false;
		//temp2 is smaller
		else if (this->releaseMonth > c.releaseMonth)
			return true;

		else// Months are the same
			return true;
	}
}
//---------------------------------------------------------------------------
// operator>=()
// checks if a Periodical object is greater than or equal to another 
// classicmovie object
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool Periodical::operator>=(const Book & m) const
{
	//casts the book object into a Periodical
	const Periodical& c = static_cast<const Periodical&>(m);
	if (this->releaseYear < c.releaseYear)
		return false;

	//temp2 is smaller
	else if (this->releaseYear > c.releaseYear)
		return true;

	else if (this->releaseMonth < c.releaseMonth)
		return false;
	//temp2 is smaller
	else if (this->releaseMonth > c.releaseMonth)
		return true;

	else
		return true; // Equal
}
//---------------------------------------------------------------------------
// operator==()
// checks if a Periodical object is equal to another Periodical object
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool Periodical::operator==(const Book &m)const
{
	//casts the book object to a Periodical
	const Periodical& c = static_cast<const Periodical&>(m);
	string temp = this->title;
	string temp2 = c.title;
	int compare = temp.compare(temp2);
	if (compare != 0)
		return false;

	else if (this->releaseMonth != c.releaseMonth)
		return false;
	else if (this->releaseYear != c.releaseYear)
		return false;
	else
		return true;
}
//---------------------------------------------------------------------------
// getReleaseMonth()
// returns the releaseMonth
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
int Periodical::getReleaseMonth()
{
	return releaseMonth;
}
