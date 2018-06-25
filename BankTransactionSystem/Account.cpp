#include "Account.h"

using namespace std;
// Constructor
Account::Account(unsigned int id, string first, string last)
{
	pID = id;
	pNameFirst = first;
	pNameLast = last;

	//Instantiate Fund
	pFunds[0] = new Fund("Money Market");
	pFunds[1] = new Fund("Prime Money Market");
	pFunds[2] = new Fund("Long-Term Bond");
	pFunds[3] = new Fund("Short-Term Bond");
	pFunds[4] = new Fund("500 Index Fund");
	pFunds[5] = new Fund("Capital Value Fund");
	pFunds[6] = new Fund("Growth Equity Fund");
	pFunds[7] = new Fund("Growth Index Fund");
	pFunds[8] = new Fund("Value Fund");
	pFunds[9] = new Fund("Stock Index Fund");
	
}

Account::~Account()
{

}

//Add account cout overload

//Methods
bool Account::Deposit(int fund, unsigned int amount)
{
	string status = "D " + to_string(pID) + to_string(fund) + " +" + to_string(amount);

	if (DepositHelper(fund, amount))
	{
		// Success
		pFunds[fund]->AddHistory(status); //Update history
		return true;
	}
	
	else
	{
		// Fail
		pFunds[fund]->AddHistory(status + " (FAILED)");//Update history
		return false;
	}
}

bool Account::Withdraw(int fund, unsigned int amount)
{
	string status = "W " + to_string(pID) + to_string(fund) + " -" + to_string(amount);

	if (WithdrawHelper(fund, amount)) //This line failed
	{
		// Success
		pFunds[fund]->AddHistory(status); //Update history
		return true;
	}
	
	else
	{
		// Fail
		pFunds[fund]->AddHistory(status + " (FAILED)");//Update history
		return false;
	}
}

bool Account::SendTransfer(unsigned int fund, unsigned int amount, unsigned int destinationID)
{
	string status = "T " + to_string(pID) + to_string(fund) + " -" + to_string(amount);
	
	if (WithdrawHelper(fund, amount))
	{
		pFunds[fund]->AddHistory(status);// Print success
		return true;
	}
	
	else
	{
		pFunds[fund]->AddHistory(status + " (FAILED)");// Print fail
		return false;
	}
}

bool Account::RecieveTransfer(unsigned int fund, unsigned int amount, unsigned int sourceID)
{
	string status = "T " + to_string(pID) + to_string(fund) + " +" + to_string(amount);
	
	if (DepositHelper(fund, amount))
	{
		pFunds[fund]->AddHistory(status);// Print success
		return true;
	}
	else
	{
		pFunds[fund]->AddHistory(status + " (FAILED)");// Print fail
		return false;
	}
}

void Account::getHistory(unsigned int id, int fund) const
{
	vector<string> temp;

	if (fund == -1)
	{
		cout << "Transaction History for " + getName() + " By Fund." << endl;
		for (int i = 0; i < 10; i++)
		{
			temp = pFunds[i]->getRecord();
			
			cout << pFunds[i]->getName() + ": $"; 
			cout << pFunds[i]->getBalance() << endl;

			for (auto it = temp.begin(); it < temp.end(); it++)
			{
				cout << "  " + *it << endl;
			}
		}
	}
	else
	{
		cout << "Transaction History for " + getName();
		cout << pFunds[fund]->getName() << endl;
	}
}

string Account::getName() const
{
	return pNameLast + " " + pNameFirst;
}

unsigned int Account::getID() const
{
	return pID;
}

string Account::Print() const
{
	string outputL1 ="";
	string outputL2 ="";

	outputL1 = getName() + " Account ID: " + to_string(getID());
	
	for(int i = 0; i <= 9; i++)
	{
		outputL2 += "    "+pFunds[i]->getName() + ": $" + to_string(pFunds[i]->getBalance()) + "\n";
	}

	return outputL1 + "\n" + outputL2 + "\n";

}

// Private Members
//===================================================================================================================

bool Account::FundLogic(int fundType, int amount) //This method implements all logic requirments for the differing fund interactions. 
{
	int altFund;

	// Logic to control what fund to borrow from
	switch (fundType)
	{
	case 0:
		altFund = 1;
		break;
	case 1:
		altFund = 0;
		break;
	case 2:
		altFund = 3;
		break;
	case 3:
		altFund = 2;
		break;
	default:
		return false;
	}

	// Check the final balance
	int balance = pFunds[fundType]->getBalance() - amount;

	// If it is negative, try to borrow from the other fund
	if (balance < 0)
	{
		// Look at balance of other Fund, cancel withdrawl is a negative would be drawn
		if (pFunds[altFund]->getBalance() >= abs(balance))
		{
			// Alt fund will cover transaction
			// Deposit into the first fund
			if (pFunds[altFund]->InnerWithdraw(abs(balance)))
			{
				// If withdraw was successful
				pFunds[fundType]->InnerDeposit(abs(balance));
			}
			else
			{
				// Withdraw failed
				return false;
			}

			// Complete the withdraw
			return pFunds[fundType]->InnerWithdraw(amount);
		}
	}
	else
	{
		// Original fund will cover transaction. Withdraw normally.
		return pFunds[fundType]->InnerWithdraw(amount);
	}
	return true;
}

// Two helper function checks proper input for deposits
bool Account::DepositHelper(int fund, unsigned int amount)
{
	// Check to see if the fund number is valid
	if (fund >= 0 && fund <= 9)
	{
		// Deposit into this fund
		pFunds[fund]->InnerDeposit(amount);

		// Success
		return true;
	}
	else
	{
		// Failure
		return false;
	}
}

bool Account::WithdrawHelper(int fund, unsigned int amount) 
{
	// Account Type Validation
	if (fund < 0 || fund > 9)
	{
		cout << "Not an Account type" << endl;
		return false;
	}

	// Edge cases
	if (fund == 0) //Money Market
	{
		FundLogic(fund, amount);
	}
	
	else if (fund == 1) //Prime Money Market 
	{
		FundLogic(fund, amount);
	}
	
	else if (fund == 2)
	{
		FundLogic(fund, amount);
	}
	
	else if (fund == 3)
	{
		FundLogic(fund, amount);
	}

	// If not moeny markets or bonds and 
	else
	{
		if (pFunds[fund]->InnerWithdraw(amount))
		{
			return true;
		}
		
		else
		{
			return false;
		}
	}

	return true;
}

// Operator overloads
bool Account::operator==(const Account &other) const
{
	if (this->getID() == other.getID())
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

bool Account::operator<(const Account &other) const
{
	if (this->getID() < other.getID())
	{
		return true;
	}
	
	else
	{
		return false;
	}
}