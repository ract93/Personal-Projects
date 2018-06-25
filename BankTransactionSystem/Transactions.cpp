#include <sstream>
#include "Transactions.h"

// TODO: Implement constructors in order to recieve incoming queue from Bank class. 

//Constructors
Transactions::Transactions() {}

Transactions::~Transactions() {}


//Transaction methods
//=============================================================================================
bool Transactions::Open(string nameFirst, string nameLast, unsigned int id) //Change to int to handle negative account numbers
{
	Account *newAccount = new Account(id, nameFirst, nameLast); //Instantiate account

	// Traverse tree to check if account already exists
	if (pAccounts.Retrieve(*newAccount, newAccount))
	{
		// If retrieve returns true, the account exists
		// PRINT ERROR
		cout << "ERROR: Account " << id << " is already open. Transaction refused." << endl;
		delete newAccount;
		return false;
	}

	//TODO
	//Add more fail cases here
	else
	{
		// Account does not exist. Adding new account.
		pAccounts.Insert(newAccount);
		
		//
		return true;
	}
}



bool Transactions::Deposit(unsigned int id, unsigned int fund, int amount) //Add cout
{
	// Dummy is starting point point for tree transversal, not actually used.
	Account *dummy = new Account(id, "dummy", "account");

	// Create a temp pointer to hold found object
	Account *temp;

	// Check to see if the account exists
	if (pAccounts.Retrieve(*dummy, temp))
	{
		temp->Deposit(fund, amount);
		delete dummy;
		return true;
	}
	
	else
	{
		// Account not found
		// Print Message to console
		cout << "ERROR: Account " << id << " does not exist. Transaction refused." << endl;
		delete dummy;
		return false;
	}

	delete dummy;
}

bool Transactions::Withdraw(unsigned int id, unsigned int fund, int amount)
{
	// Dummy is starting point point for tree transversal, not actually used.
	Account *dummy = new Account(id, "dummy", "account");

	// Create a temp pointer to hold found object
	Account *temp;

	// Check to see if the account exists
	if (pAccounts.Retrieve(*dummy, temp))
	{
		temp->Withdraw(fund, amount);
		delete dummy;
		return true;
	}
	
	else
	{
		// Account not found
		// Print Message to console
		cout << "ERROR: Account " << id << " does not exist. Transaction refused." << endl;
		delete dummy;
		return false;
	}

	delete dummy;

}


bool Transactions::Transfer(unsigned int sourceID, unsigned int sourceFund, int amount, //Add cout
	unsigned int destID, unsigned int destFund) //Add cout
{
	// Dummy is starting point point for tree transversal, not actually used.
	Account *dummy1 = new Account(sourceID, "dummy", "account");

	// Dummy is starting point point for tree transversal, not actually used.
	Account *dummy2 = new Account(destID, "dummy", "account");

	// Create temp pointer to which we will assign the retrievals
	Account *source;
	Account *dest;

	// Check to see if both accounts exist
	if (!pAccounts.Retrieve(*dummy1, source))
	{
		// Throw Error if retrieval returned false
		cout << "ERROR: Account " << sourceID << " does not exist. Transaction refused." << endl;
		delete dummy1;
		delete dummy2;
		return false;
	}
	
	if (!pAccounts.Retrieve(*dummy2, dest))
	{
		// Throw Error if retrieval returned false
		cout << "ERROR: Account " << destID << " does not exist. Transaction refused." << endl;
		delete dummy1;
		delete dummy2;
		return false;
	}

	// Check for funds in source account
	if (source->SendTransfer(sourceFund, amount, destID))
	{
		// Success
		dest->RecieveTransfer(destFund, amount, sourceID);
		delete dummy1;
		delete dummy2;
		return true;
	}
	
	else
	{
		// Failed. Trade cancelled recieved 0. 
		dest->RecieveTransfer(destFund, 0, sourceID);
		delete dummy1;
		delete dummy2;
		return false;
	}
}

bool Transactions::History(unsigned int id, unsigned int fund)
{
	// Dummy is starting point point for tree transversal, not actually used.
	Account *dummy = new Account(id, "dummy", "account");

	// Create temp pointer to which we will assign the retrieval
	Account *temp;

	// Check to see if the account exists
	if (pAccounts.Retrieve(*dummy, temp))
	{
		temp->getHistory(id, fund);
		cout << endl;
		return true;
	}
	
	else
	{
		// Account not found
		cout << "ERROR: Account " << id << " does not exist. Transaction refused." << endl;
		delete dummy;
		return false;
	}

	delete dummy;
	return true;
}

//The main workhourse function of the program, processes the queue of commands. 
//Interprets the command strings and calls the required methods for each transaction. 
bool Transactions::ProcessQueue(queue<vector<string>> CommandQueue) 
{
	vector<string> commands;

	while (!CommandQueue.empty())//While commands are still available
	{
		// Get next command
		commands = CommandQueue.front();

		//Read the command
		if (commands[0] == "O") //Open
		{
			Open(commands[2], commands[1], stoi(commands[3]));
		}
		
		else if (commands[0] == "D") //Deposit
		{
			Deposit(stoi(commands[1]), stoi(commands[2]), stoi(commands[3]));
		}
		
		else if (commands[0] == "W") //Withdraw
		{
			Withdraw(stoi(commands[1]), stoi(commands[2]), stoi(commands[3]));
		}
		
		else if (commands[0] == "T") //Trade
		{
			Transfer(stoi(commands[1]), stoi(commands[2]), stoi(commands[3]),
				stoi(commands[4]), stoi(commands[5]));
		}
		
		else if (commands[0] == "H") //History
		{
			if (commands[1].length() == 5)
			{
				History(stoi(commands[1]), stoi(commands[2]));
			}
			
			else
			{
				History(stoi(commands[1]), -1);
			}
		}

		CommandQueue.pop();
	}

	cout << endl;
	cout << endl;
	cout << "Transactions complete. Printing results:" << endl;
	cout << endl;
	pAccounts.Display();

	return true;
}




