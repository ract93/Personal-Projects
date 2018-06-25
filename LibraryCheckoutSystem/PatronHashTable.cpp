//Ricardo Carrillo
//Lab4
#include "PatronHashTable.h"
//---------------------------------------------------------------------------
// PatronHashTable()
// default constructor for PatronHashTable objects
// Preconditions: NONE
// Postconditions: PatronHashTable object created
// ---------------------------------------------------------------------------
PatronHashTable::PatronHashTable()
{
	this->size = 0;
	this->tableSize = MAX_TABLE_SIZE;

	for (int i = 0; i < MAX_TABLE_SIZE; i++)
	{
		bucketEmpty[i] = true;
		table[i] = NULL;
	}
}
//---------------------------------------------------------------------------
// ~PatronHashTable()
// destructor for PatronHashTable objects
// Preconditions: PatronHashTable object exists
// Postconditions: PatronHashTable object deleted
// ---------------------------------------------------------------------------
PatronHashTable::~PatronHashTable()
{
	for (int i = 0; i < tableSize; i++)
	{
		if (table[i] != NULL)
		{
			delete table[i];
			table[i] = NULL;
		}
	}
	delete *table;
}
//---------------------------------------------------------------------------
// insert()
// inserts a Patron object into the PatronHashTable object
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool PatronHashTable::insert(Patron *c)
{
	int key = hashPatron(c->getID());
	int i = 1;
	while (table[key] != NULL)
	{
		key = (key + (i * i) % tableSize);
		i++;
	}
	table[key] = c;
	bucketEmpty[key] = false;
	this->size += 1;
	return true;
}
//---------------------------------------------------------------------------
// remove()
// marks the item as deleted in the bool array
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool PatronHashTable::remove(int customerID)
{
	int key = hashPatron(customerID);
	int i = 1;
	while (table[key] != NULL)
	{
		if (table[key]->getID() == customerID)
		{
			bucketEmpty[key] = true;
			return true;
		}
		else
		{
			key = (key + (i * i) % tableSize);
			i++;
		}
	}
	return false;
}

//---------------------------------------------------------------------------
// getLoad()
// gets the current loadfactor of the hash table
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
double PatronHashTable::getLoad()
{
	loadFactor = this->size / this->tableSize;
	return loadFactor;
}
//get method that retrieves the size of the current hashtable.
//---------------------------------------------------------------------------
// getTableSize()
// returns the size of the hash table
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
int PatronHashTable::getTableSize()
{
	return tableSize;
}
//---------------------------------------------------------------------------
// searchCustomer()
// returns true if the patron of the corresponding ID exists
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
bool PatronHashTable::searchPatron(int customerID, Patron *&c)
{
	int key = hashPatron(customerID);
	int i = 1;
	while (table[key] != NULL)
	{
		if (table[key]->getID() == customerID)
		{
			c = table[key];
			return true;
		}
		else
		{
			key = (key + (i * i) % tableSize);
			i++;
		}
	}
	return false;
}
//---------------------------------------------------------------------------
// hashPatron()
// returns the key of the customer object given the customer ID
// Preconditions: NONE
// Postconditions: NONE
// ---------------------------------------------------------------------------
int PatronHashTable::hashPatron(int customerID)
{
	int tmp = customerID * 13 % tableSize;
	return tmp;
}