#include "Fund.h"

//TODO Change signitures

//Constructor
Fund::Fund(string name)
{
	pBalance = 0;
	pName = name;

}

//Constructor
Fund::~Fund()
{
	
}

//Getters
int Fund::getBalance() const
{
	return pBalance;
}


string Fund::getName() const
{
	return pName;
}

vector<string> Fund::getRecord()
{
	return pHistory;
}

//These are the actual setters for the funds
bool Fund::InnerDeposit(unsigned int amount)
{
	pBalance += (int)amount;
	return true;
}


bool Fund::InnerWithdraw(unsigned int amount)
{
	if (amount > pBalance)
	{
		return false;
	}
	else
	{
		pBalance -= amount;
		return true;
	}
}

bool Fund::AddHistory(string record)
{
	pHistory.push_back(record);
	return true;
}



