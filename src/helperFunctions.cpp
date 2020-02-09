#include "header.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <climits>
#include <cctype>
#include <iomanip>
#include <string.h>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <algorithm>

using std::fstream;
using std::ios;
using std::cout;
using std::endl;
using std::stack;
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
static inline std::string ltrim(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}
static inline std::string rtrim(std::string s) 
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

static inline std::string trim(std::string s) 
{
    return ltrim(rtrim(s));
}

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


vector<Tuple> addTwoTuples(vector<Tuple> A, vector<Tuple> B)
{
	vector<Tuple> X;
	for(int i=0;i<A.size();i++)
	{
		X.push_back(A[i]);
	}
	for(int i=0;i<B.size();i++)
	{
		X.push_back(B[i]);
	}
	return X;
}

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
void throwError(string error)
{
	throw error;
}
void loadData()
{
	fstream fileObject;
	//load csv file
	fileObject.open("../TablesInfo.csv", ios::in);
	if(!fileObject.is_open())
	{
		cout <<"hello"<<endl;
		throw "Error Opening File TablesInfo.csv, Please Retry...";
	}
	int tableOpen=0, istableNameSet=0;
	int schemaOpen=0,isSchemaSet=0;
	string tableName="";
	vector<string> attributes;
	vector<string> attributes_types;
	vector<vector<string> > dataForTable;
	string line;
	while(getline(fileObject,line))
	{
		//cout<<line<<endl;
		line=trim(line);
		if(line=="")
			continue;
		else if(line=="<Table>")					//Error Check
		{
			if(tableOpen==0 && schemaOpen==0 && isSchemaSet==0 && istableNameSet==0)
				tableOpen=1;
			else
				throwError("Error In TablesInfo.csv");
		}
		else if(line=="</Table>")											//Error Check
		{
			if(tableOpen==1 && schemaOpen==0 && isSchemaSet==1 && istableNameSet==1)
			{
				Database dataBase;
				dataBase.CreateTable(tableName,attributes,attributes_types);							// If </Table> then save table to Database
				for(int i=0;i<dataForTable.size();i++)
					dataBase.getTableByName(tableName).InsertIntoTable(dataForTable[i]);
				tableName="";
				attributes.clear();
				attributes_types.clear();
				dataForTable.clear();
				tableOpen=0;
				istableNameSet=0;
				isSchemaSet=0;
			}
			else
				throwError("Error In TablesInfo.csv");
		}
		else if(line=="<Schema>")
		{
			if(tableOpen==1 && isSchemaSet==0 && schemaOpen==0 && istableNameSet==1)
				schemaOpen=1;
			else
				throwError("Error In TablesInfo.csv");									//Error Check
		}
		else if(line=="</Schema>")
		{
			if(tableOpen==1 && schemaOpen==1 && istableNameSet ==1 && isSchemaSet==0)
			{
				isSchemaSet=1;
				schemaOpen=0;
			}
			else
				throwError("Error In TablesInfo.csv");										//Error Check
		}
		else if(tableOpen == 1 && isSchemaSet ==0 && schemaOpen==0 && istableNameSet==0)
		{
			tableName = line;
			istableNameSet=1;
		}
		else if(tableOpen==1 && istableNameSet==1 && schemaOpen==1 && isSchemaSet==0)
		{
			vector <string> att = commaSeparatedStrings(line,',');
			if(att.size()!=2)
				throwError("Error In TablesInfo.csv");
			att[0]=trim(att[0]);
			att[1]=trim(att[1]);
			if(att[0]=="" || att[1]=="")
				throwError("Error In TablesInfo.csv");
			attributes.push_back(att[0]);
			attributes_types.push_back(att[1]);
		}
		else if(tableOpen==1 && istableNameSet==1 && schemaOpen==0 && isSchemaSet==1)
		{
			vector<string> dataTuple = commaSeparatedStrings(line,'|');
			if(dataTuple.size()!=attributes.size())
				throwError("Error In TablesInfo.csv");
			dataForTable.push_back(dataTuple);
		}
		else
		{
				throwError("Error In TablesInfo.csv");
		}

	}
}