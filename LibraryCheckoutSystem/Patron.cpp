//Ricardo Carrillo
//Lab 4
#include "Patron.h"
//---------------------------------------------------------------------------
// Patron()
// default constructor for patron objects
// Preconditions: NONE
// Postconditions: customer object created
// ---------------------------------------------------------------------------
Patron::Patron()
{
	patronID = 0;
	firstName = "";
	lastName = "";
}
//---------------------------------------------------------------------------
// Patron()
// constructor for patron objects
// Preconditions: NONE
// Postconditions: patron object created
// ---------------------------------------------------------------------------
Patron::Patron(int ID, string first, string last)
{
	this->patronID = ID;
	this->firstName = first;
	this->lastName = last;

}
//---------------------------------------------------------------------------
// ~Patron()
// destructor for patron objects
// Preconditions: patron object exists
// Postconditions: patron object deleted
// ---------------------------------------------------------------------------
Patron::~Patron()
{
	clear();
	delete this;
}
//---------------------------------------------------------------------------
// getID()
// returns the id number of a patron
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
int Patron::getID()
{
	return patronID;
}
//---------------------------------------------------------------------------
// getWholeName()
// returns the whole name of a patron
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
string Patron::getWholeName()
{
	string temp = "";
	temp.append(firstName);
	temp.append(", ");
	temp.append(lastName);
	return temp;
}
//---------------------------------------------------------------------------
// getFirstName()
// returns the first name of a patron
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
string Patron::getFirstName()
{
	return firstName;
}
//---------------------------------------------------------------------------
// getLastName()
// returns the last name of a patron
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
string Patron::getLastName()
{
	return lastName;
}
//---------------------------------------------------------------------------
// printHistory()
// prints the patron's history from the linked list
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
void Patron::printHistory()
{
	cout << "------------TRANSACTION HISTORY------------" << endl;
	cout << "Patron ID: " << this->patronID << endl;
	cout << "Patron name: " << this->lastName << ", " << this->firstName << endl;
	patHistory.printList();

}
//---------------------------------------------------------------------------
// printPatron()
// prints the customers id and name
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
void Patron::printPatron()
{
	cout << patronID << " " << getWholeName() << endl;
}
//---------------------------------------------------------------------------
// operator==()
// returns true if two customers are the same
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool Patron::operator==(const Patron & c) const
{

	if (this->patronID != c.patronID)
		return false;
	else
		return true;
}
//---------------------------------------------------------------------------
// addHistory()
// adds a string to the history of the customer
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
void Patron::addHistory(string item)
{
	patHistory.insertFront(item);
}
//---------------------------------------------------------------------------
// clear()
// destructor helper for customer objects
// Preconditions: customer object exists
// Postconditions: customer object emptied
// ---------------------------------------------------------------------------
void Patron::clear()
{
	this->patHistory.deleteList();
	this->patronID = 0;
	this->size = 0;
	this->firstName = "";
	this->lastName = "";
}