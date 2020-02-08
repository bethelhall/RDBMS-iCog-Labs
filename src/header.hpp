#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <boost/variant.hpp>
#include <set>

using std::string;
using std::map;
using std::vector;
using boost::variant;
using std::set;
using std::string;

// declaration of Enum
enum Type
{
    INT, DOUBLE, CHAR, BOOL, STRING
};

//declaration for changing number to string
template <typename T>
string numberToString ( T Number );


bool starts_with(string s1, string s2);
bool checkBalancedParenthesis(string query);

// print elemement on the terminal
void printElement(const int& width,int flag);

// check alaphabetic
bool isAlpha(string name);
bool isAlphaNumeric(string name);
bool attributeExitsinTable(string Attribute);

// error generic function
void throwError(string error);

vector<string> commaSeparatedStrings(string list ,char delimiter);

// load data
void loadData();

//declaration of Table, Database, Tuple and Attribute class
class Attribute
{
    private:
        string attributeNames;
        Type dataType;
        string enumToString(Type v);
        Type stringToEnum(string v);
    public:
        Attribute();
        Attribute(string attributeName, Type dataType);
        Attribute(string attributeName,string dataType);
        bool operator ==(const Attribute &x) const;
        void setValues(string attributeName, string dataType);
        string getName();
        Type getDataType();
        string getDataTypeString();
        void printAttribute();
        void printDatatype();

};


class Tuple
{
    private:
        bool null;
        variant<int, std::string, bool, double, char> cellValue;
        Type dataType;
        string enumToString(Type v);
    public:
        Tuple();
        Tuple(variant<int, std::string, bool, double, char> value);
        bool operator<(const Tuple &x) const;
        void setValue(variant<int, std::string, bool, double, char> value);
        variant<int, std::string, bool, double, char> getValue();
        Type getDataType();
        string getDataTypeString();
        void printTuple();
        bool isNull();


};
class Table
{
    private:
        string tableName;
        int NoOfAttributes;
        int NoOfRecords;
        map<std::string,int> attributeIndexMap;
        vector<Attribute> schema;
    public:
        //each dataInTable implemented as a set so that no data need to duplicated
        // dataInTable defined as set of set of class object
        set<Tuple> cell;
        set<vector<Tuple>> dataInTable;
        Table();
        Table(string tableName, int noOfAttributes, vector<string> attributeNames, vector<string> attributeTypes);
        string getTableName();
        void setTableName(string name);
        int getNoOfAttributes();
        void setNoOfAttributes(int number);
        int getNoOfRecords();
        vector<Attribute> getSchema();
        void setSchema(int NoOfAttributes, vector<string> attributeNames, vector<string> attributeTypes);
        void showSchema();
        void showData();
        void InsertIntoTable(vector<string> & values);
        bool attributeExitsinTable(string attribute);
        Attribute getAttributeByName(string name);
        int getAttributeIndexByName(string name);
        void addAttributeToSchema(Attribute newAttribute);
        void addDataTuple(vector<Tuple> dataTuple);
        bool dataTupleExists(vector<Tuple> dataTuple);
        bool isDisjointSchema(std::vector<Attribute> otherSchema);
        bool isSchemaSame(Table A);


};

class Database
{
    public:
        vector<Table> Tables;
        map<string, int> tableIndexMap;
        int noOfTables;
        Database();
        void CreateTable(string tableName, vector<string> attributes, vector<string> attributes_types);
        void showTables();
        bool tableExists(string name);
        int getTableIndexByName(string name);
        Table& getTableByName(string name);
        void clearDataBase();

};

// set operations functions
Table ProjectTable(Table table, vector<string> attributes);
Table QueryParser(string query);
