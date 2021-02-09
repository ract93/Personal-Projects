//Ricardo Carrillo - Boggle Challenge
//Assignment: Given a M x N char matrix, write an algorithm to find words using the rules of the Boggle game

#include <iostream> 
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>


// Converts alphabet key into index (ASCII) 
#define CHAR_TO_INDEX(c) ((int)c - (int)'A') 

//=======================================================================================================================================================================
//Unity API 
struct Results

{

	const char* const* Words;    // pointers to unique found words, each terminated by a non-alpha char 
								 // Not sure Im using this correctly. I understood this as a const pointer to an array of const char* (null terminated) 					

	unsigned           Count;    // number of words found

	unsigned           Score;    // total score

	void*              UserData; // ignored by test framework; can use for your own purposes


	std::vector<std::string> WordStrings;//Added vector to contain found strings, later converted to const char* const* Words
	std::vector<const char*> WordPointers;//Added vector to contain const char* to the found strings. 

	Results()//Constructor for Result
	{
		Count = (unsigned)0;
		Score = (unsigned)0;
		Words = NULL;
		UserData = NULL; 
	}
	
	//Destructor to clear buffers? 

};


// input dictionary is a file with one word per line, only words without numbers or punctuation. 
void LoadDictionary(const char* path);
void FreeDictionary();

// `board` is row-major and exactly `width` * `height` chars; char 'q' represents the 'qu' Boggle cube
template<int m, int n>
Results FindWords(char boggle [m][n]);//Modified signature 
// `results` is identical to what was returned from `FindWords`
void FreeWords(Results results);//QUESTION: This signature means results is passed by value, how can this be used to deallocate Results? 



// Trie Node 
struct TrieNode
{
	TrieNode *Child[26];
	// leaf is true if the node represents 
	// end of a word 
	bool leaf;
};
//========================================================================================================================================================================



//Implementation

//Global Data Members
bool g_dictInitialized = false;
bool g_resultsInitialized = false;
TrieNode *g_dictionary;


//TRIE FUNCTIONS
// Returns new trie node in heap (children initialized to NULLs) 
TrieNode *getNode()
{
	TrieNode * newNode = new TrieNode;//Initialize node in heap, freed in freeTrie()
	newNode->leaf = false;
	for (int i = 0; i < 26; i++)
		newNode->Child[i] = NULL;
	return newNode;
}

// Returns true if root has no children, else false 
bool isEmpty(TrieNode* root)
{
	for (int i = 0; i < 26; i++)
	{
		if (root->Child[i] != NULL)
		{
			return false;
		}
	}
	return true;
}

// If not present, inserts a word into the trie 
void insert(TrieNode *root, std::string word)
{
	int n = word.length();

	for (int i = 0; i < n; i++)
	{
		int key = CHAR_TO_INDEX(word[i]);

		if (key < 0 || key >25)//Filter bad input, punctuation, and spaces
		{
			//std::cout << "Bad input at char:" + std::to_string(word[i]) << std::endl;
			//std::cout << std::endl;
		}

		else// Good input
		{
			if (root->Child[key] == NULL)//Check if already initialized
				root->Child[key] = getNode();

			root = root->Child[key];
		}
	}
	// make last node a leaf node 
	root->leaf = true;
}

TrieNode *LoadTrie(const char * path) //Creates a Trie from a .txt dictionary given the relative path. Dictionaries must be line seperated, only covers words containing A-Z
{
	//Open txt file from path, if input is bad, return empty trie. 
	std::ifstream readDict(path);
	if (!readDict.is_open())
	{
		std::cout << "File does not exist" << std::endl;
		TrieNode * head = getNode();
		return head; 
	}

	std::string line;
	std::vector<std::string> dictionary;

	while (!readDict.eof()) 
	{
		getline(readDict, line);

		//Make line uppercase
		std::for_each(line.begin(), line.end(), [](char & c)
		{
			c = ::toupper(c);
		});

		dictionary.push_back(line);
		//std::cout << line << std::endl;
	}

	//Initialize trie in heap
	TrieNode * head = getNode();

	int n = dictionary.size();

	for (int i = 0; i < n; i++)
	{
		insert(head, dictionary[i]);
	}

	return head;

}

