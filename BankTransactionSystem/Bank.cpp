#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Bank.h"

Bank::Bank() {}
Bank::~Bank() {}

bool Bank::AddToQueue(vector<string> command)
{
	commandQueue.push(command);
	return true;
}

void Bank::ParseFile(string path)
{
	ifstream fstream;
	string tempstr = "";
	vector<string> data;

	fstream.open(path);

	while (!fstream.eof())
	{
		fstream >> tempstr;
		data.push_back(tempstr);

		// This only works if input is well formed
		if (data[0] == "T")
		{
			// ID1
			fstream >> tempstr;
			data.push_back(tempstr.substr(0, tempstr.length() - 1));

			// Fund1
			data.push_back(tempstr.substr(tempstr.length() - 1,
				tempstr.length() - 1));

			// Amount
			fstream >> tempstr;
			data.push_back(tempstr);

			// ID2
			fstream >> tempstr;
			data.push_back(tempstr.substr(0, tempstr.length() - 1));

			// Fund2
			data.push_back(tempstr.substr(tempstr.length() - 1,
				tempstr.length() - 1));
		}
		
		// Open
		else if (data[0] == "O")
		{
			// Last Name
			fstream >> tempstr;
			data.push_back(tempstr);

			// First Name
			fstream >> tempstr;
			data.push_back(tempstr);

			// ID1
			fstream >> tempstr;
			data.push_back(tempstr);
		}
		else if (data[0] == "H")
		{
			// ID1
			fstream >> tempstr;

			// Checks fund type
			if (tempstr.length() == 5)
			{
				data.push_back(tempstr.substr(0, tempstr.length() - 1));

				// Fund1
				data.push_back(tempstr.substr(tempstr.length() - 1,
					tempstr.length() - 1));
			}
			// Handles history
			else
			{
				data.push_back(tempstr);
			}

		}
		// Carry out transaction
		else
		{
			// ID1
			fstream >> tempstr;
			data.push_back(tempstr.substr(0, tempstr.length() - 1));

			// Fund1
			data.push_back(tempstr.substr(tempstr.length() - 1,
				tempstr.length() - 1));

			// Money
			fstream >> tempstr;
			data.push_back(tempstr);
		}

		// Push vector to queue
		AddToQueue(data);

		// Clear vector
		data.clear();
	}
}


bool Bank::SendToTransactor() //DO NOT CALL UNTIL THE QUEUE IS CREATED, PROGRAM EXPLODES
{	
	return transactor.ProcessQueue(commandQueue);
}