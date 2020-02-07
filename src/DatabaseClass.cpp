#include "header.hpp"
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <map>
#include <cctype>
#include <vector>

using std::cout;
using std::endl;

//Initialise dataabse with zero tables
Database::Database()
{
    noOfTables=0;
}

// Adds a table to the database
void Database::CreateTable(string tableName, vector<string> attributes, vector<string> attributes_types)
{
    if(tableExists(tableName))
    {
        string error="Table Create Error: Table Already Exists With Name: "+tableName;
        throw error;
    }
    if(attributes.size()!=attributes_types.size())						
    {
            string error="Attribute Match Error: All Attributes should have a type";
            throw error;
    }

    Table newTable(tableName,attributes.size(),attributes,attributes_types);
    Tables.push_back(newTable);
    tableIndexMap[tableName]=noOfTables;
    noOfTables++;
}

//Show all tables in the database
void Database::showTables()
{
    for(int i=0;i<Tables.size();i++)
        cout<<i+1<<". "<<Tables[i].getTableName()<<endl;
}
//Check if table exists in Database
bool Database::tableExists(string name)
{
    if(tableIndexMap.count(name)>0)
        return true;
    return false;
}
//returns the index of string name in the database
int Database::getTableIndexByName(string name)
{
    if(!tableExists(name))
    {
        string error="Table Name Error: No Table With Name: "+name;
        throw error;
    }
    return tableIndexMap[name];
}

//Returns the pointer to the table with table name as name
Table& Database::getTableByName(string name)
{
    if(!tableExists(name))
    {
        string error="Table Name Error: No Table With Name: "+name;
        throw error;
    }
    int index = tableIndexMap[name];
    cout <<index<<endl;
    return Tables[index];
}

//Clear the database
void Database::clearDataBase()
{
    Tables.clear();
    tableIndexMap.clear();
};