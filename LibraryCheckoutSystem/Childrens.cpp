//Ricardo Carrillo
//Lab 4
#include "Childrens.h"
//---------------------------------------------------------------------------
// Childrens()
// creates a Childrens object
// Preconditions: NONE
// Postconditions: created childrens object
// ---------------------------------------------------------------------------
Childrens::Childrens(int stock, string title, string author, int releaseYear)

{
	this->inventory[hardcover] = stock;
	this->title = title;
	this->author = author;
	this->releaseYear = releaseYear;
	this->bookType = 'Y';

}
//---------------------------------------------------------------------------
// ~ComedyMovie()
// creates a childrens object
// Preconditions: full childrens object
// Postconditions: deleted childrens object
// ---------------------------------------------------------------------------
Childrens::~Childrens()
{
	delete this;
}
//---------------------------------------------------------------------------
// print()
// prints the contents of a childrens object
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
void Childrens::print()
{
	cout << "Y" << WHITE_SPACE << WHITE_SPACE << inventory[hardcover] << WHITE_SPACE
		<< title << COMMA_SPACE << author << COMMA_SPACE
		<< releaseYear << endl;
}
//---------------------------------------------------------------------------
// operator>()
// checks if a childrens object is greater than another comedymovie object
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool Childrens::operator>(const Book  &m) const
{
	const Childrens& c = static_cast<const Childrens&>(m);
	string temp = this->title;
	string temp2 = c.title;
	int compare = temp.compare(temp2);
	if (compare < 0)
		return false;
	//temp2 is smaller
	else if (compare > 0)
		return true;
	else
	{
		if (this->releaseYear <= c.releaseYear)
			return false;
		else
			return true;
	}
}
//---------------------------------------------------------------------------
// operator>=()
// checks if a childrens object is greater than or equal to another 
// comedymovie object
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool Childrens::operator>=(const Book  & m) const
{
	const Childrens& c = static_cast<const Childrens&>(m);
	string temp = this->title;
	string temp2 = c.title;
	int compare = temp.compare(temp2);
	if (compare < 0)
		return false;
	//temp2 is smaller
	else if (compare > 0)
		return true;
	else
	{
		if (this->releaseYear < c.releaseYear)
			return false;
		else
			return true;
	}
}
//---------------------------------------------------------------------------
// operator==()
// checks if a childrens object is equal to another comedymovie object
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool Childrens::operator==(const Book  &m) const
{
	const Childrens& c = static_cast<const Childrens&>(m);
	string temp = this->title;
	string temp2 = c.title;
	int compare = temp.compare(temp2);
	if (compare != 0)
		return false;
	//temp2 is smaller
	else
	{
		if (this->releaseYear != c.releaseYear)
			return false;
		else
			return true;
	}
}