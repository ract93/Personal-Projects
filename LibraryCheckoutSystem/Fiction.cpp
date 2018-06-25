//Ricardo Carrillo
//Lab 4
#include "Fiction.h"
//---------------------------------------------------------------------------
// Fiction()
// creates a Fiction object
// Preconditions: NONE
// Postconditions: created Fiction object
// ---------------------------------------------------------------------------
Fiction::Fiction(int stock, string title, string author, int releaseYear)

{
	this->inventory[hardcover] = stock;
	this->title = title;
	this->author = author;
	this->releaseYear = releaseYear;
	this->bookType = 'F';
}

//---------------------------------------------------------------------------
// ~Fiction()
// creates a Fiction object
// Preconditions: full Fiction object
// Postconditions: deleted Fiction object
// ---------------------------------------------------------------------------
Fiction::~Fiction()
{
	delete this;
}
//---------------------------------------------------------------------------
// operator>()
// checks if a Fiction object is greater than another Fiction object
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool Fiction::operator>(const Book  &m) const
{
	if (compareTypes(m) == 0)
	{

		const Fiction& d = static_cast<const Fiction&>(m);
		string temp = this->author;
		string temp2 = d.author;
		int compare = temp.compare(temp2);
		if (compare < 0)
			return false;
		//temp2 is smaller
		else if (compare > 0)
			return true;
		else if (compare == 0)
		{
			temp = this->title;
			temp2 = d.title;
			compare = temp.compare(temp2);
			if (compare <= 0)
				return false;
			//temp2 is smaller
			else
				return true;
		}
	}
	else if (compareTypes(m) > 0)
		return true;
	else
		return false;
	return false;
}
//---------------------------------------------------------------------------
// operator>=()
// checks if a fiction object is greater than or equal to another 
// fiction object
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool Fiction::operator>=(const Book  & m) const
{
	if (compareTypes(m) == 0)
	{

		const Fiction& d = static_cast<const Fiction&>(m);
		string temp = this->author;
		string temp2 = d.author;
		int compare = temp.compare(temp2);
		if (compare < 0)
			return false;
		//temp2 is smaller
		else if (compare > 0)
			return true;
		else if (compare == 0)
		{
			temp = this->title;
			temp2 = d.title;
			compare = temp.compare(temp2);
			if (compare < 0)
				return false;
			//temp2 is smaller
			else
				return true;
		}
	}
	else if (compareTypes(m) > 0)
		return true;
	else
		return false;
	return false;
}
//---------------------------------------------------------------------------
// operator==()
// checks if a fiction object is equal to another dramamovie object
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool Fiction::operator==(const Book  &m) const
{
	const Fiction& d = static_cast<const Fiction&>(m);
	if (compareTypes(m) == 0)
	{

		string temp = this->author;
		string temp2 = d.author;
		int compare = temp.compare(temp2);
		if (compare != 0)
			return false;
		//temp2 is smaller
		else
		{
			temp = this->title;
			temp2 = d.title;
			compare = temp.compare(temp2);
			if (compare != 0)
				return false;
			//temp2 is smaller
			else
				return true;
		}
	}
	else
		return false;
}
//---------------------------------------------------------------------------
// print()
// prints the contents of a fiction object
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
void Fiction::print()
{
	cout << "F" << WHITE_SPACE  WHITE_SPACE << inventory[hardcover] << WHITE_SPACE
		<< author << WHITE_SPACE << title << WHITE_SPACE
		<< releaseYear << endl;
}