#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Bank.h"

using namespace std;

int main()
{

	Bank *bank = new Bank();
	bank->ParseFile("BankTransIn.txt");
	bank->SendToTransactor();
	delete bank;
}

