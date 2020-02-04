#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <boost/variant.hpp>
#include <set>

using std::string;
using std::vector;
using boost::variant;
using std::set;


enum Type
{
    INT, DOUBLE, CHAR, BOOL, STRING
};
template<class T>
// declarations for table class

string getTableName();
void setTableName();
int getNoOfAttribute();
void setNoOfAttribute();
int getNoOfRecord();
void NoOfRecords();
vector <string> getSchema();
void setSchema(int noOfAttributes, vector<string> attributeNames, vector<string> attributeTypes);
void showSchema();
void showData();
void InsertIntoTable(std::vector<std::string>& values);

// declarations for database class

void CreateTable(string tableName, vector<string> attributes, vector<string> attributes_types);
void ShowTables();
bool tableExists(string name);
int getTableIndexByName(string name);
void ClearDatabase();

//declaration for Attribute class
void setValues(string attributeName, string dataType);
string getName();
//Type getDataType();
string getDataTypeString();
void printAttribute();
void printDatatype();

// declarations  for Tuple class
set<variant<int, std::string>> buildTuple(variant<int, std::string, double, char, bool>);

// check alaphabetic
bool isAlphaNumeric(string name);
bool attributeExitsinTable(string Attribute);







