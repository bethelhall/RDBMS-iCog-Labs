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
std::string ltrim(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}
std::string rtrim(std::string s) 
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

std::string trim(std::string s) 
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
bool checkBalancedParenthesis(string query)
{
	stack<string> brackets;														//Check the pair of brackets by pushing and poping from the stack
	for(int i=0;i<query.size();i++)
	{
		if(query[i]=='(' || query[i]=='{' || query[i]=='[')
			brackets.push(numberToString(query[i]));
		else if(query[i]==')')
		{
			if(!brackets.empty() && brackets.top()=="(")						//If it matches the same type, else error
				brackets.pop();
			else
				return false;
		}
		else if(query[i]=='}')
		{
			if(!brackets.empty() && brackets.top()=="{")						//If it matches the same type, else error
				brackets.pop();
			else
				return false;
		}
		else if(query[i]==']')
		{
			if(!brackets.empty() && brackets.top()=="[")						//If it matches the same type, else error
				brackets.pop();
			else
				return false;
		}
	}

	return true;
}
//Generic function used to throw error from anywhere in the code
void throwError(string error)
{
	throw error;
}

string removeExtraParenthese(string query)
{
	while(query[0]=='(' || query[0]=='[' || query[0]=='{')
		query = query.substr(1,query.size()-2);
	return query;
}
//Describes the schema of table "name"
bool starts_with(string s1, string s2)
{
    return s2.size() <= s1.size() && s1.compare(0, s2.size(), s2) == 0;
}
void DescribeTable(string name)
{
	Database dataBase;
	name=trim(name.substr(4));
	if(dataBase.tableExists(name))
		dataBase.getTableByName(name).showSchema();
	else
		throwError("Invalid Query: No Table Found Named \""+name+"\"");
}

