#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>
#include <iostream>
#include <queue>
#include "BSTree.h"
#include "Account.h"

using namespace std;

class Transactions
{
public:
	Transactions();
	~Transactions();

	bool Open(string nameFirst, string nameLast, unsigned int id);
	bool Deposit(unsigned int id, unsigned int fund, int amount);
	bool Withdraw(unsigned int id, unsigned int fund, int amount);
	bool Transfer(unsigned int sourceID, unsigned int destID, int amount,
		unsigned int sourceFund, unsigned int destFund);
	bool History(unsigned int id, unsigned int fund);
	bool ProcessQueue(queue<vector<string>> CommandQueue);



private:
	BSTree pAccounts;
};

#endif