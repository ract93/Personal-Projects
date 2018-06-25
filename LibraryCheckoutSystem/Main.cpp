//Ricardo Carrillo
//Lab 4
#include "Library.h"
#include <iostream>
#include <fstream>


int main()
{
	//opens and reads all the text files
	ifstream books("data4books.txt");
	ifstream patrons("data4patrons.txt");
	ifstream commands("data4commands.txt");
	if (!books)
	{
		cout << "File could not be opened." << endl;
		return 1;
	}
	Library a;
	a.initRentals(books);
	if (!patrons)
	{
		cout << "File could not be opened." << endl;
		return 1;
	}

	a.initPatrons(patrons);
	if (!commands)
	{
		cout << "File could not be opened." << endl;
		return 1;
	}
	a.initCommands(commands);

}