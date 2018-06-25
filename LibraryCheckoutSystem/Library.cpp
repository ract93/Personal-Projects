//Ricardo Carrillo
//Lab 4
#include "Library.h"
//---------------------------------------------------------------------------
// Library()
// creates the library object
// Preconditions: library object does not exist
// Postconditions: library object created
// --------------------------------------------------------------------------
Library::Library()
{
	this->numPatrons = 0;
}
//---------------------------------------------------------------------------
// ~LibraryStore()
// deletes the library object
// Preconditions: library object exist
// Postconditions: library object deleted
// --------------------------------------------------------------------------
Library::~Library()
{

	delete this;
}
//---------------------------------------------------------------------------
// initRentals()
// reads in the books from the text file and inserts them into the 
// corresponding skip list based on type
// Preconditions: NONE
// Postconditions: full skip list of patrons
// --------------------------------------------------------------------------
void Library::initRentals(ifstream& input)
{
	string title, author;
	char type;
	int stock;
	string badInput;

	for (;;)
	{
		input >> type;
		
		if (input.eof())
			break;

		if (type == 'P') // Periodical
		{
			getline(input, title, ',');
			int releaseMonth;
			int releaseYear;

			input >> releaseMonth >> releaseYear;
			//book created as corresponding type and added to list
			// Stock parameter hard passed as one. Allows for stock to be extended so multiple can be added. 
			Book  *r = new Periodical(1, title, author, releaseMonth, releaseYear);
			PeriodicalsList.insert(r);
			//put r into hashtable

		}
		else if (type == 'Y') //Childrens
		{
			getline(input, author, ',');
			getline(input, title, ',');
			int releaseYear;
			input >> releaseYear;
			//book created as corresponding type and added to list
			// Stock parameter hard passed as one. Allows for stock to be extended so multiple can be added. 
			Book  *r = new Childrens(1, title, author, releaseYear);
			ChildrensList.insert(r);
			//put r into hashtable
		}
		else if (type == 'F') // Fiction
		{
			getline(input, author, ',');
			getline(input, title, ',');
			int releaseYear;
			input >> releaseYear;
			//book created as corresponding type and added to list
			// Stock parameter hard passed as one. Allows for stock to be extended so multiple can be added. 
			Book  *m = new Fiction(1, title, author, releaseYear);
			FictionList.insert(m);
			//put r into hashtable
		}
		//not correct book type, input is ignored and user notified
		else
		{
			getline(input, badInput, '\n');

			cout << "Bad Book Input" << endl << type << " " << stock << " " << title
				<< " " << author << " " << badInput << endl;
		}
		//variables reset
		type = ' ';
		stock = 0;
		author = "";
		title = "";
		badInput = "";
	}
}
//---------------------------------------------------------------------------
// initPatrons()
// reads in the customers from the text file and inserts them into the 
// hash table
// Preconditions: NONE
// Postconditions: full hash table of Patrons
// --------------------------------------------------------------------------
void Library::initPatrons(ifstream& input)
{
	string firstName, lastName;
	int patronID;

	int i = 0;
	for (;;)
	{
		input >> patronID >> firstName >> lastName;
		//ignores any other input
		input.ignore(144, '\n');
		Patron *c = new Patron(patronID, firstName, lastName);

		this->numPatrons++;
		//patron object added to hashtable
		patrons.insert(c);

		if (input.eof())
			break;
		i++;
	}
}

//---------------------------------------------------------------------------
// initCommands()
// reads in the commands from the text file and executes them
// Preconditions: patron hash table and book slists full
// Postconditions: NONE
// --------------------------------------------------------------------------

