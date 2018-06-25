#ifndef BANK_H
#define BANK_H

#include <string>
#include <iostream>
#include <queue>
#include "BSTree.h"
#include "Account.h"
#include "Transactions.h"

using namespace std;

class Bank
{

public:
	Bank();
	~Bank();

	bool AddToQueue(vector<string> command);
	void ParseFile(string path);
	bool SendToTransactor();



private:
	Transactions transactor;
	queue<vector<string>> commandQueue; //Instanciated by constructor
};

#endif