//Query Parser for six basic operations
//Input: string query
//Output: Returns a Table according to the query
Table QueryParser(string query)
{
	Database dataBase;
	query = trim(query);   													//trims the trailing spaces from front and back of string
	if(query=="")															//NULL Query Check
		throwError("Query Parser Error: NULL Query Parsed");
	if(!checkBalancedParenthesis(query))									//MisBalanced Parenthesis Check
		throwError("Query Parser Error: Misbalanced Bracket Query Parsed");
	query = removeExtraParenthese(query);							//Remove Extra Brackets
	if(dataBase.tableExists(query))											//If table exists in dataabse then return table, otherwise nested query
		return dataBase.getTableByName(query);
	int firstCurlyBracket = query.find("{");								//Find position of first '{'
	int firstSquareBracket = query.find("[");								//Find position of first '['
	cout << firstCurlyBracket <<endl;
	cout << firstSquareBracket<<endl;
	if(firstSquareBracket==string::npos && firstCurlyBracket==string::npos)			//if both not found then error
		throwError("Query Parser Error: Invalid Query Or Subquery");

	int flag;
	if(firstSquareBracket!=string::npos && firstCurlyBracket!=string::npos)
	{
		if(firstCurlyBracket<firstSquareBracket)
			flag=0;
		else flag=1;
	}
	else if(firstCurlyBracket==string::npos)
		flag=1;
	else
		throwError("Query Parser Error: Proper Brackets Are Not Provided In Your Query Or Subquery");

	string checkQuery = query;
	transform(checkQuery.begin(), checkQuery.end(), checkQuery.begin(), ::toupper);
	if(flag==1 && (starts_with(checkQuery,"SELECT")||starts_with(checkQuery,"RENAME")||starts_with(checkQuery,"PROJECT")))
		throwError("Query Parser Error: Proper Brackets Are Not Provided In Your Query Or Subquery");
	if(flag==0 && (starts_with(checkQuery,"UNION")||starts_with(checkQuery,"CART")||starts_with(checkQuery,"SDIFF")))
		throwError("Query Parser Error: Proper Brackets Are Not Provided In Your Query Or Subquery");
	
	if(flag==0)
	{
		int secondCurlyBracket = query.find("}",firstCurlyBracket);
		if(secondCurlyBracket==string::npos || trim(query.substr(secondCurlyBracket+1,firstSquareBracket-secondCurlyBracket-1))!="" || query[query.size()-1]!=']')
			throwError("Query Parser Error: Proper Brackets Are Not Provided In Your Query Or Subquery");

		string queryFunction = trim(query.substr(0,firstCurlyBracket));				//extract queryfunction from query
		transform(queryFunction.begin(), queryFunction.end(), queryFunction.begin(), ::toupper);		//Transform it to UPPERCASE
		string betweenBraces = trim(query.substr(firstCurlyBracket+1,secondCurlyBracket-firstCurlyBracket-1));  //extract { } part
		string betweenBrackets = trim(query.substr(firstSquareBracket+1,query.size()-firstSquareBracket-2));	//extract [ ] part

		Table A;				

		if(dataBase.tableExists(betweenBrackets))							//If table exists in dataabse then return table, otherwise nested query
			A = dataBase.getTableByName(betweenBrackets);
		else
			A = QueryParser(betweenBrackets);

		if(queryFunction=="PROJECT")
		{
			vector<string> attributes = commaSeparatedStrings(betweenBraces,',');
			return ProjectTable(A,attributes);
		}
		else
			throwError("Query Parser Error: Wrong Query Given ");

	}
	else if(flag==1)
	{
		if(query[query.size()-1]!=']')
			throwError("Query Parser Error: Proper Brackets Are Not Provided In Your Query Or Subquery");
		
		string betweenBrackets = trim(query.substr(firstSquareBracket+1,query.size()-firstSquareBracket-2));	// extract [ ] part
		string queryFunction = trim(query.substr(0,firstSquareBracket));			//extract query function
		transform(queryFunction.begin(), queryFunction.end(), queryFunction.begin(), ::toupper);				//Convert to UPPERCASE
		//Table A B
		int count=0;
		int indexOfComma=-1;
		for(int i=0;i<betweenBrackets.size();i++)
		{
			if(betweenBrackets[i]=='(' || betweenBrackets[i]=='{' || betweenBrackets[i]=='[')
			{
				count++;
				continue;
			}
			if(betweenBrackets[i]==')' || betweenBrackets[i]=='}' || betweenBrackets[i]==']')
			{
				count--;
				continue;
			}
			if(betweenBrackets[i]==',' && count == 0 && indexOfComma==-1)
			{
				indexOfComma=i;
			}
			else if(betweenBrackets[i]==',' && count == 0 && indexOfComma!=-1)
				throwError("Query Parser Error: Query Not Given In Proper Format");

		}
		if(indexOfComma==-1 || indexOfComma==0 || indexOfComma==betweenBrackets.size()-1)
			throwError("Query Parser Error: Query Not Given In Proper Format");

		string queryA = trim(betweenBrackets.substr(0,indexOfComma));			//split strings about comma
		string queryB = trim(betweenBrackets.substr(indexOfComma+1));
		if(queryA==""||queryB=="")
			throwError("Query Parser Error: Wrong Query Given");

		Table A,B;
		if(dataBase.tableExists(queryA))
			A = dataBase.getTableByName(queryA);
		else
			A = QueryParser(queryA);
		if(dataBase.tableExists(queryB))
			B = dataBase.getTableByName(queryB);
		else
			B = QueryParser(queryB);
	}
	else
		throwError("Query Parser Error: Wrong Query Given");

}

void loadData()
{
	fstream fileObject;
	//load csv file
	fileObject.open("TablesInfo.csv", ios::in);				
	cout <<"hello"<<endl;
	int tableOpen=0, istableNameSet=0;
	int schemaOpen=0,isSchemaSet=0;
	string tableName="";
	vector<string> attributes;
	vector<string> attributes_types;
	vector<vector<string> > dataForTable;
	string line;
	while(getline(fileObject,line))
	{
		// cout<<line<<endl;
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