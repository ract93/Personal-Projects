Library checkout system with c++

Most of the program tested except for initCommands() on the highest level within library.h/.cpp handles parsing
and execution of data4commands. There is an error somewhere in how the data file is parsed. , but only the base case
(bad input message) is being called.

A Hash table is implemented in PatronHashTable .h/.cpp that is used to store patrons. 

Book data is read and handeled at the high level by initRentals() in library.h/.cpp .

Commands are read and handeled at the high level by initCommands() within library.h / .cpp but currently bugged.

Commands are read based on a switch statement. This could be better generalized as its own class using virtual methods
and more easily extended. Same thing with checkout/ return which are exactly the same 
besides the lover level function call to librarySList. 

Skip list implemented in librarySList to store the books by catagory and print them sorted. 

TODO: Fix issue with command parsing. Possibly caused by varience in how end of file is handled between windows and linux
