V2

The interface is still not quite right, but closer to what you wanted in spirit. 

The issue is basically just that my FindWords() with signature:

template<int m, int n>
Results FindWords(char board[m][n])


is not compatible with the signature given in the interface of:

Results FindWords(const char* board, unsigned width, unsigned height);



I basically just cant figure out how a 2d boggle board is supposed to be passed with a const char*.
I thought about building a string with the 2d char array row by row, assigning a const char pointer to that string 
passing that with the const char* and then building it again on the other side, but the problem with that is I dont know how the board parameter
looks like when it is passed to findWords() in your test harness, so my way of building the 2d char board again may be different and cause incorrect results. 

Otherwise, I think I have supplied all required functionality and shown an example with several boards and dictionaries.
Please let me know if you have any feedback



Compiled with G++ on windows. 

How to run:

Test main on bottom of BoggleSolver.cpp. 