#ifndef _MY_CUSTOMER
#define _MY_CUSTOMER

#include <iostream>
#include <string>
#include <vector>
#include "PatronHistoryList.h"
// ---------------------- Patron.h ------------------------- 
// Ricardo Carrillo
// Lab 4
// ---------------------------------------------------------------- 
// Purpose: Abstract class for patrons. Stores a patrons's data
//	and their history of transactions.
// ----------------------------------------------------------------
// Special Algorithms:
// - Hashing functions. This class is derived from hashable class
// ----------------------------------------------------------------
// Assumptions: 
//	- Users will not need to search transaction history.
//	- Transaction history is displayed in chronological order.
//	- Patron class won't require extension.
// ----------------------------------------------------------------
using namespace std;
class Patron {
public:
	//default constructor
	Patron();
	Patron(int ID, string first, string last);
	//default destructor
	~Patron();
	//get patrons's unique id number
	int getID();
	//Ways to retrieve customer name
	string getWholeName();
	string getFirstName();
	string getLastName();
	//prints all transactions of a patron
	void printHistory();
	void printPatron();
	void addHistory(string item);
	bool operator==(const Patron &c) const;
	void clear();
private:
	int patronID;		//patron unique id
	int size;			//size of vector
						
	string firstName;
	string lastName;
	PatronHistoryList patHistory;
};

#endif