void FreeTrie(TrieNode * dictionary) //Transverse tree and free memory bottom up
{
	//No trie to free
	if (dictionary == NULL)
		return;

	//All children are null
	if (isEmpty(dictionary)) 
	{  
		delete dictionary;
		return;
	}

	//If neither null or empty, DFS
	else
	{
		for (int i=0; i<26; i++)
		{
			FreeTrie(dictionary->Child[i]);
			//Dangling pointers?
		}
		delete dictionary;
	}
}

void LoadDictionary(const char* path)//Unity
{
	if (g_dictInitialized == true)//Dictionary already loaded, free and reload, initialization flag remains true 
	{
		FreeDictionary();
		g_dictionary = LoadTrie(path);
		//std::cout << "Dictionary reloaded" << std::endl;
		//std::cout << std::endl;
		g_dictInitialized = true;
	}

	else//If no dictionary already loaded, load dictioanary, set initialization flag to true
	{
		g_dictionary = LoadTrie(path);
		//std::cout << "Dictionary loaded" << std::endl;
		//std::cout << std::endl;
		g_dictInitialized = true;
	}
}

void FreeDictionary() //Frees memory allocated to the dictionary trie
{
	if (g_dictInitialized == false)//No dictionary loaded, do nothing
	{
		//std::cout << "No dictionary to delete" << std::endl;
		//std::cout << std::endl;
		return;
	}

	else //Delete dictionary, and set initialization flag to false
	{
		FreeTrie(g_dictionary);
		//std::cout << "Dictionary deleted" << std::endl;
		//std::cout << std::endl;
		g_dictInitialized = false;
		return;
	}
}


//MISC FUNCTIONS

//function that calculates the score of a found word.
int calcScore(std::string input)
{
	if (input.length() == 3 || input.length() == 4)
		return 1;
	if (input.length() == 5)
		return 2;
	if (input.length() == 6)
		return 3;
	if (input.length() == 7)
		return 5;
	if (input.length() >= 8)
		return 8;
	else
		return 0;

}

//prints the results struct
void printResults(Results res)
{
	std::cout << std::endl;
	std::cout << "Results:" << std::endl;
	std::cout << "Count: " + std::to_string(res.Count) << std::endl;
	std::cout << "Score: " + std::to_string(res.Score) << std::endl;
	std::cout << "Words: "; //<< std::endl;
	//for (int i = 0; i < res.WordStrings.size(); i++)
		//std::cout << res.WordStrings[i] << " ";

	int wordsSize = res.WordStrings.size();
	for(int i = 0; i < wordsSize; ++i)
		std::cout << res.Words[i] << " ";

	std::cout << std::endl;

}


//BOARD FUNCTIONS
// function that checks that the current location of i and j is in matrix range 
template<int m, int n> //Template allows dynamic sizing
bool isSafe(int i, int j, bool visited[m][n])
{
	return (i >= 0 && i < m && j >= 0 &&
		j < n); // j < n && !visited[i][j]); //Im assuming you can actually repeat visited cells, or you wouldnt be able to find tuque in the example. 
											 //Uncomment the commented out code if not allowed.
}

