#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <ostream>
#include <vector>

using std::string;
using std::vector;


// string parser
vector<string> parseQuery(string query);

//declaration for changing number to string
template <typename T>
string numberToString ( T Number );

// print elemement on the terminal
void printElement(const int& width,int flag);


// check alaphabetic
bool isAlpha(string name);
bool isAlphaNumeric(string name);
bool attributeExitsinTable(string Attribute);


// error generic function
void throwError(string error);

vector<string> commaSeparatedStrings(string list ,char delimiter);



