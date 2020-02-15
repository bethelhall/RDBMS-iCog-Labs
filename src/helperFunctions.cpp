#include "helper.hpp"
#include "database.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <cctype>
#include <iomanip>
#include <string.h>
#include <vector>
#include <algorithm>


using std::fstream;
using std::ios;
using std::cout;
using std::endl;
using std::vector;

//Constants For Displaying in Tabular Form In Terminal
const char separator    = ' ';
const int nameWidth     = 28;
const int numWidth      = 10;

template <typename T>
string numberToString ( T Number )
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

// definition of left trim functions to erase spaces 
static inline std::string ltrim(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// definition of right trim function to erase space
static inline std::string rtrim(std::string s) 
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// definition of trim function to erase space
static inline std::string trim(std::string s) 
{
    return ltrim(rtrim(s));
}
// check for alphabetic and numeric values
bool isAlpha(string name)
{
	for(int i=0;i<name.size();i++)
		if(!( (name[i]>='a' && name[i]<='z')|| (name[i]>='A' && name[i]<='Z') ) )
			return false;
	return true;
}

bool isAlphaNumeric(string name)
{
	for(int i=0;i<name.size();i++)
		if(!( (name[i]>='a' && name[i]<='z')|| (name[i]>='A' && name[i]<='Z') || (name[i]>='0' && name[i]<='9') || name[i]=='_' || name[i]==' ' ||name[i]=='-'|| name[i]=='|') )
			return false;
	return true;
}

//Function for printing elements on terminal
template<typename T> 
void printElement(T t, const int& width,int flag)
{
	if(flag==1)
	    std::cout << std::left << std::setw(width) << std::setfill(separator) << t;
	else
	    std::cout << std::setw(width) << std::setfill(separator) << t;
}

// definition for commaseparatedstring 
vector<string> commaSeparatedStrings(string list ,char delimiter)
{
    std::stringstream ss(list);
    vector<string> result;
    while(ss.good())
    {
        string substr;
        getline(ss,substr,delimiter);
        result.push_back(substr);
    }
    return result;
}
// generic function to throw error
void throwError(string error)
{
	throw error;
}