void Library::initCommands(ifstream & input) //BUG HERE! No input is parsing
{
	bool badInput = false;
	char actionType, bookType, mediaType;
	string title, author;
	//used to keep hold all the info of the transaction
	stringstream history;
	int patronID, releaseYear, releaseMonth;

	//loops until end of file is found
	for (;;)
	{
		input >> actionType;
		switch (actionType)
		{

		case 'C': //CHECKOUT
		{
			history << actionType;
			input >> patronID >> bookType >> mediaType;
			history << WHITE_SPACE << patronID << WHITE_SPACE << bookType
				<< WHITE_SPACE << mediaType << WHITE_SPACE;
			
			//check if customer ID is valid
			Patron *f = NULL;
			if (!patrons.searchPatron(patronID, f))
			{
				badInput = true;
				cout << "Patron ID not valid" << endl;
				input.ignore(144, '\n');
				break;
			}

			if (!badInput)
			{
				switch (bookType)//Switch on book type
				{


				case 'P': // Periodical YEAR MONTH TITLE,
				{
					input >> releaseYear >> releaseMonth;
					getline(input, title, ',');
					history << releaseYear << WHITE_SPACE << releaseMonth << WHITE_SPACE << title;
					Periodical *tmpPeriodical = NULL;
					if (PeriodicalsList.searchPeriodical(mediaType, releaseMonth,
						releaseYear, tmpPeriodical))//Search book
					{
						//borrow book
						tmpPeriodical->checkOut(mediaType);
						//add transaction to patron history
						f->addHistory(history.str());
					}
					else
					{
						cout << "Book not found: " << bookType << WHITE_SPACE << mediaType << WHITE_SPACE << releaseYear
							<< WHITE_SPACE << releaseMonth << WHITE_SPACE << title << endl;
						//clears history stringstream
						history.str("");
						break;
					}
				}
				break;


				case 'Y': // Childrens TITLE, AUTHOR,
				{
					getline(input, title, ',');
					getline(input, author, ',');

					history << title << WHITE_SPACE << author << WHITE_SPACE;
					Childrens *tmpChildren = NULL;
					if (ChildrensList.searchChildren(mediaType, title, author, tmpChildren))
					{
						//borrow book
						tmpChildren->checkOut(mediaType);
						//add transaction to patron history
						f->addHistory(history.str());
					}
					else
					{
						cout << "Book not found: " << bookType << WHITE_SPACE << mediaType << WHITE_SPACE <<title
							<< WHITE_SPACE << author << WHITE_SPACE << endl;
						history.str("");
						break;
					}
				}
				break;


				case 'F': //Fiction AUTHOR, TITLE,
				{
					getline(input, author, ',');
					getline(input, title, ',');

					history << author << WHITE_SPACE << title << WHITE_SPACE;
					Fiction *tmpFiction = NULL;
					if (FictionList.searchFiction(mediaType, author, title, tmpFiction))
					{
						//borrow book
						tmpFiction->checkOut(mediaType);
						//add transaction to history
						f->addHistory(history.str());
					}
					else
					{
						cout << "Book not found: " << bookType << WHITE_SPACE << author
							<< WHITE_SPACE << title << WHITE_SPACE << endl;
						history.str("");
						break;
					}
				}
				break;
				default:
					cout << "Invalid book catagory for checkout." << endl;
					string badInput;
					getline(input, badInput, '\n');
					cout << actionType << WHITE_SPACE << patronID << WHITE_SPACE << mediaType
						<< WHITE_SPACE << bookType << WHITE_SPACE << badInput << endl;
					break;
				}
			}
		}
		break;
	
		case 'R': //RETURN
		{
			history << actionType;
			input >> patronID >> bookType >> mediaType;
			history << WHITE_SPACE << patronID << WHITE_SPACE << bookType
				<< WHITE_SPACE << mediaType << WHITE_SPACE;

			//Check if patron id is valid
			Patron *f = NULL;
			if (!patrons.searchPatron(patronID, f))
			{
				badInput = true;
				cout << "Patron ID not valid" << endl;
				input.ignore(144, '\n');
				break;
			}

			switch (bookType)
			{
			case 'P': // Periodical TITLE, MONTH YEAR
			{
				input >> releaseYear >> releaseMonth;
				getline(input, title, ',');
				history << releaseYear << WHITE_SPACE << releaseMonth << WHITE_SPACE << title;
				Periodical *tmpPeriodical = NULL;
				if (PeriodicalsList.searchPeriodical(mediaType, releaseMonth,
					releaseYear, tmpPeriodical))//Search book
				{
					//return book
					tmpPeriodical->returnRental(mediaType);
					//add transaction to patron history
					f->addHistory(history.str());
				}
				else
				{
					cout << "Book not found: " << bookType << WHITE_SPACE << mediaType << WHITE_SPACE << releaseYear
						<< WHITE_SPACE << releaseMonth << WHITE_SPACE << title << endl;
					//clears history stringstream
					history.str("");
					break;
				}
			}
			break;

			case 'Y': // Childrens TITLE, AUTHOR,
			{
				getline(input, title, ',');
				getline(input, author, ',');
				input >> releaseYear;
				history << title << WHITE_SPACE << author << WHITE_SPACE;
				Childrens *tmpChildren = NULL;
				if (ChildrensList.searchChildren(mediaType, title, author, tmpChildren))
				{
					//return book
					tmpChildren->returnRental(mediaType);
					//add transaction to patron history
					f->addHistory(history.str());
				}
				else
				{
					cout << "Book not found: " << bookType << WHITE_SPACE << mediaType
						<< WHITE_SPACE << title << WHITE_SPACE << author << endl;
					history.str("");
				}
			}
			break;

			case 'F': // Fiction AUTHOR, TITLE,
			{
				getline(input, author, ',');
				getline(input, title, ',');
				history << author << WHITE_SPACE << title << WHITE_SPACE;
				Fiction *tmpFiction = NULL;
				if (FictionList.searchFiction(mediaType, author, title, tmpFiction))
				{
					//borrow book
					tmpFiction->returnRental(mediaType);
					//add transaction to history
					f->addHistory(history.str());
				}
				else
				{
					cout << "Book not found: " << bookType << WHITE_SPACE << mediaType 
						<< WHITE_SPACE << author << WHITE_SPACE << title << endl;
					history.str("");
				}
			}
			break;

			default:
				cout << "Invalid book catagory for return." << endl;
				string badInput;
				getline(input, badInput, '\n');
				cout << actionType << WHITE_SPACE << patronID << WHITE_SPACE << mediaType
					<< WHITE_SPACE << bookType << WHITE_SPACE << badInput << endl;
				break;

			}
			break;
		}
		//case for printing out inventory
		case 'D': //DISPLAY
			//prints out the lists in order of comedy, drama, then classics
			ChildrensList.print('Y');
			FictionList.print('F');
			PeriodicalsList.print('P');
			break;
		
		case 'H': //HISTORY
		{
			input >> patronID;
			Patron *f = NULL;
			//customer exists, print out history
			if (patrons.searchPatron(patronID, f))
				f->printHistory();

			//customer does not exist
			else
			{
				input.ignore(144, '\n');
				delete f;
			}
			break;
		}
		//command not correct, ignores the line and alerts user
		default:
			cout << "bad command input" << endl;
			input.ignore(144, '\n');
			break;
		}
		//ends infinite loop at end of file
		if (input.eof())
		{
			break;
		}

		//reset variables for next round
		history.str(""); 
		mediaType = ' ';
		bookType = ' ';
		badInput = false;
		title = "";
		author = "";
		patronID = 0;
		releaseYear = 0;
		releaseMonth = 0;

		actionType = ' ';
	}
}
