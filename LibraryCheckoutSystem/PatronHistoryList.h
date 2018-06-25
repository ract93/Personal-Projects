//Ricardo Carrillo
//Lab 4
#ifndef PatronHistoryList_h
#define PatronHistoryList_h

#include <iostream>
#include <string>
using namespace std;

class PatronHistoryList
{

public:
	PatronHistoryList();
	~PatronHistoryList();
	void insertFront(string movie);
	void insertBack(string movie);
	void printList();
	void deleteList();
private:
	struct HistoryNode
	{
		HistoryNode *next;
		HistoryNode *prev;
		string book;

		HistoryNode(string m)
		{
			book = m;
			this->next = NULL;
			this->prev = NULL;
		}
	};
	HistoryNode *head;
	HistoryNode *tail;
};

#endif