// A recursive helper function to finds all words present on a boggle board and writes results to a struct, given the board and the head of a dictionary trie
template<int m, int n>//Template to allows dynamic sizing at runtime. <0,0> and negatives not allowed by calling function.
void FindHelper(TrieNode *root, char boggle[m][n], int i, int j, bool visited[][n], std::string str, Results *res)
{
	// If trieNode is a leaf, we completed a word in the trie.  
	if (root->leaf == true)
	{
		//std::cout << "Found " + str + " Worth " + std::to_string(calcScore(str)) + " point(s)"<< std::endl;
		res->Count++;
		res->Score += calcScore(str);
		res->WordStrings.push_back(str);
	}

	// If both i and j is in range and have not been visited
	// found first occurance of this element in the board
	if (isSafe<m,n>(i, j, visited))
	{
		// mark as visited
		visited[i][j] = true;

		// traverse all children of current node 
		for (int K = 0; K < 26; K++)
		{
			if (root->Child[K] != NULL)
			{
				// Find ASCII of current character, and access node with that key 
				char ch = (char)K + (char)'A';

				// Recursively search remaining characters of the word 
				// in trie for all 8 adjacent cells of current location boggle[i][j] if it is valid
				if (isSafe<m, n>(i + 1, j + 1, visited) && boggle[i + 1][j + 1] == ch)
					FindHelper<m,n>(root->Child[K], boggle, i + 1, j + 1, visited, str + ch, res);

				if (isSafe<m, n>(i, j + 1, visited) && boggle[i][j + 1] == ch)
					FindHelper<m,n>(root->Child[K], boggle, i, j + 1, visited, str + ch, res);

				if (isSafe<m, n>(i - 1, j + 1, visited) && boggle[i - 1][j + 1] == ch)
					FindHelper<m,n>(root->Child[K], boggle, i - 1, j + 1, visited, str + ch, res);

				if (isSafe<m, n>(i + 1, j, visited) && boggle[i + 1][j] == ch)
					FindHelper<m,n>(root->Child[K], boggle, i + 1, j, visited, str + ch, res);

				if (isSafe<m, n>(i + 1, j - 1, visited) && boggle[i + 1][j - 1] == ch)
					FindHelper<m,n>(root->Child[K], boggle, i + 1, j - 1, visited, str + ch, res);

				if (isSafe<m, n>(i, j - 1, visited) && boggle[i][j - 1] == ch)
					FindHelper<m,n>(root->Child[K], boggle, i, j - 1, visited, str + ch, res);

				if (isSafe<m, n>(i - 1, j - 1, visited) && boggle[i - 1][j - 1] == ch)
					FindHelper<m,n>(root->Child[K], boggle, i - 1, j - 1, visited, str + ch, res);

				if (isSafe<m, n>(i - 1, j, visited) && boggle[i - 1][j] == ch)
					FindHelper<m,n>(root->Child[K], boggle, i - 1, j, visited, str + ch, res);
			}
		}
		// make current element unvisited 
		visited[i][j] = false;
	}
}

// Finds all dictionary words present in boggle board
template<int m, int n> //Template allows dynamic sizing at runtime. 
Results InnerFindWords(char boggle[m][n], TrieNode *dict)
{
	//Initialize Results struct;
	Results res = Results(); //Result is on stack, so dont need dynamic memory allocation.  

	// Visited array of same size as boggle board 
	bool visited[m][n];
	memset(visited, false, sizeof(visited));//Initialize to not visited

	std::string str = "";

	// traverse all matrix elements 
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// start searching for a word in the dictionary 
			// If it is a match in the trie, call DFS search on adjascent cells. 
			if (dict->Child[CHAR_TO_INDEX(boggle[i][j])])
			{
				str = str + boggle[i][j];
				FindHelper<m, n>(dict->Child[CHAR_TO_INDEX(boggle[i][j])], boggle, i, j, visited, str, &res);//Pass res by reference to recursive function
				str = "";
			}
		}
	}

	//Fill WordPointers with pointers pointing to the Strings in WordStrings.
	for(int k = 0; k < res.WordStrings.size(); k++)
	{
		res.WordPointers.push_back(res.WordStrings[k].c_str());//c_str() returns a const char* to a string. 
	}

	//Point Words to the data contained inside of WordPointers. Not sure if this is the intended use of the Words field.
	res.Words = res.WordPointers.data();//Not normally safe, but the strings, pointers, and vectors are in the same struct so they will go out of scope at the same time. 
	
	return res;
}

//Function to Find Words in a Boggle board of M x N size.
template<int m, int n>
Results FindWords(char board[m][n])
{
	//No dictionary loaded, return empty results. 
	if(g_dictInitialized == false)
	{
		Results res = Results(); 
		return res;
	}

	// Invalid board size, return empty results; 
	if (m < 1 || n < 1)
	{
		Results res = Results();
		return res;
	}

	else
	{
		Results res = InnerFindWords<m, n>(board, g_dictionary);
		return res;
	}
}

void FreeWords(Results results)// Frees memory allocated to a Result object
{
	//Nothing needs to happen here. No part of Results is allocated to heap, so it will be deleted automatically when the destructor is called. 
	return;
}

//Test Main
int main()
{
	char boggle1[3][3] =
	{   {'D','Z','X'},
		{'E','A','I'},
		{'Q','U','T'}
	};

	char boggle2[4][4] =
	{	{'D','Z','X','Y'},
		{'E','A','I','A'},
		{'Q','U','T','L'},
		{'E','F','L','E'}
	};

	LoadDictionary("ShortDict.txt");
	Results res1 = FindWords<3,3>(boggle1);
	LoadDictionary("LongDict.txt");
	Results res2 = FindWords<4,4>(boggle2);
	FreeDictionary();
	Results res3 = FindWords<3, 3>(boggle1);
	printResults(res1);
	printResults(res2);
	printResults(res3);

	return 0;

} 



