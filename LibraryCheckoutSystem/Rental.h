// ---------------------- Rental.h ------------------------- 
//Ricardo Carrillo
// Lab 4
// ---------------------------------------------------------------- 
// Purpose: Abstract base class for items that must be tracked by
//	the overall program. All rental items have the basic properties
//	of this class.
// ----------------------------------------------------------------
// Special Algorithms:
// - Hashing functions. This class is derived from hashable class
// ----------------------------------------------------------------
// Assumptions: 
//	- Users will not need to search transaction history.
//	- Transaction history is displayed in chronological order.
// ----------------------------------------------------------------

#ifndef _MY_RENTAL
#define _MY_RENTAL

#include <iostream>
#include <string>

using namespace std;

class Rental
{
public:
	Rental() {};	//default constructor
	~Rental() {};	//destructor
					//subtracts one from inventory count of rental
	virtual bool checkOut(char type) = 0;
	//adds one to inventory count of rental
	virtual void returnRental(char type) = 0;
	//returns information about the rental as formatted output.
	virtual void printRental() = 0;
};

#endif