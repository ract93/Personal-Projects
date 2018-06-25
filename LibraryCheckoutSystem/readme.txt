Library checkout system with c++

1. Most of the program tested except for initCommands() on the highest level within library.h/.cpp which is supposed to handle parsing
and execution of data4commands. The error is somewhere in how the data file is parsed. , but only the base case
(bad input message) is being called.

2. A Hash table is implementend in PatronHashTable .h/.cpp that is used to store patrons. 

3. Book data is read and handeled at the high level by initRentals() in library.h/.cpp .

4. Commands are read and handeled at the high level by initCommands() within library.h / .cpp but currently bugged.

5. Commands are read based on a switch statement. This could be better generalized as its own class using virtual methods
and more easily extended. Same thing with checkout/ return which are exactly the same 
besides the lover level function call to librarySList. 

6. Skip list implemented in librarySList to store the books by catagory and print them sorted. 
