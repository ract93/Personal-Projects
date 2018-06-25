// Account.h

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <iostream>
#include "Fund.h"

using namespace std;

class Account
{
public:
	Account(unsigned int id, string first, string last);
	~Account();

	bool Deposit(int fund, unsigned int amount);
	bool Withdraw(int fund, unsigned int amount);
	bool SendTransfer(unsigned int fund, unsigned int amount, unsigned int destID);
	bool RecieveTransfer(unsigned int fund, unsigned int amount, unsigned int sourceID);
	void getHistory(unsigned int id, int fund) const;
	unsigned int getID() const;
	string getName() const;
	string Print() const;

	// Operator Overloads
	bool operator==(const Account &other) const;
	bool operator<(const Account &other) const;
	//Add account cout overload

private:
	unsigned int pID;
	string pNameFirst;
	string pNameLast;
	Fund *pFunds[10];
	vector <string> pHistory;

	bool FundLogic(int fund, int amount); //This is buggy
	bool DepositHelper(int fund, unsigned int amount);
	bool WithdrawHelper(int fund, unsigned int amount);
};

#endif