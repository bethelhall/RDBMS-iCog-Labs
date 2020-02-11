#include "table.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>


using std::string;
using std::map;
using std::vector;
using std::string;

class Database
{
public:
//each public declaration for database class
    string DatabaseName;
    vector<Table> Tables;
    map<string, int> tableIndexMap;
    int noOfTables;
    Database();
    void CreateDatabase(string name);
    string getDatabaseName();
    void NameTable(string name);
    void CreateTable(string tableName, vector<string> attributes, vector<string> attributes_types);
    void showTables();
    bool tableExists(string name);
    int getTableIndexByName(string name);
    Table& getTableByName(string name);
    void clearDataBase();

};