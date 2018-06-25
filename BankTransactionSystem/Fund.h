//TODO Change signitures
#ifndef FUND_H
#define FUND_H

#include <string>
#include <vector>

using namespace std;

class Fund
{
	public:
		Fund(string name);
		~Fund();

		string getName() const;
		int getBalance() const;
		vector<string> getRecord();

		//These are the actual setters for the funds
		bool InnerDeposit(unsigned int amount); 
		bool InnerWithdraw(unsigned int amount);
		bool AddHistory(string record);

	private:
		int pBalance;
		string pName;
		vector<string> pHistory; //String of vectors detailing fund history
};

#endif